#version 330 core
out vec4 FragColor;

uniform bool wall;
void main()
{
	if(wall)
		FragColor = vec4(1.f, 1.f, 1.f, 1.f);
	else
		FragColor = vec4(0.f, 0.f, 0.f, 1.f);
}