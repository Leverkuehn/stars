#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	color = vec4(aVertexColor, 1.0);
	texCoord = aTexCoord;
}