#include<Windows.h>
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

typedef unsigned int uint32;

static float EPSILON = FLT_EPSILON * 15000;

uint32 createComputeShader(const char *filename)
{
	GLuint rayShader = glCreateShader(GL_COMPUTE_SHADER);
	char *rayShaderSource = ReadStringFromFile(filename);
	glShaderSource(rayShader, 1, &rayShaderSource, NULL);
	glCompileShader(rayShader);
	
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(rayShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(rayShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	GLuint rayProgram = glCreateProgram();
	glAttachShader(rayProgram, rayShader);
	glLinkProgram(rayProgram);

	glGetProgramiv(rayProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(rayProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(rayShader);

	return rayProgram;
}

uint32 createTestVAO()
{
	float vertices[] = {
		-1.f, -1.f, 0.0f,
		-1.f,  1.f, 0.0f,
		1.f,  1.f, 0.0f,
		1.f,  1.f, 0.0f,
		1.f, -1.f, 0.0f,
		-1.f, -1.f, 0.0f,
	};

	uint32 VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return(VAO);
}

int main()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	int screenW = 640, screenH = 480;

	GLFWwindow *window = glfwCreateWindow(screenW, screenH, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewInit();

	printf("Maximum of vertex attributes supported: %d", getMaxVertexAttributesNumber());

	float vertices[] = {  
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	coreShader shader = coreCreateShaderFromVertexAndFragmentSource("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
	coreBindShader(&shader);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.f, 0.f, 0.f, 1.0f);

		{
			glClear(GL_COLOR_BUFFER_BIT);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			coreBindShader(&shader);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return(0);
}