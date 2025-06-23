/*
 * WorkSpace.cpp
 *
 *  Created on: May 24, 2025
 *      Author: vagha
 */

#include "WorkSpace.h"

#include <algorithm>
#include <set>
#include "Utility.h"
using namespace std;
WorkSpace::WorkSpace(Coordinate system_center, float d, float l1, float l2) :
		system_center(system_center), d(d), l1_Left(l1), l2_Left(l2), l1_Right(
				l1), l2_Right(l2) {
	s_circle_left = Circle(
			Coordinate(system_center.X() - d / 2, system_center.Y(), 0),
			l2_Left - l1_Left);
	l_circle_left = Circle(
			Coordinate(system_center.X() - d / 2, system_center.Y(), 0),
			l2_Left + l1_Left);
	s_circle_right = Circle(
			Coordinate(system_center.X() + d / 2, system_center.Y(), 0),
			l2_Right - l1_Right);
	l_circle_right = Circle(
			Coordinate(system_center.X() + d / 2, system_center.Y(), 0),
			l2_Right + l1_Right);

	s_circle_left.setPainterTransform([](QPainter &painter) {
		QPen pen(Qt::PenStyle::DashLine);
		pen.setColor(QColor(0, 0, 0, 30));
		painter.setPen(pen);
		painter.setBrush(Qt::BrushStyle::NoBrush);
	});
	l_circle_left.setPainterTransform([](QPainter &painter) {
		QPen pen(Qt::PenStyle::DashLine);
		pen.setColor(QColor(0, 0, 0, 30));
		painter.setPen(pen);
		painter.setBrush(Qt::BrushStyle::NoBrush);
	});
	s_circle_right.setPainterTransform([](QPainter &painter) {
		QPen pen(Qt::PenStyle::DashLine);
		pen.setColor(QColor(0, 0, 0, 30));
		painter.setPen(pen);
		painter.setBrush(Qt::BrushStyle::NoBrush);
	});
	l_circle_right.setPainterTransform([](QPainter &painter) {
		QPen pen(Qt::PenStyle::DashLine);
		pen.setColor(QColor(0, 0, 0, 30));
		painter.setPen(pen);
		painter.setBrush(Qt::BrushStyle::NoBrush);
	});
}

WorkSpace::WorkSpace(Coordinate system_center, float d, float l1_Left,
		float l2_Left, float l1_Right, float l2_Right) :
		system_center(system_center), d(d), l1_Left(l1_Left), l2_Left(l2_Left), l1_Right(
				l1_Right), l2_Right(l2_Right) {

	s_circle_left = Circle(
			Coordinate(system_center.X() - d / 2, system_center.Y(), 0),
			l2_Left - l1_Left);
	l_circle_left = Circle(
			Coordinate(system_center.X() - d / 2, system_center.Y(), 0),
			l2_Left + l1_Left);
	s_circle_right = Circle(
			Coordinate(system_center.X() + d / 2, system_center.Y(), 0),
			l2_Right - l1_Right);
	l_circle_right = Circle(
			Coordinate(system_center.X() + d / 2, system_center.Y(), 0),
			l2_Right + l1_Right);
}

WorkSpace::~WorkSpace() {
}

float WorkSpace::getD() const {
	return d;
}

void WorkSpace::setD(float d) {
	this->d = d;
}

float WorkSpace::getL1Left() const {
	return l1_Left;
}

void WorkSpace::setL1Left(float l1Left) {
	l1_Left = l1Left;
}

float WorkSpace::getL1Right() const {
	return l1_Right;
}

void WorkSpace::setL1Right(float l1Right) {
	l1_Right = l1Right;
}

float WorkSpace::getL2Left() const {
	return l2_Left;
}

void WorkSpace::setL2Left(float l2Left) {
	l2_Left = l2Left;
}

float WorkSpace::getL2RIght() const {
	return l2_Right;
}

std::vector<int> WorkSpace::intersection_angle_arranged(const Circle &circle,
		std::optional<std::vector<Coordinate>> &points) const {
	std::vector<int> angles;

	Line line(circle.getCenter(), circle.getCenter());
	float angle;
	if (points.has_value()) {
		for (const auto &point : points.value()) {
			line = Line(circle.getCenter(), point);
			angle = makeAngleDeg_Posi(line.angles_D().first);

			angles.push_back(angle);
		}
	}
	std::sort(angles.begin(), angles.end());
	return angles;
}

void WorkSpace::setL2RIght(float l2RIght) {
	l2_Right = l2RIght;
}

