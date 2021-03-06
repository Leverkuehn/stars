#pragma once

#include <GL\glew.h>

#include "../utils/types.h"
#include "../math/matrices.h"

typedef struct coreShader
{
	uint32 id;
} coreShader;

coreShader coreShaderCreateFromVertexAndFragmentSource(const char *vertexSourceFilepath, const char *fragmentSourceFilepath);

void coreShaderBind(coreShader *shader);

void coreShaderSetUniform1f(coreShader *shader, const char *uniformName, float value);
void coreShaderSetUniform3f(coreShader *shader, const char *uniformName, vec3f value);
void coreShaderSetUniform4f(coreShader *shader, const char *uniformName, vec4f value);
void coreShaderSetUniformMatrix4f(coreShader *shader, const char *uniformName, mat4 *m);
