#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "utils.h"

float vec3fLength(vec3f a);

vec3f vec3fNormalizeCopy(vec3f v);

vec3f vec3fSub(vec3f a, vec3f b);

vec3f vec3fAdd(vec3f a, vec3f b);
vec3f vec3fAddValue(vec3f a, float value);

vec3f vec3fMul(vec3f a, vec3f b);

vec3f vec3fMulByVal(vec3f a, float value);

vec3f vec3fNegate(vec3f v);

vec3f vec3fCross(vec3f a, vec3f b);

vec4f vec4fCross(vec4f a, vec4f b);

float vec4fLength(vec4f v);

color clamp(vec3f col);

float toRadians(float degrees);

#endif
