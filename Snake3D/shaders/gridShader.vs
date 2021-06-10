#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vBorderCoord;

out vec3 fragColor;
out vec2 fBorderCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	fBorderCoord = vBorderCoord;
	gl_Position = proj * view * model * vec4(vPos, 1.0);
}