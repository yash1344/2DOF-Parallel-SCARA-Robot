#ifndef UTILITY_H
#define UTILITY_H

// Function declarations (prototypes)
float d2r(float degree);
float r2d(float rad);
float limit(float minVal, float value, float maxVal);
float wrapAngleRad(float angle);
float wrapAngleDeg(float angle);
float makeAngleRad_Posi(float angle);
float makeAngleDeg_Posi(float angle);

#endif // UTILITY_H
