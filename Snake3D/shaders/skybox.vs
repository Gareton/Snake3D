#version 330 core

layout (location = 0) in vec3 vPos;

out vec3 fTexCoord;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	fTexCoord = vPos;
	gl_Position = (proj * vec4(mat3(view) * vPos, 1.0)).xyww;
}