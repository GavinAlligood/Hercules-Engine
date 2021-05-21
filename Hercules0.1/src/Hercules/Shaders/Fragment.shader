#version 330 core

layout (location = 0) out vec4 color;

in vec2 TexCoord;

uniform vec4 inColor;

uniform sampler2D Texture;

void main()
{
	//for color
	//color = inColor;

	//for texture
	color = texture(Texture, TexCoord);
}