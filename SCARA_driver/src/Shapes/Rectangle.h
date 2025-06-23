/*
 * Rectangle.h
 *
 *  Created on: Apr 9, 2025
 *      Author: vagha
 */

#ifndef SHAPES_RECTANGLE_H_
#define SHAPES_RECTANGLE_H_
#include "Line.h"
#include "Shape.h"

class MyRectangle: public Shape {
	Coordinate leftTopCorner;
	int width, height;
	float angle;
	int corner_radius = 0;

public:
	MyRectangle(Coordinate leftTopCorner, int width, int height, float angle);
	MyRectangle(Line line, int height);
	virtual ~MyRectangle();
	virtual void draw(QPainter &painter, View viewType) const override;

	int getHeight() const;
	void setHeight(int height);
	Coordinate getLeftBottomCorner() const;
	void setLeftBottomCorner(const Coordinate &new_LeftBottomCorner);
	int getWidth() const;
	void setWidth(int width);
	float getAngle() const;
	void setAngle(float angle);
	void setCornerRadius(int cornerRadius);
};

#endif /* SHAPES_RECTANGLE_H_ */
