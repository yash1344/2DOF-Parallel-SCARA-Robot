/*
 * PersistentTrajectorySpeedManipulator.cpp
 *
 *  Created on: Jun 14, 2025
 *      Author: vagha
 */

#include "PersistentTrajectorySpeedManipulator.h"

#include <qnumeric.h>
#include <qpoint.h>
#include <cmath>
#include <iostream>
#include <utility>
#include <thread>

using namespace std::chrono;
using namespace std;

PersistentTrajectory_SpeedManipulator::PersistentTrajectory_SpeedManipulator(
		QVector<QPointF> *path, float derivativeLimit, float lengthStepSize) :
		path(path), derivativeLimit(derivativeLimit), lengthStepSize(
				lengthStepSize) {
}

PersistentTrajectory_SpeedManipulator::PersistentTrajectory_SpeedManipulator(
		QVector<QPointF> *path, float derivativeLimit, float lengthStepSize,
		QPoint startingPoint) :
		path(path), derivativeLimit(derivativeLimit), lengthStepSize(
				lengthStepSize), startingPoint(startingPoint) {
	path->push_front(startingPoint);
}

float PersistentTrajectory_SpeedManipulator::getDerivativeLimit() const {
	return derivativeLimit;
}

void PersistentTrajectory_SpeedManipulator::setDerivativeLimit(
		float derivativeLimit) {
	this->derivativeLimit = derivativeLimit;
}

PersistentTrajectory_SpeedManipulator::~PersistentTrajectory_SpeedManipulator() {
	path = nullptr;
	last_time.reset();
}

std::optional<pair<double_t, QPointF>> PersistentTrajectory_SpeedManipulator::getNewPoint() {
	using namespace std::chrono;

	auto now = high_resolution_clock::now();
	if (path == nullptr) {
		last_time = now;
		return std::nullopt;
	}

	// Initialize last_time if needed
	if (!last_time.has_value()) {
		last_time = now;
		if (!path->isEmpty())
			return make_pair(0, path->first());
		else
			return std::nullopt;
	}

	cout << endl << "path: ";
	for (const auto &point : *path) {
		cout << "(" << point.x() << ", " << point.y() << ")...";
	}

	// Compute elapsed ms
	auto elapsed_us = duration_cast<microseconds>(now - *last_time).count(); // @suppress("Method cannot be resolved") // @suppress("Invalid arguments") // @suppress("Symbol is not resolved")
	float elapsed = static_cast<float>(elapsed_us) / 1000.0f;
	if (elapsed <= 0 || derivativeLimit <= 0.0f) {
		last_time = now;
		return std::nullopt;  // or handle as you see fit
	}
	// Need at least two points to interpolate
	if (path->size() < 2) {
		last_time = now;
		return std::nullopt;
	}

	// Compute vector between first two points (floating)
	QPointF diffF = QPointF(path->at(1)) - QPointF(path->first());
	float length = std::hypot(diffF.x(), diffF.y());

	// How long *should* it take to cover this segment at our max speed?
	float required_ms = length / derivativeLimit;

	float parts = required_ms / static_cast<float>(elapsed);

	if (parts > 1.0f) {
		// advance fractionally along the segment
		QPointF stepF = diffF / parts;
		QPointF newPF = QPointF(path->first()) + stepF;

//		// Convert to QPoint by rounding (or floor/ceil as you prefer)
//		QPoint newP(qRound(newPF.x()), qRound(newPF.y()));

		(*path)[0] = newPF;
		last_time = now;
		return make_pair(static_cast<double_t>(elapsed), newPF); // return a QPoint, not a QPointF
	} else {
		// we can finish this segment this tick → consume it
		last_time = now;
		path->removeFirst();
		return path->isEmpty() ?
				std::nullopt :
				make_optional(
						make_pair(static_cast<double_t>(elapsed),
								path->first())); // @suppress("Invalid arguments")
	}
}

std::optional<pair<double_t, QPointF>> PersistentTrajectory_SpeedManipulator::getNewPoint2() {
	using namespace std::chrono;

	auto delayEnough = [this](float elapsed, float length) -> int {
		float required_delay = (length / derivativeLimit) * 1000;
//		cout << endl << "sleep_time..." << required_delay - elapsed;
		return (elapsed > required_delay) ? 0 : required_delay - elapsed;
	};

	auto now = high_resolution_clock::now();

	if (path == nullptr) {
		return std::nullopt;
	}

	// Initialize last_time if needed
	if (!last_time.has_value() && !path->isEmpty()) {
		last_time = now;
		return make_pair(0, path->first());
	}

//	cout << endl << "path..." << path->size();

	if (path->size() == 1) {
		return std::nullopt;
	}

	if (path->size() > 1) {
		// Compute vector between first two points (floating)
		QPointF diffF = QPointF(path->at(1)) - QPointF(path->first());
		float length = std::hypot(diffF.x(), diffF.y());

		if (length <= lengthStepSize) {
			auto elapsed_us =
					duration_cast<microseconds>(now - *last_time).count(); // @suppress("Method cannot be resolved") // @suppress("Invalid arguments") // @suppress("Symbol is not resolved")
			float elapsed = static_cast<float>(elapsed_us) / 1000.0f;

			//delay thread for required time
			auto time_to_pause = delayEnough(elapsed, length);
//			cout << endl << "sleep_time..." << time_to_pause;
			std::this_thread::sleep_for(chrono::milliseconds(time_to_pause));
			last_time = now;
			path->removeFirst();
			return make_pair(elapsed + time_to_pause, path->first());
		}

		if (length > lengthStepSize) {
			int inter_count = ceilf((length / lengthStepSize));

			QPointF newPoint = path->first() + (diffF / inter_count);
			path->removeFirst();
			path->push_front(newPoint);

			auto elapsed_us =
					duration_cast<microseconds>(now - *last_time).count(); // @suppress("Method cannot be resolved") // @suppress("Invalid arguments") // @suppress("Symbol is not resolved")
			float elapsed = static_cast<float>(elapsed_us) / 1000.0f;

			//delay thread for required time
			auto time_to_pause = delayEnough(elapsed, length / inter_count);
//			cout << endl << "sleep_time..." << time_to_pause;
			std::this_thread::sleep_for(chrono::milliseconds(time_to_pause));
			last_time = now;
			return make_pair(elapsed + time_to_pause, path->first());
		}
	}
	return std::nullopt;
}
