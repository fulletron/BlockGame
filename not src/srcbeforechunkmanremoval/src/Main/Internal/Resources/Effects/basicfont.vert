#version 150 core

in vec2 position;
in vec2 texcoord;
in vec4 color;

out vec2 Texcoord;
out vec4 Color;

void main() 
{
	Color = color;
	Texcoord = texcoord;
	gl_Position = vec4(position, 0.0, 1.0);
}