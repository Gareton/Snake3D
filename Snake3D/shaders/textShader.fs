#version 330 core

in vec2 fTexCoord;
out vec4 FragColor;

uniform vec3 color;
uniform sampler2D texture0;

void main()
{
	FragColor = vec4(color, texture(texture0, fTexCoord).r);
	//FragColor = vec4(fTexCoord, 0.0f, 1.0f);
}