/*
 * TriangleTTT.cpp
 *
 *  Created on: Jun 1, 2025
 *      Author: vagha
 */

#include "MyTriangle.h"

MyTriangle::MyTriangle(Coordinate center, int size, float angle) :
		MyRectangle(center - size / 2, size, size, angle) {
}

MyTriangle::~MyTriangle() {
}

void MyTriangle::draw(QPainter &painter, View viewType) const {
	float x = getLeftBottomCorner().X() + (getWidth() / 2) * cos(getAngle());
	float y = getLeftBottomCorner().Y() - (getWidth() / 2) * sin(getAngle());
	QPoint topCenter = QPoint(x, y);

	x = getLeftBottomCorner().X() + getHeight() * sin(getAngle());
	y = getLeftBottomCorner().Y() + getHeight() * cos(getAngle());
	QPoint leftBottom = QPoint(x, y);

	x = leftBottom.x() + getWidth() * cos(getAngle());
	y = leftBottom.y() - getWidth() * sin(getAngle());
	QPoint rightBottom = QPoint(x, y);

	painter.save();
	if (painterTransform) {
		painterTransform(painter);
	} else {
		// Custom brush (fill)
		painter.setPen(
				QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	}

	painter.drawLine(topCenter, leftBottom);
	painter.drawLine(leftBottom, rightBottom);
	painter.drawLine(rightBottom, topCenter);
	painter.restore();
}

QVector<QPointF> MyTriangle::getPath() const {
	QVector<QPointF> path;

	// Calculate triangle corners
	float x = getLeftBottomCorner().X() + (getWidth() / 2) * cos(getAngle());
	float y = getLeftBottomCorner().Y() - (getWidth() / 2) * sin(getAngle());
	QPointF topCenter(x, y);

	x = getLeftBottomCorner().X() + getHeight() * sin(getAngle());
	y = getLeftBottomCorner().Y() + getHeight() * cos(getAngle());
	QPointF leftBottom(x, y);

	x = leftBottom.x() + getWidth() * cos(getAngle());
	y = leftBottom.y() - getWidth() * sin(getAngle());
	QPointF rightBottom(x, y);

	path.append(topCenter);
	path.append(leftBottom);
	path.append(rightBottom);
	path.append(topCenter);

	return path;
}
/*std::vector<Coordinate> MyTriangle::getPath(unsigned int segments) const {
 std::vector<Coordinate> path;

 if (segments < 3)
 segments = 3; // Minimum 3 points

 // Calculate triangle corners
 float x = getLeftBottomCorner().X() + (getWidth() / 2) * cos(getAngle());
 float y = getLeftBottomCorner().Y() - (getWidth() / 2) * sin(getAngle());
 QPointF topCenter(x, y);

 x = getLeftBottomCorner().X() + getHeight() * sin(getAngle());
 y = getLeftBottomCorner().Y() + getHeight() * cos(getAngle());
 QPointF leftBottom(x, y);

 x = leftBottom.x() + getWidth() * cos(getAngle());
 y = leftBottom.y() - getWidth() * sin(getAngle());
 QPointF rightBottom(x, y);

 // Convert to Coordinate
 Coordinate A(topCenter.x(), topCenter.y(), 0);
 Coordinate B(leftBottom.x(), leftBottom.y(), 0);
 Coordinate C(rightBottom.x(), rightBottom.y(), 0);

 // Edge lengths
 float lenAB = std::hypot(B.X() - A.X(), B.Y() - A.Y());
 float lenBC = std::hypot(C.X() - B.X(), C.Y() - B.Y());
 float lenCA = std::hypot(A.X() - C.X(), A.Y() - C.Y());
 float totalLength = lenAB + lenBC + lenCA;

 // Distribute segments proportionally
 unsigned int segAB = std::round(segments * lenAB / totalLength);
 unsigned int segBC = std::round(segments * lenBC / totalLength);
 unsigned int segCA = segments - segAB - segBC; // Ensure total is exact

 // Helper lambda to interpolate points between two Coordinates
 auto interpolate = [](const Coordinate &p1, const Coordinate &p2,
 unsigned int count) {
 std::vector<Coordinate> pts;
 for (unsigned int i = 0; i < count; ++i) {
 float t = static_cast<float>(i) / count;
 float x = (1 - t) * p1.X() + t * p2.X();
 float y = (1 - t) * p1.Y() + t * p2.Y();
 pts.emplace_back(x, y, 0);
 }
 return pts;
 };

 // Build the path
 auto part1 = interpolate(A, B, segAB);
 auto part2 = interpolate(B, C, segBC);
 auto part3 = interpolate(C, A, segCA);

 // Concatenate all parts
 path.insert(path.end(), part1.begin(), part1.end());
 path.insert(path.end(), part2.begin(), part2.end());
 path.insert(path.end(), part3.begin(), part3.end());

 return path;
 }*/
