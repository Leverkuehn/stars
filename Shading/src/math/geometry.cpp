#include "geometry.h"

float vec3fLength(vec3f a)
{
	return(sqrt(vec3fDot(a, a)));
}

vec3f vec3fSub(vec3f a, vec3f b)
{
	vec3f result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return(result);
}

vec3f vec3fAdd(vec3f a, vec3f b)
{
	vec3f result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return(result);
}

vec3f vec3fAddValue(vec3f a, float value)
{
	vec3f result;
	result.x = a.x + value;
	result.y = a.y + value;
	result.z = a.z + value;
	return(result);
}

vec3f vec3fMul(vec3f a, vec3f b)
{
	vec3f result;
	result = { a.x*b.x, a.y*b.y, a.z*b.z };
	return result;
}

vec3f vec3fMulByVal(vec3f a, float value)
{
	vec3f result;
	result = { a.x*value, a.y*value, a.z*value };
	return result;
}

vec4f vec4fCross(vec4f a, vec4f b)
{
	return vec4fVector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float vec4fLength(vec4f v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

color clamp(vec3f col)
{
	color result;
	result = { (uint8)fminf(255, fmaxf(0, (float)col.x)), (uint8)fminf(255, fmaxf(0, (float)col.y)), (uint8)fminf(255, fmaxf(0, (float)col.z)) };
	return result;
}