void WorkSpace::draw(QPainter &painter, View viewType) const {
	painter.save();

	s_circle_left.draw(painter, View::SIDE_VIEW);
	l_circle_right.draw(painter, View::SIDE_VIEW);
	s_circle_right.draw(painter, View::SIDE_VIEW);
	l_circle_left.draw(painter, View::SIDE_VIEW);
	painter.restore();
	//intersection of large circles
	std::optional<std::vector<Coordinate>> is =
			l_circle_right.circleIntersection(l_circle_left);
	vector<int> l2l_left = intersection_angle_arranged(l_circle_left, is);
	vector<int> l2l_right = intersection_angle_arranged(l_circle_right, is);

	//intersection of small circles
	is = s_circle_left.circleIntersection(s_circle_right);
	vector<int> s2s_left = intersection_angle_arranged(s_circle_left, is);
	vector<int> s2s_right = intersection_angle_arranged(s_circle_right, is);

	//intersection of large-Right and small-Left circles
	is = l_circle_right.circleIntersection(s_circle_left);
	vector<int> l2s_right_large = intersection_angle_arranged(l_circle_right,
			is);
	vector<int> l2s_left_small = intersection_angle_arranged(s_circle_left, is);

	//intersection of large-Left and small-Right circles
	is = l_circle_left.circleIntersection(s_circle_right);
	vector<int> l2s_left_large = intersection_angle_arranged(l_circle_left, is);
	vector<int> l2s_right_small = intersection_angle_arranged(s_circle_right,
			is);

	if (l2l_left.size() == 2) {
		if (l2s_right_large.size() == 2) {
			Arc_custom arc(l_circle_right, l2l_right[0], l2s_right_large[0]);
			arc.draw(painter, View::SIDE_VIEW);

			arc.setFrom(l2l_right[1]);
			arc.setTo(l2s_right_large[1]);
			arc.draw(painter, View::SIDE_VIEW);

			if (s2s_left.size() == 2) {
				Arc_custom arc(s_circle_left, l2s_left_small[0], s2s_left[0]);
				arc.draw(painter, View::SIDE_VIEW);

				arc.setFrom(l2s_left_small[1]);
				arc.setTo(s2s_left[1]);
				arc.draw(painter, View::SIDE_VIEW);
			} else {
				Arc_custom arc(s_circle_left, l2s_left_small[0],
						l2s_left_small[1], false);
				arc.draw(painter, View::SIDE_VIEW);
			}
		} else {
			Arc_custom arc(l_circle_right, l2l_right[0], l2l_right[1]);
			arc.draw(painter, View::SIDE_VIEW);

			if (s2s_left.size() == 2) {
				Arc_custom arc(s_circle_left, s2s_left[0], s2s_left[1]);
				arc.draw(painter, View::SIDE_VIEW);
			} else {
				Arc_custom arc(s_circle_left, 0, 360);
				arc.draw(painter, View::SIDE_VIEW);
			}
		}
	}

	if (l2l_right.size() == 2) {
		if (l2s_left_large.size() == 2) {
			Arc_custom arc(l_circle_left, l2l_left[0], l2s_left_large[0]);
			arc.draw(painter, View::SIDE_VIEW);

			arc.setFrom(l2l_left[1]);
			arc.setTo(l2s_left_large[1]);
			arc.draw(painter, View::SIDE_VIEW);

			if (s2s_right.size() == 2) {
				Arc_custom arc(s_circle_right, l2s_right_small[0],
						s2s_right[0]);
				arc.draw(painter, View::SIDE_VIEW);

				arc.setFrom(l2s_right_small[1]);
				arc.setTo(s2s_right[1]);
				arc.draw(painter, View::SIDE_VIEW);
			} else {
				Arc_custom arc(s_circle_right, l2s_right_small[0],
						l2s_right_small[1]);
				arc.draw(painter, View::SIDE_VIEW);
			}
		} else {
			Arc_custom arc(l_circle_left, l2l_left[0], l2l_left[1], false);
			arc.draw(painter, View::SIDE_VIEW);

			if (s2s_right.size() == 2) {
				Arc_custom arc(s_circle_right, s2s_right[0], s2s_right[1], false);
				arc.draw(painter, View::SIDE_VIEW);
			} else {
				Arc_custom arc(s_circle_right, 0, 360, false);
				arc.draw(painter, View::SIDE_VIEW);
			}
		}
	}
}

const Coordinate& WorkSpace::getSystemCenter() const {
	return system_center;
}
