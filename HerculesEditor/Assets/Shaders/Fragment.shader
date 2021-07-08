#version 330 core

out vec4 color;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 inColor;

uniform sampler2D Texture;

struct Light {
	vec3 position;
	vec3 direction;

	float cutOff;
	float outerCutOff;
	
	float constant;
	float linear;
	float quadratic;
};

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform float shininess;

uniform Light light;

void main()
{
	float ambientStrength = 0.7;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * spec * lightColor;

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	//ambient *= intensity;
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	color = vec4(result, 1.0) * texture(Texture, TexCoord);
}