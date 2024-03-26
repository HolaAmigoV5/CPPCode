#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;
layout(location=1) in vec3 aNormal; // 法向量
layout(location=2) in vec2 aTexCoords;  // 纹理坐标

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 transform;
uniform mat3 normalMat;     // 法线矩阵

void main()
{
    FragPos = vec3(model * aPos);
    Normal = normalMat * aNormal;
    TexCoords=aTexCoords;

    gl_Position = transform * aPos;
};

#shader fragment
#version 330 core
out vec4 color;

// 材质
struct Material{
    sampler2D diffuse;      // 漫反射贴图
    sampler2D specular;     // 镜面反射贴图
    float shininess;	// 影响镜面高光的散射/半径
    };

// 直接光
struct DirLight {
    vec3 direction;     // 光源方向
	
    vec4 ambient;       // 光源环境光颜色
    vec4 diffuse;       // 光源漫反射颜色
    vec4 specular;      // 光源镜面高光颜色
};

// 点光
struct PointLight {
    vec3 position;      // 光源位置
    
    // 计算衰减配置的三项
    float constant;     // 常数项
    float linear;       // 一次项
    float quadratic;    // 二次项
	
    vec4 ambient;       // 光源环境光颜色
    vec4 diffuse;       // 光源漫反射颜色
    vec4 specular;      // 光源镜面高光颜色
};

// 聚光
struct SpotLight {
    vec3 position;      // 光源位置
    vec3 direction;     // 光源方向
    float cutOff;       // 聚光的内切光角
    float outerCutOff;  // 聚光的外切光角
  
    // 计算衰减配置的三项
    float constant;     // 常数项
    float linear;       // 一次项
    float quadratic;    // 二次项
  
    vec4 ambient;       // 光源环境光颜色
    vec4 diffuse;       // 光源漫反射颜色
    vec4 specular;      // 光源镜面高光颜色
};

#define NR_POINT_LIGHTS 4

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;       // 摄像机位置
uniform DirLight dirLight;  
uniform PointLight pointLights[NR_POINT_LIGHTS]; 
uniform SpotLight spotLight; 
uniform Material material;  // 材质

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec4 result = CalcDirLight(dirLight, norm, viewDir);

    for(int i=0; i< NR_POINT_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
     }

     result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
     color = result;
}

// calculates the color when using a directional light.
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec4 ambient = light.ambient * texture(material.diffuse, TexCoords);
    vec4 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords);
    vec4 specular = light.specular * spec * texture(material.specular, TexCoords);
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec4 ambient = light.ambient * texture(material.diffuse, TexCoords);
    vec4 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords);
    vec4 specular = light.specular * spec * texture(material.specular, TexCoords);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec4 ambient = light.ambient * texture(material.diffuse, TexCoords);
    vec4 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords);
    vec4 specular = light.specular * spec * texture(material.specular, TexCoords);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

