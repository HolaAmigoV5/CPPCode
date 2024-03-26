#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;
layout(location=1) in vec3 aNormal; // 法向量

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 transform;
uniform mat3 normalMat;     // 法线矩阵

void main()
{
    FragPos = vec3(model * aPos);
    Normal = normalMat * aNormal;

    gl_Position = transform * aPos;
};

#shader fragment
#version 330 core

struct Material{
    vec4 ambient;		// 定义当前材质在环境光下表面反射的是什么颜色
    vec4 diffuse;		// 定义当前材质在漫反射光照下表面颜色
    vec4 specular;		// 设置当前材质镜面高光颜色
    float shininess;	// 影响镜面高光的散射/半径
    };


struct Light{
    vec3 position;      // 光源位置

    vec4 ambient;       // 光源环境光颜色
    vec4 diffuse;       // 光源漫反射颜色
    vec4 specular;      // 光源镜面高光颜色
    };

out vec4 color;

in vec3 Normal;
in vec3 FragPos;

uniform Material material;  // 材质
uniform Light light;        // 光源

uniform vec3 lightPos;      // 光源位置
uniform vec3 viewPos;       // 摄像机位置

void main()
{
    // 环境光
    vec4 ambient = light.ambient * material.ambient;

    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff =max(dot(norm, lightDir), 0.0);
    vec4 diffuse= light.diffuse * (diff * material.diffuse);

    // 镜面光照
    vec3 viewDir =normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
    vec4 specular = light.specular * (spec * material.specular);

    color = ambient + diffuse + specular;
}