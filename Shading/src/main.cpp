#include<GL\glew.h>
#include<glfw3.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define _USE_MATH_DEFINES
#include<math.h>

#include "math\matrices.h"

#include "utils\info.h"
#include "utils\io.h"

#include "core\shader.h"

#include "utils\vendor\stb_image.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>

#include "core/camera.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

//------------------ Setting up camera ----------------------

vec3f cameraPos = { 0.0f,  0.0f,  3.0f };
vec3f cameraFront = { 0.0f,  0.0f, -1.0f };
vec3f cameraUp = { 0.0f,  1.0f,  0.0f };

//-----------------------------------------------------------

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int screenW = 1280, screenH = 720;

float lastX = screenW/2.0f, lastY = screenH/2.0f;

bool firstMouse = true;

camera cam = coreCameraCreate({ 0.0f, 0.0f, 3.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f });

int main()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow *window = glfwCreateWindow(screenW, screenH, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glewInit();

	printf("Maximum of vertex attributes supported: %d\n", getMaxVertexAttributesNumber());

//------------------ Initializing texture----------------------

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	uint8 *data = stbi_load("src/textures/Marigold Blue Pattern By William Morris.jpg", &width, &height, &nrChannels, 0);
	if (!data)
		printf("Failed to load a texture\n");

	uint32 texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	data = stbi_load("src/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (!data)
		printf("Failed to load a texture\n");
	uint32 texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

//------------------ End --------------------------------------

	coreShader shader = coreShaderCreateFromVertexAndFragmentSource("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
	coreShaderBind(&shader);

	glUniform1i(glGetUniformLocation(shader.id, "tex1"), 0);
	glUniform1i(glGetUniformLocation(shader.id, "tex2"), 1);

//------------------ Initializing cube----------------------

	float cubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	};

	uint32 cubeVBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

//------------------ End -----------------------------------

	glEnable(GL_DEPTH_TEST);

	vec4f cubePositions[] = {
		{0.0f,  0.0f,  0.0f , 0.0f },
		{2.0f,  5.0f, -15.0f, 0.0f },
		{-1.5f, -2.2f, -2.5f, 0.0f },
		{-3.8f, -2.0f, -12.3, 0.0f },
		{2.4f, -0.4f, -3.5f , 0.0f },
		{-1.7f,  3.0f, -7.5f, 0.0f },
		{1.3f, -2.0f, -2.5f , 0.0f },
		{1.5f,  2.0f, -2.5f , 0.0f },
		{1.5f,  0.2f, -1.5f , 0.0f },
		{-1.3f,  1.0f, -1.5f, 0.0f },
	};

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);

		{
			const float radius = 10.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			mat4 view = coreCameraGetLookAtMatrix(&cam);

			mat4 projection = mat4Projection(toRadians(cam.zoom), (float)screenW / (float)screenH, 0.1f, 100.0f);

			coreShaderSetUniformMatrix4f(&shader, "view", &view);
			coreShaderSetUniformMatrix4f(&shader, "projection", &projection);
		}

		{
			glClear(GL_COLOR_BUFFER_BIT);
			coreShaderBind(&shader);
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);

			glBindVertexArray(cubeVAO);
			for (uint32 i = 0; i < 10; i++)
			{
				mat4 translation = mat4Translation(cubePositions[i]);
				float angle = 20.0f  * i + 5;
				mat4 model = mat4Mul(&translation, &mat4Rotation(angle * (float)glfwGetTime() / 20.0f, { 1.0f, 0.3f, 0.5f }));
		
				coreShaderSetUniformMatrix4f(&shader, "model", &model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);

	glfwTerminate();
	return(0);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	coreCameraProcessMouseMovement(&cam, xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	coreCameraProcessMouseScroll(&cam, yoffset);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		coreCameraProcessKeyboard(&cam, CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		coreCameraProcessKeyboard(&cam, CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		coreCameraProcessKeyboard(&cam, CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		coreCameraProcessKeyboard(&cam, CameraMovement::RIGHT, deltaTime);
}