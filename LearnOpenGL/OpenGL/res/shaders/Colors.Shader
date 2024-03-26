#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;
layout(location=1) in vec3 aNormal; // ������

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 transform;
uniform mat3 normalMat;     // ���߾���

void main()
{
    FragPos = vec3(model * aPos);
    Normal = normalMat * aNormal;

    gl_Position = transform * aPos;
};

#shader fragment
#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;

uniform vec4 objectColor;   // ������ɫ
uniform vec4 lightColor;    // ��Դ��ɫ
uniform vec3 lightPos;      // ��Դλ��
uniform vec3 viewPos;       // �����λ��

void main()
{
    // ������
    float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * lightColor;

    // ������
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff =max(dot(norm, lightDir), 0.0);
    vec4 diffuse= diff * lightColor;

    // �������
    float specularStrength = 0.5;   // ����ǿ��
    vec3 viewDir =normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32);
    vec4 specular = specularStrength * spec * lightColor;

    color = (ambient + diffuse + specular)*objectColor;
}