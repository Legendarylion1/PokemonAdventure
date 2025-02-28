#version 330 core

layout(location = 0) out vec4 FragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	vec4 texture = texture(tex0, texCoord);
	FragColor = vec4(texture.r + color.r, texture.g + color.g, texture.b + color.b, texture.a + color.a);
	
}