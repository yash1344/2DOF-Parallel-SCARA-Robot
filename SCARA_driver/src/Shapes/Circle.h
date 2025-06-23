/*
 * Circle.h
 *
 *  Created on: Mar 30, 2025
 *      Author: vagha
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_
#include <optional>

#include "../Coordinate.h"
#include "Shape.h"
#include "Line.h"

class Circle: public Shape {
protected:
	float radius;
	Coordinate center;
	Coordinate bottomLeft;

	void updateBottomLeft();

public:
	Circle();
	Circle(Coordinate center, float radius);
	virtual ~Circle();
	Coordinate closestPoint_2_origin() const;
	virtual void draw(QPainter &painter, View viewType) const override;

	std::optional<std::vector<Coordinate>> circleIntersection(
			const Circle &c2) const;

	QVector<QPointF> getPath(float maxChord) const;

	Coordinate getBottomLeft() const;
	Coordinate getCenter() const;
	float getRadius() const;
};
#endif /* CIRCLE_H_ */
