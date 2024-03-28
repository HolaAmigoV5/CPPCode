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
uniform mat3 normalMat;     // ���߾���

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
    vec3 position;      // ��Դλ��
    vec3 direction;     // ��Դ����
    float cutOff;       // �۹�����й��
    float outerCutOff;  // �۹�����й��

    vec4 ambient;       // ��Դ��������ɫ
    vec4 diffuse;       // ��Դ��������ɫ
    vec4 specular;      // ��Դ����߹���ɫ

    // ����˥�����õ�����
    float constant;     // ������
    float linear;       // һ����
    float quadratic;    // ������
    };

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;       // �����λ��
uniform Light light;        // ��Դ

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

void main()
{
     // ������
    vec4 ambient = light.ambient * texture(texture_normal1, TexCoords);

    // ������
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff =max(dot(norm, lightDir), 0.0);
    vec4 diffuse= light.diffuse * diff * texture(texture_diffuse1, TexCoords);

    // �������
    vec3 viewDir =normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32f);
    vec4 specular = light.specular * spec * texture(texture_specular1,TexCoords);

    // �۹�
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