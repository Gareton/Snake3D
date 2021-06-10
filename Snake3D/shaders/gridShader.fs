#version 330 core

in vec2 fBorderCoord;

out vec4 FragColor;

void main()
{	
	if((fBorderCoord.x >= 0.0f && fBorderCoord.x <= 1.0f)
	&& (fBorderCoord.y >= 0.0f && fBorderCoord.y <= 1.0f))
		FragColor = vec4(1.0f, 0.136f, 0.938f, 1.0f);
	else
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}