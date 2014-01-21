#version 150

in vec2 position;
in vec2 texcoord;
in vec4 color;
out vec2 TexCoord;
out vec4 Color;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
	Texcoord = texcoord;
	Color = color;
}
