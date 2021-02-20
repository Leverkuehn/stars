#version 330

in vec4 color;

out vec4 fragColor;

uniform vec3 u_Color;

void main()
{
	//fragColor = color;
	fragColor = vec4(u_Color, 1.0);
}