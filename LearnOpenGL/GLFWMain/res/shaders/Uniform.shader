#shader vertex
#version 330 core
        
layout(location=0) in vec4 position;
void main()
{
    gl_Position=position;
};

#shader fragment
#version 330 core
out vec4 color;
uniform vec4 u_Color;   // Shader文件中定义uniform

void main()
{
    color = u_Color;      // 使用uniform变量
}