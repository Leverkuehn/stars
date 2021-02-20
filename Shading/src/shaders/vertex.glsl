#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 VertexColor;

out vec4 color;

void main()
{
	gl_Position = vec4(pos, 1.0);
	color = vec4(VertexColor, 1.0);
}