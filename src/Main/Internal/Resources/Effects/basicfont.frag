#version 150

in vec2 TexCoord;
in vec4 Color;
out vec4 outColor;

uniform sampler2D gSampler;

void main()
{
	vec4 vTexColor = texture2D(gler, TexCoord);
    outColor = vTexColor * Color;
}

