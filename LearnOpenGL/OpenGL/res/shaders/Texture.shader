#shader vertex
#version 330 core
        
layout(location=0) in vec4 position;
layout(location=1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position=position;
    v_TexCoord=texCoord;
};

#shader fragment
#version 330 core
out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;   // Shader文件中定义uniform
uniform sampler2D u_Texture;

void main()
{
    vec4 texCoord=texture(u_Texture, v_TexCoord);
    //color=u_Color;      // 使用uniform变量
    color=texCoord;
}