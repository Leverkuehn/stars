#pragma once

#include "../utils/types.h"

#include <GL\glew.h>

typedef struct coreShader
{
	uint32 id;
} coreShader;

coreShader coreCreateShaderFromVertexAndFragmentSource(const char *vertexSourceFilepath, const char *fragmentSourceFilepath);

void coreBindShader(coreShader *shader);

