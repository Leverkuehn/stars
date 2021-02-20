#version 330

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
	//fragColor = texture(tex, texCoord) * color;
	fragColor = mix(texture(tex1, texCoord), texture(tex2, texCoord), 0.5);
}