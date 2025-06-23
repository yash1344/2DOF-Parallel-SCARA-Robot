/*
 * TriangleTTT.h
 *
 *  Created on: Jun 1, 2025
 *      Author: vagha
 */

#ifndef TTT_MYTRIANGLE_H_
#define TTT_MYTRIANGLE_H_
#include "../Shapes/Rectangle.h"

class MyTriangle: MyRectangle {
public:
	MyTriangle(Coordinate center, int size, float angle);
	virtual ~MyTriangle();
	virtual void draw(QPainter &painter, View viewType) const override;

	QVector<QPointF> getPath() const;

};

#endif /* TTT_MYTRIANGLE_H_ */
