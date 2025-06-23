/*
 * Arc.h
 *
 *  Created on: May 24, 2025
 *      Author: vagha
 */

#ifndef SHAPES_ARCCUSTOM_H_
#define SHAPES_ARCCUSTOM_H_
#include <qpainterpath.h>

#include "Circle.h"

class Arc_custom: Circle {
private:
	int from, to;
	bool clockwise;

public:
	Arc_custom(Coordinate center, float radius, int from, int to,
			bool clockwise = true);
	Arc_custom(Circle circle, int from, int to, bool clockwise = true);
	virtual ~Arc_custom();

	virtual void draw(QPainter &painter, View viewType) const;
	int getFrom() const;
	void setFrom(int from);
	int getTo() const;
	void setTo(int to);
};

#endif /* SHAPES_ARCCUSTOM_H_ */
