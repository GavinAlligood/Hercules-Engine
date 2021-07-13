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

uniform int PointLightNR;
uniform PointLight pointLights[2];

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform float shininess;

//uniform Light light;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	//float ambientStrength = 0.7;
	//vec3 ambient = light.ambientStrength * lightColor;

	//vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(light.position - FragPos); //for point and spot lights
	////vec3 lightDir = normalize(-light.direction); //for directional lights
	//float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * lightColor;

	//float specularStrength = 0.5;
	//vec3 viewDir = normalize(viewPos - FragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	//vec3 specular = specularStrength * spec * lightColor;

	////remove this for directional
	//float theta = dot(lightDir, normalize(-light.direction));
	//float epsilon = light.cutOff - light.outerCutOff;
	//float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	////ambient *= intensity;
	//diffuse *= intensity;
	//specular *= intensity;

	//float distance = length(light.position - FragPos);
	//float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//ambient *= attenuation;
	//diffuse *= attenuation;
	//specular *= attenuation;

	//vec3 result = (ambient + diffuse + specular) * objectColor;

	//color = vec4(result, 1.0) * texture(Texture, TexCoord);
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	// phase 1: Directional lighting
	//vec3 result = CalcDirLight(dirLight, norm, viewDir);
	// phase 2: Point lights
	for (int i = 0; i < PointLightNR; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	// phase 3: Spot light
	//result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

	color = vec4(result, 1.0);
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