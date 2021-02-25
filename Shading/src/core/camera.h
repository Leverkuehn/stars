#pragma once

#include "../math/matrices.h"

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

typedef struct camera
{
	vec3f position;
	vec3f front;
	vec3f up;
	vec3f right;
	vec3f worldUp;

	float pitch;
	float yaw;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;
} camera;

camera coreCameraCreate(vec3f position, vec3f up, vec3f front);

mat4 coreCameraGetLookAtMatrix(camera *c);

void coreCameraProcessKeyboard(camera *c, CameraMovement direction, float deltaTime);
void coreCameraProcessMouseMovement(camera *c, float xoffset, float yoffset);
void coreCameraProcessMouseScroll(camera *c, float yoffset);
