#version 330

in vec2 fTexCoords;

uniform vec4 uColor;

void main()
{
	gl_FragColor = uColor;
}
