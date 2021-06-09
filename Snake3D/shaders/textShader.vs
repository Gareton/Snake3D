#version 330 core

layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vTexCoord;

out vec2 fTexCoord;

uniform mat4 proj;
uniform mat4 model;

void main()
{
	fTexCoord = vTexCoord;
	gl_Position = proj * model * vec4(vPos, 0.0f, 1.0f);
}