#include "shader.h"

#define internal static

#include <stdio.h>

#include "../utils/io.h"

internal uint32 internal_createShaderFromVertexAndFragmentSource(char *vertexSrc, char *fragmentSrc)
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
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	}

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return(programID);
}

coreShader coreShaderCreateFromVertexAndFragmentSource(const char *vertexSourceFilepath, const char *fragmentSourceFilepath)
{
	coreShader shader;

	char *vertexSource = ReadStringFromFile(vertexSourceFilepath);
	char *fragmentSource = ReadStringFromFile(fragmentSourceFilepath);
	shader.id = internal_createShaderFromVertexAndFragmentSource(vertexSource, fragmentSource);

	return shader;
}

void coreShaderBind(coreShader *shader)
{
	glUseProgram(shader->id);
}

void coreShaderSetUniform1f(coreShader *shader, const char *uniformName, float value)
{
	coreShaderBind(shader);
	glUniform1f(glGetUniformLocation(shader->id, uniformName), value);
}

void coreShaderSetUniform3f(coreShader *shader, const char *uniformName, vec3f value)
{
	coreShaderBind(shader);
	glUniform3f(glGetUniformLocation(shader->id, uniformName), value.x, value.y, value.z);
}

void coreShaderSetUniform4f(coreShader *shader, const char *uniformName, vec4f value)
{
	coreShaderBind(shader);
	glUniform4f(glGetUniformLocation(shader->id, uniformName), value.x, value.y, value.z, value.w);
}

void coreShaderSetUniformMatrix4f(coreShader *shader, const char *uniformName, mat4 *m)
{
	coreShaderBind(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader->id, uniformName), 1, GL_TRUE, (float*)m);
}