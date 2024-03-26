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

struct Material{
    vec4 ambient;		// ���嵱ǰ�����ڻ������±��淴�����ʲô��ɫ
    vec4 diffuse;		// ���嵱ǰ����������������±�����ɫ
    vec4 specular;		// ���õ�ǰ���ʾ���߹���ɫ
    float shininess;	// Ӱ�쾵��߹��ɢ��/�뾶
    };


struct Light{
    vec3 position;      // ��Դλ��

    vec4 ambient;       // ��Դ��������ɫ
    vec4 diffuse;       // ��Դ��������ɫ
    vec4 specular;      // ��Դ����߹���ɫ
    };

out vec4 color;

in vec3 Normal;
in vec3 FragPos;

uniform Material material;  // ����
uniform Light light;        // ��Դ

uniform vec3 lightPos;      // ��Դλ��
uniform vec3 viewPos;       // �����λ��

void main()
{
    // ������
    vec4 ambient = light.ambient * material.ambient;

    // ������
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff =max(dot(norm, lightDir), 0.0);
    vec4 diffuse= light.diffuse * (diff * material.diffuse);

    // �������
    vec3 viewDir =normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
    vec4 specular = light.specular * (spec * material.specular);

    color = ambient + diffuse + specular;
}