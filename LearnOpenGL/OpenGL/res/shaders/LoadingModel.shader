#shader vertex
#version 330 core
        
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 transform;
uniform mat3 normalMat;     // 法线矩阵

void main()
{
    FragPos = vec3(model * vec4(aPos,1.0));
    Normal = normalMat * aNormal;
    TexCoords = aTexCoord;

    gl_Position = transform * vec4(aPos, 1.0);
};

#shader fragment
#version 330 core

struct Light{
    vec3 position;      // 光源位置
    vec3 direction;     // 光源方向
    float cutOff;       // 聚光的内切光角
    float outerCutOff;  // 聚光的外切光角

    vec4 ambient;       // 光源环境光颜色
    vec4 diffuse;       // 光源漫反射颜色
    vec4 specular;      // 光源镜面高光颜色

    // 计算衰减配置的三项
    float constant;     // 常数项
    float linear;       // 一次项
    float quadratic;    // 二次项
    };

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;       // 摄像机位置
uniform Light light;        // 光源

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{
     // 环境光
    vec4 ambient = light.ambient * texture(texture_normal1, TexCoords);

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff =max(dot(norm, lightDir), 0.0);
    vec4 diffuse= light.diffuse * diff * texture(texture_diffuse1, TexCoords);

    // 镜面光照
    vec3 viewDir =normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32f);
    vec4 specular = light.specular * spec * texture(texture_specular1,TexCoords);

    // 聚光
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   

    color = ambient + diffuse + specular;
}