#include "Utility.h"
#include <cmath>

constexpr double PI = std::acos(-1.0);
using namespace std;

// Function definitions
float d2r(float degree) {
	return degree * (PI / 180);
}

float r2d(float rad) {
	return rad * (180 / PI);
}

float limit(float minVal, float value, float maxVal) {
	value = wrapAngleRad(value);
	return std::max(minVal, std::min(value, maxVal));
}

float wrapAngleRad(float angle) {
	angle = fmodf(angle, d2r(360));
	while (angle > d2r(180))
		angle -= d2r(360);
	while (angle <= d2r(-180))
		angle += d2r(360);
	return angle;
}

float wrapAngleDeg(float angle) {
	angle = d2r(angle);
	return r2d(wrapAngleRad(angle));
}

float makeAngleRad_Posi(float angle) {
	if (angle > 0) {
		return angle;
	} else {
		return angle + d2r(360);
	}
}

float makeAngleDeg_Posi(float angle) {
	return r2d(makeAngleRad_Posi(d2r(angle)));
}
