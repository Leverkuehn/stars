#pragma once

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