/*
 * DrawingCanvas.h
 *
 *  Created on: May 22, 2025
 *      Author: vagha
 */

#ifndef DRAWINGCANVAS_H_
#define DRAWINGCANVAS_H_
#include <qwidget.h>
#include <QWidget>
#include <QVector>
#include <QPoint>
#include <qpainterpath.h>
#include <optional>

#include "Communication/TCPsend.h"
#include "CursorSender.h"
#include "Shapes/Arccustom.h"
#include "TTT.h"
#include "WorkSpace.h"

class DrawingCanvas: public QWidget {
Q_OBJECT
public:
	explicit DrawingCanvas(TTT *ttt, QVector<QPointF> *path_buffer,
			QWidget *parent = nullptr);
	Coordinate getPoint();
	TTT* const& getTtt() const;
	const QVector<QPoint>& getMPoints() const;
	QVector<QPointF>* getPathBuffer();
	const WorkSpace& getWorkSpace() const;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

public slots:
	void clear();

	// DrawingCanvas.h
signals:
	void pointSelected(Coordinate point);

private:
	QVector<QPoint> m_points;
	QVector<QPointF> *path_buffer;
	TTT *ttt;
//	QPainterPath m_path;
	bool m_isDrawing;
	bool picking_a_point = false;
	std::thread picking_point_thread;
	Coordinate picked_point;
	std::mutex path_mutex;

	WorkSpace workSpace;
};

#endif /* DRAWINGCANVAS_H_ */
