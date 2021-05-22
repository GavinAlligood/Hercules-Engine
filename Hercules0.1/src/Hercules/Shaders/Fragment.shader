#version 330 core

layout (location = 0) out vec4 color;

in vec2 TexCoord;

uniform vec4 inColor;
uniform sampler2D Texture;
uniform bool i;

void main()
{
	//for color
	if (i && true) { color = inColor; }
	else { color = texture(Texture, TexCoord); }

	//for texture
	//color = texture(Texture, TexCoord);
}