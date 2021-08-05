#version 450 core

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 color2;

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

	float ambientStrength;

	float constant;
	float linear;
	float quadratic;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//currently 0 point lights in scene
//#define PointLightNR 0
//uniform PointLight pointLights[PointLightNR];

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform float shininess;

//uniform Light light;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	//Directional lighting
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
	//for (int i = 0; i < PointLightNR; i++)
		//result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	//spotlight
	//result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

	color = vec4(result, 1.0) * texture(Texture, TexCoord);
	color2 = vec4(0.8, 0.2, 0.3, 1.0) * texture(Texture, TexCoord);
	//color2 = 50;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	// combine results
	vec3 ambient = light.ambient * objectColor;
	vec3 diffuse = light.diffuse * diff * objectColor;
	vec3 specular = light.specular * spec * objectColor;
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
		light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * objectColor;
	vec3 diffuse = light.diffuse * diff * objectColor;
	vec3 specular = light.specular * spec * objectColor;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}