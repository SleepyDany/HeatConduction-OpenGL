#version 330 core
layout (location = 0) in vec3 aPosition;

uniform vec3 uColor;

out vec3 color;

void main()
{
	gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
	color = uColor;
}