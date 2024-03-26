#shader vertex
#version 330 core
        
layout(location=0) in vec4 aPos;
layout(location=1) in vec3 aNormal; // ������
layout(location=2) in vec2 aTexCoords;  // ��������

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 transform;
uniform mat3 normalMat;     // ���߾���

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

struct Material{
    sampler2D diffuse;      // ��������ͼ
    sampler2D specular;     // ���淴����ͼ
    float shininess;	// Ӱ�쾵��߹��ɢ��/�뾶
    };


struct Light {
    vec3 position;      // ��Դλ��

    vec4 ambient;       // ��Դ��������ɫ
    vec4 diffuse;       // ��Դ��������ɫ
    vec4 specular;      // ��Դ����߹���ɫ
    };

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;       // �����λ��
uniform Light light;        // ��Դ
uniform Material material;  // ����

void main()
{
    // ������
    vec4 ambient = light.ambient * texture(material.diffuse, TexCoords);

    // ������
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff =max(dot(norm, lightDir), 0.0);
    vec4 diffuse= light.diffuse * diff * texture(material.diffuse, TexCoords);

    // �������
    vec3 viewDir =normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
    vec4 specular = light.specular * spec * texture(material.specular,TexCoords);

    color = ambient + diffuse + specular;
}