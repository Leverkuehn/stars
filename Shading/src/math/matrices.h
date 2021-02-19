#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <string.h>
#include "utils.h" 
#include "geometry.h"

typedef struct mat4
{
	float data[16];
} mat4;

typedef struct mat3
{
	float data[9];
} mat3;

typedef struct mat2
{
	float data[4];
} mat2;

float mat2Determinant(mat2 *a);

mat2 mat3Submatrix(mat3 *a, uint8 row, uint8 col);

float mat3Minor(mat3 *a, uint8 row, uint8 col);

float mat3Cofactor(mat3 *a, uint8 row, uint8 col);

float mat3Determinant(mat3 *a);

int mat3SetElement(mat3 *a, int i, int j, float value);

int mat4SetElement(mat4 *a, int i, int j, float value);

mat4 mat4Identity();

mat4 mat4Zero();

mat4 mat4Transpose(mat4 *a);

mat4 mat4Mul(mat4 *a, mat4 *b);

vec4f  mat4MulByVec4f(mat4 *a, vec4f *b);

mat3 mat4Submatrix(mat4 *a, uint8 row, uint8 col);

float mat4Minor(mat4 *a, uint8 row, uint8 col);

float mat4Cofactor(mat4 *a, uint8 row, uint8 col);

float mat4Determinant(mat4 *a);

mat4 mat4Inverse(mat4 *a);

mat4 mat4Translation(vec4f v);

mat4 mat4Scaling(vec4f v);

mat4 mat4RotationX(float radians);

mat4 mat4RotationY(float radians);

mat4 mat4RotationZ(float radians);

mat4 mat4Shearing(float xy, float xz, float yx, float yz, float zx, float zy);

void mat4Print(mat4 *a);

void mat3Print(mat3 *a);

void mat2Print(mat2 *a);

#endif 



