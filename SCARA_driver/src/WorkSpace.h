/*
 * WorkSpace.h
 *
 *  Created on: May 24, 2025
 *      Author: vagha
 */

#ifndef WORKSPACE_H_
#define WORKSPACE_H_
#include "Shapes/Arccustom.h"
#include "Shapes/Shape.h"

class WorkSpace: Shape {
private:
	Coordinate system_center;
	float d;	//distance between two motors
	float l1_Left;	//active Left-arm length
	float l2_Left;	//passive Left-arm length
	float l1_Right;	//active Right-arm length
	float l2_Right;	//passive Right-arm length

	Circle s_circle_left, s_circle_right;	//small inner circles
	Circle l_circle_left, l_circle_right;	//large outer circles

	std::vector<int> intersection_angle_arranged(const Circle &circle,
			std::optional<std::vector<Coordinate>> &points) const;

public:
	WorkSpace(Coordinate system_center, float d, float l1, float l2);
	WorkSpace(Coordinate system_center, float d, float l1_Left, float l2_Left,
			float l1_Right, float l2_Right);
	virtual ~WorkSpace();
	virtual void draw(QPainter &painter, View viewType) const override;
	float getD() const;
	void setD(float d);
	float getL1Left() const;
	void setL1Left(float l1Left);
	float getL1Right() const;
	void setL1Right(float l1Right);
	float getL2Left() const;
	void setL2Left(float l2Left);
	float getL2RIght() const;
	void setL2RIght(float l2RIght);
	const Coordinate& getSystemCenter() const;
};

#endif /* WORKSPACE_H_ */
