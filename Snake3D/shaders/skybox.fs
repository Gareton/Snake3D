#version 330 core

in vec3 fTexCoord;

uniform samplerCube tex;

out vec4 FragColor;

void main()
{
	FragColor = vec4(texture(tex, fTexCoord).rgb, 1.0);
}