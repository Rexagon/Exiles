#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoords;

uniform vec2 uWindowSize;

out vec2 fTexCoords;

void main() 
{
	gl_Position.x = 2.0 * vPosition.x / uWindowSize.x - 1.0;
	gl_Position.y = 1.0 - 2.0 * vPosition.y / uWindowSize.y;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fTexCoords = vTexCoords;
}
