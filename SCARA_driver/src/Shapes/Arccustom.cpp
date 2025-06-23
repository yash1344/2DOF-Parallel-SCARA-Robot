/*
 * Arc.cpp
 *
 *  Created on: May 24, 2025
 *      Author: vagha
 */

#include "Arccustom.h"

#include "../Utility.h"
using namespace std;
Arc_custom::Arc_custom(Coordinate center, float radius, int from, int to,
		bool clockwise) :
		Circle(center, radius), from(from), to(to), clockwise(clockwise) {

}

Arc_custom::Arc_custom(Circle circle, int from, int to, bool clockwise) :
		Circle(circle), from(from), to(to), clockwise(clockwise) {
}

Arc_custom::~Arc_custom() {
}

int Arc_custom::getFrom() const {
	return from;
}

void Arc_custom::setFrom(int from) {
	this->from = from;
}

int Arc_custom::getTo() const {
	return to;
}

void Arc_custom::setTo(int to) {
	this->to = to;
}

void Arc_custom::draw(QPainter &painter, View viewType) const {
	QRect arcRect = QRect(QPoint(center.X() - radius, center.Y() - radius),
			QSize(radius * 2, radius * 2));
	QPainterPath path;

	float startX = center.X() + (radius * cos(d2r(from)));
	float startY = center.Y() - (radius * sin(d2r(from)));
	Coordinate temp(startX, startY, 0);
	path.moveTo(startX, startY);
	if (clockwise) {
		path.arcTo(arcRect, from, to - from);
	} else {
		path.arcTo(arcRect, from, -(360 - (to - from)));
	}

	painter.drawPath(path);
}

