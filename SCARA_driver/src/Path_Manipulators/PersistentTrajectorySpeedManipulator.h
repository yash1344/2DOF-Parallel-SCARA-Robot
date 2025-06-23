/*
 * PersistentTrajectorySpeedManipulator.h
 *
 *  Created on: Jun 14, 2025
 *      Author: vagha
 */

#ifndef PATH_MANIPULATORS_PERSISTENTTRAJECTORYSPEEDMANIPULATOR_H_
#define PATH_MANIPULATORS_PERSISTENTTRAJECTORYSPEEDMANIPULATOR_H_

#include <qpoint.h>
#include <QVector>
#include <chrono>
#include <optional>
#include <utility>

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
class PersistentTrajectory_SpeedManipulator {

private:
	QVector<QPointF> *path = nullptr;
	float derivativeLimit;	// in pixels/sec
	float lengthStepSize;
	QPoint startingPoint;
	std::optional<TimePoint> last_time;

public:
	PersistentTrajectory_SpeedManipulator(QVector<QPointF> *path,
			float derivativeLimit, float lengthStepSize, QPoint startingPoint);
	PersistentTrajectory_SpeedManipulator(QVector<QPointF> *path,
			float derivativeLimit, float lengthStepSize);
	virtual ~PersistentTrajectory_SpeedManipulator();

	float getDerivativeLimit() const;
	void setDerivativeLimit(float derivativeLimit);

	std::optional<std::pair<double_t, QPointF>> getNewPoint();
	std::optional<std::pair<double_t, QPointF>> getNewPoint2();
};

#endif /* PATH_MANIPULATORS_PERSISTENTTRAJECTORYSPEEDMANIPULATOR_H_ */
