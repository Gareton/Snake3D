#version 330 core

in vec2 fBorderCoord;

out vec4 FragColor;

void main()
{	
	float minAbsX = min(abs(fBorderCoord.x), abs(fBorderCoord.x - 1.0f));
	float minAbsY = min(abs(fBorderCoord.y), abs(fBorderCoord.y - 1.0f));
	float intensivity = min(minAbsX, minAbsY);
	
	if(intensivity > 0.5f)
		intensivity = 1.0f;

	if((fBorderCoord.x >= 0.0f && fBorderCoord.x <= 1.0f)
	&& (fBorderCoord.y >= 0.0f && fBorderCoord.y <= 1.0f))
		FragColor = vec4(vec3(1.0f, 0.136f, 0.938f) * intensivity, 1.0f);
	else
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}