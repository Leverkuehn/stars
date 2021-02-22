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

mat4 mat4Rotation(float radians, vec3f axis)
{
	/*template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<4, 4, T, Q> rotate(mat<4, 4, T, Q> const& m, T angle, vec<3, T, Q> const& v)
	{
		T const a = angle;
		T const c = cos(a);
		T const s = sin(a);

		vec<3, T, Q> axis(normalize(v));
		vec<3, T, Q> temp((T(1) - c) * axis);

		mat<4, 4, T, Q> Rotate;
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		mat<4, 4, T, Q> Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}*/

	const float c = cosf(radians);
	const float s = sinf(radians);

	vec3fNormalize(&axis);
	//vec3f temp = vec3fMulByVal(axis, 1.0f - c);

	mat4 rotate = mat4Identity();

	/*rotate.data[0] = c + temp.x * axis.x;
	rotate.data[1] = temp.x * axis.y + s * axis.z;
	rotate.data[2] = temp.x * axis.z - s * axis.y;

	rotate.data[4] = temp.y * axis.x - s * axis.z;
	rotate.data[5] = c + temp.y * axis.y;
	rotate.data[6] = temp.y * axis.z + s * axis.x;

	rotate.data[8] = temp.z * axis.x + s * axis.y;
	rotate.data[9] = temp.z * axis.y - s * axis.x;
	rotate.data[10] = c + temp.z * axis.z;*/

	const float cc = 1.0f - c;

	rotate.data[0] = c + axis.x * axis.x * cc;
	rotate.data[1] = axis.x * axis.y * cc - axis.z * s;
	rotate.data[2] = axis.x * axis.z * cc + axis.y * s;

	rotate.data[4] = axis.y * axis.x * cc + axis.z * s;
	rotate.data[5] = c + axis.y * axis.y * cc;
	rotate.data[6] = axis.y * axis.z * cc - axis.x * s;

	rotate.data[8] = axis.z * axis.x * cc - axis.y * s;
	rotate.data[9] = axis.z * axis.y * cc + axis.x * s;
	rotate.data[10] = c + axis.z * axis.z * cc;

	return rotate;
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

mat4 mat4Projection(float FoV, float aspect, float near, float far)
{
	mat4 result = {};

	float halfTan = tanf(FoV / 2.0f);

	result.data[0]  = 1.0f / (aspect * halfTan);
	result.data[5]  = 1.0f / halfTan;
	result.data[10] = -(far + near) / (far - near);
	result.data[11] = -(2 * far * near) / (far - near);
	result.data[14] = -1;

	return result;
}

mat4 mat4LookAt(vec3f position, vec3f target, vec3f up)
{
	vec3f direction = vec3fNormalizeCopy(vec3fSub(position, target));
	vec3f right = vec3fNormalizeCopy(vec3fCross(up, direction));
	
	vec3f cameraUp = vec3fCross(direction, right);

	mat4 lookAt = mat4Identity();

	lookAt.data[0]  = right.x;
	lookAt.data[1]  = right.y;
	lookAt.data[2]  = right.z;
	lookAt.data[3]  = vec3fDot(vec3fNegate(position), right);

	lookAt.data[4]  = cameraUp.x;
	lookAt.data[5]  = cameraUp.y;
	lookAt.data[6]  = cameraUp.z;
	lookAt.data[7]  = vec3fDot(vec3fNegate(position), cameraUp);

	lookAt.data[8]  = direction.x;
	lookAt.data[9]  = direction.y;
	lookAt.data[10] = direction.z;
	lookAt.data[11] = vec3fDot(vec3fNegate(position), direction);

	return lookAt;
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