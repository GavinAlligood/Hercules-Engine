#version 330 core

layout (location = 0) out vec4 color;

in vec2 TexCoord;

uniform vec4 inColor;
uniform sampler2D Texture;
uniform bool UseColor;

void main()
{
	//for color
	//if (UseColor && true) { color = inColor; }
	//else { color = texture(Texture, TexCoord); }
	color = inColor * texture(Texture, TexCoord);
}