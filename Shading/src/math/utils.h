#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef char		  int8;
typedef unsigned char uint8;
typedef int			  int32;
typedef unsigned int  uint32;

typedef struct color
{
	uint8 r, g, b;
} color;

typedef struct vec2i
{
	int32 x, y;
} vec2i;

typedef struct vec2f
{
	float x, y;
} vec2f;

typedef struct vec3f
{
	float x, y, z;
} vec3f;

typedef struct vec4f
{
	float x, y, z, w;
} vec4f;

color colorCreate(uint8 r, uint8 g, uint8 b);

int colorEqual(color a, color b);

vec2i vec2iCreate(int32 x, int32 y);

vec2i vec2iSub(vec2i a, vec2i b);

vec2i vec2iAdd(vec2i a, vec2i b);

vec2i vec2iMul(vec2i a, float t);

float vec3fDot(vec3f a, vec3f b);

float crossVec2i(vec2i *a, vec2i *b);

void swapVec2i(vec2i *v1, vec2i *v2);

void swapi(int32 *a, int32 *b);

vec3f colorToVec3f(color col);

vec3f createVec3f(float x, float y, float z);

color vec3fToColor(vec3f vec);

int equal();

vec4f vec4fPoint(float x, float y, float z);

vec4f vec4fVector(float x, float y, float z);

vec4f vec4fMulByVal(vec4f a, float value);

vec4f vec4fAdd(vec4f a, vec4f b);

vec4f vec4fSub(vec4f a, vec4f b);

vec4f vec4fAddValue(vec4f a, float value);

float vec4fDot(vec4f a, vec4f b);

void vec4fNormalize(vec4f *v);

vec4f vec4fNegate(vec4f v);

void vec4fPrint(vec4f *a);

int getRnd(int max, int min);

#endif
