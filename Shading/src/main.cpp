
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

typedef unsigned int uint32;

static float EPSILON = FLT_EPSILON * 15000;

char* ReadStringFromFile(const char *filename)
{
	char *buffer = 0;
	FILE *file = fopen(filename, "r");
	long length;
	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);

		buffer = (char*)malloc(length);
		memset(buffer, 0, length);

		if (buffer)
			fread(buffer, 1, length, file);

		fclose(file);
	}

	return(buffer);
}

uint32 CreateProgram(char *vertexSrc, char *fragmentSrc)
{
	uint32 programID = 0, vertexID = 0, fragmentID = 0;

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexSrc, NULL);
	glCompileShader(vertexID);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return(programID);
}

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

	char *vertexSrc = ReadStringFromFile("src/shaders/vertex.glsl");
	char *fragmentSrc = ReadStringFromFile("src/shaders/fragment.glsl");
	uint32 program = CreateProgram(vertexSrc, fragmentSrc);
	glUseProgram(program);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.f, 0.f, 0.f, 1.0f);

		{
			glClear(GL_COLOR_BUFFER_BIT);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glUseProgram(program);
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