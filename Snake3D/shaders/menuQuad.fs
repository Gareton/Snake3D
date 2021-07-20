#version 330 core

in vec2 fTexCoord;

uniform sampler2D tex;

out vec4 fColor; 

void main()
{
	fColor = texture(tex, fTexCoord);
}