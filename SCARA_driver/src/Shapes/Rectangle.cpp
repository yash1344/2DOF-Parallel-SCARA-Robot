/*
 * Rectangle.cpp
 *
 *  Created on: Apr 9, 2025
 *      Author: vagha
 */

#include "Rectangle.h"

#include <cmath>
#include <iostream>

using namespace std;

#include "../Utility.h"
MyRectangle::~MyRectangle() {
}

MyRectangle::MyRectangle(Coordinate leftTopCorner, int width, int height,
		float angle) :
		leftTopCorner(leftTopCorner), width(width), height(height), angle(angle) {

}

MyRectangle::MyRectangle(Line line, int height) :
		width(line.length()), height(height), angle(line.angles().first) {
	float x = line.getStart().X()
			+ ((height / 2) * cos(line.angles().first - d2r(-90)));
	float y = line.getStart().Y()
			- ((height / 2) * sin(line.angles().first - d2r(-90)));
	leftTopCorner = Coordinate(x, y, 0);
}

int MyRectangle::getHeight() const {
	return height;
}

void MyRectangle::setHeight(int height) {
	this->height = height;
}

Coordinate MyRectangle::getLeftBottomCorner() const {
	return leftTopCorner;
}

void MyRectangle::setLeftBottomCorner(const Coordinate &leftTopCorner) {
	this->leftTopCorner = leftTopCorner;
}

int MyRectangle::getWidth() const {
	return width;
}

float MyRectangle::getAngle() const {
	return angle;
}

void MyRectangle::setAngle(float angle) {
	this->angle = angle;
}

void MyRectangle::setCornerRadius(int cornerRadius = 0) {
	corner_radius = cornerRadius;
}

void MyRectangle::setWidth(int width) {
	this->width = width;
}

void MyRectangle::draw(QPainter &painter, View viewType) const {
	if (painterTransform) {
		painterTransform(painter);
	} else {
		// Custom brush (fill)
		QBrush brush(QColor(0, 0, 0, 50));
		brush.setStyle(Qt::BrushStyle::SolidPattern);
		painter.setBrush(brush);
	}

	painter.save();
	painter.translate(leftTopCorner.X(), leftTopCorner.Y());
	painter.rotate((int) round(r2d(-angle)));

	if (viewType == SIDE_VIEW) {
		painter.drawRoundedRect(0, 0, width, height, corner_radius,
				corner_radius, Qt::AbsoluteSize);
	} else {
		painter.drawRoundedRect(0, 0, width, height, corner_radius,
				corner_radius, Qt::AbsoluteSize);
	}
	painter.restore();
}

