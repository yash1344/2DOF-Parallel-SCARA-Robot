/*
 * Circle.cpp
 *
 *  Created on: Mar 30, 2025
 *      Author: vagha
 */

#include "Circle.h"
Circle::Circle(Coordinate center, float radius) :
		radius(radius), center(center) {
	updateBottomLeft();
}

Circle::~Circle() {
}

Coordinate Circle::closestPoint_2_origin() const {
	Line line2Origin(Coordinate(0, 0, 0), center);
	return line2Origin.cut_or_extend(radius, END).getEnd();
}

void Circle::draw(QPainter &painter, View viewType) const {
	if (painterTransform) {
		painterTransform(painter);
	} else {
		// Custom brush (fill)
		QBrush brush(QColor(0, 0, 0, 50));
		brush.setStyle(Qt::BrushStyle::SolidPattern);
		painter.setBrush(brush);
	}

	//as painter is mirrored...
	if (viewType == SIDE_VIEW) {
		painter.drawEllipse(bottomLeft.X(), bottomLeft.Y(), radius * 2,
				radius * 2);
	} else {
		painter.drawEllipse(bottomLeft.X(), bottomLeft.Z(), radius * 2,
				radius * 2);
	}
}

void Circle::updateBottomLeft() {
	bottomLeft = Coordinate(center.X() - radius, center.Y() - radius,
			center.Z() - radius);
}

Coordinate Circle::getBottomLeft() const {
	return bottomLeft;
}

Coordinate Circle::getCenter() const {
	return center;
}

float Circle::getRadius() const {
	return radius;
}

std::optional<std::vector<Coordinate>> Circle::circleIntersection(
		const Circle &c2) const {

	float x0 = this->center.X();
	float y0 = this->center.Y();
	float x1 = c2.center.X();
	float y1 = c2.center.Y();
	float r0 = this->radius;
	float r1 = c2.radius;

	double dx = x1 - x0;
	double dy = y1 - y0;
	double d = std::sqrt(dx * dx + dy * dy);

	// No intersection: the circles are separate or one is inside the other
	if (d > r0 + r1 || d < std::abs(r0 - r1)) {
		return std::nullopt;
	}

	// Coincident circles: infinite points (returning empty to indicate special case)
	if (d == 0 && r0 == r1) {
		return std::vector<Coordinate> { }; // or std::nullopt if you prefer
	}

	// Find a and h
	double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
	double h = std::sqrt(r0 * r0 - a * a);

	// Find P2, the point where the line through the circle intersection points crosses the line between the circle centers
	double x2 = x0 + a * (dx) / d;
	double y2 = y0 + a * (dy) / d;

	// Intersection points
	double rx = -dy * (h / d);
	double ry = dx * (h / d);

	Coordinate p1(x2 + rx, y2 + ry, 0);
	Coordinate p2(x2 - rx, y2 - ry, 0);

	// If h == 0, the circles touch at one point
	if (h == 0) {
		return std::vector<Coordinate> { p1 };
	} else {
		return std::vector<Coordinate> { p1, p2 };
	}
}

//std::vector<Coordinate> Circle::getPath(unsigned int segments) const {
//	std::vector<Coordinate> path;
//	path.reserve(segments);
//
//	for (unsigned int i = 0; i < segments; ++i) {
//		float angle = 2 * M_PI * i / segments;
//		float x = center.X() + radius * std::cos(angle);
//		float y = center.Y() + radius * std::sin(angle);
//		path.emplace_back(x, y, 0);
//	}
//
//	return path;
//}

QVector<QPointF> Circle::getPath(float maxChord) const {
	// avoid weirdness for extremely small circles
	if (maxChord <= 0.0f)
		maxChord = 1.0f;

	// compute how many segments so each chord <= maxChord
	float circumference = 2.0f * M_PI * radius;
	unsigned int segments = std::max(3u,                  // at least a triangle
			static_cast<unsigned int>(std::ceil(circumference / maxChord)));

	QVector<QPointF> path;
	path.reserve(segments);

	for (unsigned int i = 0; i < segments; ++i) {
		float angle = 2.0f * M_PI * float(i) / float(segments);
		float x = center.X() + radius * std::cos(angle);
		float y = center.Y() + radius * std::sin(angle);
		path.emplace_back(x, y);
	}

	return path;
}

Circle::Circle() {
}
