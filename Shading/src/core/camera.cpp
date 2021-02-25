#include "camera.h"

#define internal static

internal void coreCameraUpdateVectors_internal(camera *c)
{
	vec3f front;
	front.x = cosf(toRadians(c->yaw)) * cosf(toRadians(c->pitch));
	front.y = sinf(toRadians(c->pitch));
	front.z = sinf(toRadians(c->yaw)) * cosf(toRadians(c->pitch));
	c->front = vec3fNormalizeCopy(front);

	c->right = vec3fNormalizeCopy(vec3fCross(c->front, c->worldUp)); 
	c->up = vec3fNormalizeCopy(vec3fCross(c->right, c->front));
}

camera coreCameraCreate(vec3f position, vec3f up, vec3f front)
{
	camera result;

	result.position = position;
	result.worldUp = up;
	result.front = front;
	result.pitch = 0.0f;
	result.yaw = -90.0f;
	result.movementSpeed = 2.5f;
	result.mouseSensitivity = 0.1f;
	result.zoom = 45.0f;

	coreCameraUpdateVectors_internal(&result);

	return result;
}

mat4 coreCameraGetLookAtMatrix(camera *c)
{
	return mat4LookAt(c->position, vec3fAdd(c->position, c->front), c->up);
}

void coreCameraProcessKeyboard(camera *c, CameraMovement direction, float deltaTime)
{
	float velocity = c->movementSpeed * deltaTime;
	if (direction == FORWARD)
		c->position = vec3fAdd(c->position, vec3fMulByVal(c->front, velocity));
	if (direction == BACKWARD)
		c->position = vec3fSub(c->position, vec3fMulByVal(c->front, velocity));
	if (direction == LEFT)
		c->position = vec3fSub(c->position, vec3fMulByVal(c->right, velocity));
	if (direction == RIGHT)
		c->position = vec3fAdd(c->position, vec3fMulByVal(c->right, velocity));
	if (direction == UP)
		c->position = vec3fAdd(c->position, vec3fMulByVal(c->up, velocity));
	if (direction == DOWN)
		c->position = vec3fSub(c->position, vec3fMulByVal(c->up, velocity));
}

void coreCameraProcessMouseMovement(camera *c, float xoffset, float yoffset)
{
	xoffset *= c->mouseSensitivity;
	yoffset *= c->mouseSensitivity;

	c->yaw += xoffset;
	c->pitch += yoffset;

	if (c->pitch > 89.0f)
		c->pitch = 89.0f;
	if (c->pitch < -89.0f)
		c->pitch = -89.0f;

	coreCameraUpdateVectors_internal(c);
}

void coreCameraProcessMouseScroll(camera *c, float yoffset)
{
	c->zoom -= (float)yoffset;
	if (c->zoom < 1.0f)
		c->zoom = 1.0f;
	if (c->zoom > 45.0f)
		c->zoom = 45.0f;
}