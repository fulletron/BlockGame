#version 150 core

in vec2 Texcoord;
in vec4 Color;
out vec4 outColor;
uniform sampler2D tex;

void main() 
{
	float temp = texture2D(tex, Texcoord).r;
	outColor = vec4(Color.r, Color.g, Color.b, temp);
}