#include "matrices.h"

float mat2Determinant(mat2 *a)
{
	return a->data[0] * a->data[3] - a->data[1] * a->data[2];
}

mat2 mat3Submatrix(mat3 *a, uint8 row, uint8 col)
{
	mat2 result;
	for (uint8 i = 0, iMat2 = 0; i < 3; i++)
	{
		if (i == row)
			continue;

		for (uint8 j = 0, jMat2 = 0; j < 3; j++)
		{
			if (j == col)
				continue;

			result.data[jMat2 + iMat2 * 2] = a->data[j + i * 3];
			jMat2++;
		}

		iMat2++;
	}

	return result;
}

float mat3Minor(mat3 *a, uint8 row, uint8 col)
{
	mat2 temp = mat3Submatrix(a, row, col);

	return mat2Determinant(&temp);
}

float mat3Cofactor(mat3 *a, uint8 row, uint8 col)
{
	float result = mat3Minor(a, row, col);

	if ((row + col + 1) % 2 == 0)
		return -result;

	return result;
}

float mat3Determinant(mat3 *a)
{
	float result = 0;

	for (uint8 i = 0; i < 3; i++)
		result += a->data[i] * mat3Cofactor(a, 0, i);

	return result;
}

int mat3SetElement(mat3 *a, int i, int j, float value)
{
	if (i > 2 || i < 0 || j > 2 || j < 0 || a == NULL)
		return -1;

	a->data[j + i * 3] = value;
	return 1;
}

int mat4SetElement(mat4 *a, int i, int j, float value)
{
	if (i > 3 || i < 0 || j > 3 || j < 0 || a == NULL)
		return -1;

	a->data[j + i * 4] = value;
	return 1;
}

mat4 mat4Identity()
{
	mat4 result;
	memset(&result, 0, sizeof(result));

	mat4SetElement(&result, 0, 0, 1);
	mat4SetElement(&result, 1, 1, 1);
	mat4SetElement(&result, 2, 2, 1);
	mat4SetElement(&result, 3, 3, 1);

	return result;
}

mat4 mat4Zero()
{
	mat4 result;
	memset(&result, 0, sizeof(result));

	return result;
}

mat4 mat4Transpose(mat4 *a)
{
	mat4 result;

	for (uint8 j = 0; j < 4; j++)
		for (uint8 i = 0; i < 4; i++)
			result.data[j + i * 4] = a->data[i + j * 4];

	return result;
}

mat4 mat4Mul(mat4 *a, mat4 *b)
{
	mat4 result;

	for (uint8 i = 0; i < 4; i++)
	{
		for (uint8 j = 0; j < 4; j++)
		{
			result.data[j + i * 4] = a->data[0 + i * 4] * b->data[j] + a->data[1 + i * 4] * b->data[j + 4] + a->data[2 + i * 4] * b->data[j + 8] + a->data[3 + i * 4] * b->data[j + 12];
		}
	}

	return result;
}

vec4f  mat4MulByVec4f(mat4 *a, vec4f *b)
{
	vec4f result;
	void *result_ptr = &result;

	for (uint8 i = 0; i < 4; i++)
		((float*)result_ptr)[i] = a->data[0 + i * 4] * b->x + a->data[1 + i * 4] * b->y + a->data[2 + i * 4] * b->z + a->data[3 + i * 4] * b->w;

	return result;
}

mat3 mat4Submatrix(mat4 *a, uint8 row, uint8 col)
{
	mat3 result;
	for (uint8 i = 0, iMat3 = 0; i < 4; i++)
	{
		if (i == row)
			continue;

		for (uint8 j = 0, jMat3 = 0; j < 4; j++)
		{
			if (j == col)
				continue;

			result.data[jMat3 + iMat3 * 3] = a->data[j + i * 4];
			jMat3++;
		}

		iMat3++;
	}

	return result;
}

float mat4Minor(mat4 *a, uint8 row, uint8 col)
{
	mat3 temp = mat4Submatrix(a, row, col);

	return mat3Determinant(&temp);
}

float mat4Cofactor(mat4 *a, uint8 row, uint8 col)
{
	float result = mat4Minor(a, row, col);

	if ((row + col + 1) % 2 == 0)
		return -result;

	return result;
}

float mat4Determinant(mat4 *a)
{
	float result = 0;

	for (uint8 i = 0; i < 4; i++)
		result += a->data[i] * mat4Cofactor(a, 0, i);

	return result;
}

mat4 mat4Inverse(mat4 *a)
{
	mat4 result;

	for (uint8 i = 0; i < 4; i++)
		for (uint8 j = 0; j < 4; j++)
			result.data[j + i * 4] = mat4Cofactor(a, i, j);

	result = mat4Transpose(&result);

	float determinant = mat4Determinant(a);
	for (uint8 i = 0; i < 16; i++)
		result.data[i] /= determinant;

	return result;
}

mat4 mat4Translation(vec4f v)
{
	mat4 result = mat4Identity();

	result.data[3] = v.x;
	result.data[7] = v.y;
	result.data[11] = v.z;
	result.data[15] = 1;

	return  result;
}

mat4 mat4Scaling(vec4f v)
{
	mat4 result = mat4Zero();

	result.data[0] = v.x;
	result.data[5] = v.y;
	result.data[10] = v.z;
	result.data[15] = 1;

	return result;
}

mat4 mat4RotationX(float radians)
{
	mat4 result = mat4Identity();

	result.data[5] = cosf(radians);
	result.data[6] = -sinf(radians);
	result.data[9] = sinf(radians);
	result.data[10] = cosf(radians);

	return result;
}

mat4 mat4RotationY(float radians)
{
	mat4 result = mat4Identity();

	result.data[0] = cosf(radians);
	result.data[2] = sinf(radians);
	result.data[8] = -sinf(radians);
	result.data[10] = cosf(radians);

	return result;
}

mat4 mat4RotationZ(float radians)
{
	mat4 result = mat4Identity();

	result.data[0] = cosf(radians);
	result.data[1] = -sinf(radians);
	result.data[4] = sinf(radians);
	result.data[5] = cosf(radians);

	return result;
}

mat4 mat4Shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	mat4 result = mat4Identity();

	result.data[1] = xy;
	result.data[2] = xz;
	result.data[4] = yx;
	result.data[6] = yz;
	result.data[8] = zx;
	result.data[9] = zy;

	return result;
}

void mat4Print(mat4 *a)
{
	for (uint8 i = 0; i < 4; i++)
	{
		for (uint8 j = 0; j < 4; j++)
		{
			printf("A[%u][%u] = %5f ", i, j, a->data[j + i * 4]);
		}
		printf("\n");
	}
	printf("\n");
}

void mat3Print(mat3 *a)
{
	for (uint8 i = 0; i < 3; i++)
	{
		for (uint8 j = 0; j < 3; j++)
		{
			printf("A[%u][%u] = %f ", i, j, a->data[j + i * 3]);
		}
		printf("\n");
	}
	printf("\n");
}

void mat2Print(mat2 *a)
{
	for (uint8 i = 0; i < 2; i++)
	{
		for (uint8 j = 0; j < 2; j++)
		{
			printf("A[%u][%u] = %f ", i, j, a->data[j + i * 2]);
		}
		printf("\n");
	}
	printf("\n");
}