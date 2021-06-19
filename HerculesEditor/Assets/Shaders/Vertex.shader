#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

//when i work on the 2d renderer i need to only have one model,
//no reason to have one for 3d and 2d since you cant use 2d and 3d at the same time
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;
uniform mat3 normalCalc;

uniform bool mode;

void main()
{
	if (mode && true) { gl_Position = projection * view * model * vec4(aPos, 1.0); TexCoord = aTexCoord; }
	else { gl_Position = projection * transform * vec4(aPos, 1.0); }

	FragPos = vec3(model * vec4(aPos, 1.0));

	Normal = normalCalc * aNormal;
}