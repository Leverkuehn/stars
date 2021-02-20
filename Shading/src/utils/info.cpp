#include "info.h"

#include<GL\glew.h>

int getMaxVertexAttributesNumber()
{
	int nAttr;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
	return nAttr;
}