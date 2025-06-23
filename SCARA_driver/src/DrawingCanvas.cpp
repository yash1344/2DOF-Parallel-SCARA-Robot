#include "DrawingCanvas.h"

#include <qtmetamacros.h>
#include <QMouseEvent>
#include <QPainter>
#include <thread>

#include "Shapes/MyTriangle.h"
#include "Shapes/Rectangle.h"
#include "Utility.h"
#include "WorkSpace.h"
//#include "moc_DrawingCanvas.cpp"

DrawingCanvas::DrawingCanvas(TTT *ttt, QVector<QPointF> *path_buffer,
		QWidget *parent) :
		QWidget(parent), path_buffer(path_buffer), ttt(ttt), m_isDrawing(false), picked_point(
				Coordinate(0, 0, 0)), workSpace(Coordinate(400, 400, 0), 208,
				90, 200) {
	setAttribute(Qt::WA_StaticContents);
	setMouseTracking(true);

	// Set background to white by default
	setAutoFillBackground(true);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::white);
	setPalette(pal);
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
	if (!picking_a_point) {
		if (event->button() == Qt::LeftButton) {
			m_isDrawing = true;
			m_points.append(event->pos());
			{
				std::lock_guard<std::mutex> lock(path_mutex); // LOCK ADDED
				path_buffer->append(event->pos());
			}
			update();
		}
	} else {
		auto posi = event->pos();
		Coordinate point = Coordinate(posi.x(), posi.y(), 0);
		emit pointSelected(point); // @suppress("Type cannot be resolved")
	}
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
	if (m_isDrawing) {
		m_points.append(event->pos());
		{
			std::lock_guard<std::mutex> lock(path_mutex); // LOCK ADDED
			path_buffer->append(event->pos());
		}
		update();
	}
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		m_isDrawing = false;
	}
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(
			QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	workSpace.draw(painter, View::SIDE_VIEW);

	if (m_points.size() > 1) {
		for (int i = 1; i < m_points.size(); ++i) {
			painter.drawLine(m_points[i - 1], m_points[i]);
		}
	}

	ttt->draw(painter);

	{
		// If you’re modifying path_buffer from another thread,
		// lock the same mutex you use there:
		std::lock_guard<std::mutex> lock(path_mutex);

		if (path_buffer && path_buffer->size() > 1) {
			// Use a different color or pen to distinguish it
			painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap));
			for (int i = 1; i < path_buffer->size(); ++i) {
				painter.drawLine((*path_buffer)[i - 1], (*path_buffer)[i]);
			}
		}
	}

}

Coordinate DrawingCanvas::getPoint() {
	picking_a_point = true;
	QEventLoop loop;
	Coordinate selectedPoint;

	// Connect signal to local slot that captures point and quits loop
	connect(this, &DrawingCanvas::pointSelected, this, [&](Coordinate point) {
		selectedPoint = point;
		loop.quit();
	}, Qt::SingleShotConnection);

	loop.exec();  // Wait here until pointSelected is emitted

	picking_a_point = false;
	return selectedPoint;
}

const QVector<QPoint>& DrawingCanvas::getMPoints() const {
	return m_points;
}

QVector<QPointF>* DrawingCanvas::getPathBuffer() {
	return path_buffer;
}

const WorkSpace& DrawingCanvas::getWorkSpace() const {
	return workSpace;
}

void DrawingCanvas::clear() {
	m_points.clear();
	update();
}

TTT* const& DrawingCanvas::getTtt() const {
	return ttt;
}

void DrawingCanvas::closeEvent(QCloseEvent *event) {
	ttt->setIsGameOn(false);
}
