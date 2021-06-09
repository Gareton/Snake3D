#version 330 core

in vec2 fBorderCoord;
in float fRatio;

out vec4 FragColor;

void main()
{
	vec3 color;
	float lbx = 0.2f;
	float ubx = 1.0f - lbx;
	float lby = lbx * fRatio;
	float uby = 1.0f - lby;
	
	if(fBorderCoord.x <= lbx || fBorderCoord.x >= ubx
	|| fBorderCoord.y <= lby || fBorderCoord.y >= uby)
		color = vec3(0.0f, 0.0f, 0.0f);
	else
		color = vec3(1.0f, 0.136f, 0.938f);

	FragColor = vec4(color, 1.0f);
}