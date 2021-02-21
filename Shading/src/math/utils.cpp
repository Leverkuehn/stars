#include "utils.h"

color colorCreate(uint8 r, uint8 g, uint8 b)
{
	color result;
	result.r = r;
	result.g = g;
	result.b = b;

	return(result);
}

int colorEqual(color a, color b)
{
	return(a.r == b.r && a.g == b.g && a.b == b.b);
}

vec2i vec2iCreate(int32 x, int32 y)
{
	vec2i result;
	result.x = x;
	result.y = y;

	return(result);
}

vec2i vec2iSub(vec2i a, vec2i b)
{
	vec2i result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return(result);
}

vec2i vec2iAdd(vec2i a, vec2i b)
{
	vec2i result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return(result);
}

vec2i vec2iMul(vec2i a, float t)
{
	vec2i result;
	result.x = (int32)((float)a.x * t);
	result.y = (int32)((float)a.y * t);
	return(result);
}

float vec3fDot(vec3f a, vec3f b)
{
	return(a.x*b.x + a.y*b.y + a.z*b.z);
}

float crossVec2i(vec2i *a, vec2i *b)
{
	return((float)a->x * (float)b->y - (float)a->y * (float)b->y);
}

void swapVec2i(vec2i *v1, vec2i *v2)
{
	vec2i temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void swapi(int32 *a, int32 *b)
{
	int32 temp = *a;
	*a = *b;
	*b = temp;
}

vec3f colorToVec3f(color col)
{
	vec3f result;
	result = { (float)col.r, (float)col.g, (float)col.b };
	return result;
}

vec3f createVec3f(float x, float y, float z)
{
	vec3f result;
	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

color vec3fToColor(vec3f vec)
{
	color result;

	if (vec.x > 255)
		vec.x = 255;
	if (vec.y > 255)
		vec.y = 255;
	if (vec.z > 255)
		vec.z = 255;

	result = { (uint8)vec.x, (uint8)vec.y, (uint8)vec.z };
	return result;
}

void vec3fNormalize(vec3f *v)
{
	float length = sqrtf(vec3fDot(*v, *v));
	*v = { v->x / length, v->y / length , v->z / length};
}

int equal()
{
	return 0;
}

vec4f vec4fPoint(float x, float y, float z)
{
	vec4f result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 1;

	return result;
}

vec4f vec4fVector(float x, float y, float z)
{
	vec4f result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0;

	return result;
}

vec4f vec4fMulByVal(vec4f a, float value)
{
	vec4f result;
	result = { a.x * value, a.y * value, a.z * value, a.w * value };
	return result;
}

vec4f vec4fAdd(vec4f a, vec4f b)
{
	vec4f result;
	result = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
	return result;
}

vec4f vec4fSub(vec4f a, vec4f b)
{
	vec4f result;
	result = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return result;
}

vec4f vec4fAddValue(vec4f a, float value)
{
	vec4f result;
	result = { a.x + value, a.y + value, a.z + value, a.w + value };
	return result;
}

float vec4fDot(vec4f a, vec4f b)
{
	return(a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
}

void vec4fNormalize(vec4f *v)
{
	float length = sqrtf(vec4fDot(*v, *v));
	*v = { v->x / length, v->y / length , v->z / length , v->w / length };
}

vec4f vec4fNegate(vec4f v)
{
	return { -v.x, -v.y, -v.z, -v.w };
}

void vec4fPrint(vec4f *a)
{
	printf("[ ");
	printf("%f, ", a->x);
	printf("%f, ", a->y);
	printf("%f, ", a->z);
	printf("%f ", a->w);
	printf("]");
	printf("\n\n");
}

int getRnd(int max, int min)
{
	return(rand() % (max + 1 - min) + min);
}