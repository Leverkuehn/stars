#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>

#include "utils.h"

float vec3fLength(vec3f a);

vec3f vec3fSub(vec3f a, vec3f b);

vec3f vec3fAdd(vec3f a, vec3f b);
vec3f vec3fAddValue(vec3f a, float value);

vec3f vec3fMul(vec3f a, vec3f b);

vec3f vec3fMulByVal(vec3f a, float value);

vec4f vec4fCross(vec4f a, vec4f b);

float vec4fLength(vec4f v);

color clamp(vec3f col);

#endif
