#shader vertex
#version 330 core

// 从顶点缓冲区获取数据
layout(location=0) in vec4 position;
layout(location=1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;    // 模型视图投影矩阵

void main()
{
    gl_Position = u_MVP * position;    // 设置顶点位置
    v_TexCoord = texCoord;             // 将纹理坐标输出到着色器管道的下一个阶段
};

#shader fragment
#version 330 core

layout(location=0) out vec4 color;

in vec2 v_TexCoord;

// 从CPU中拿到两个uniform
uniform vec4 u_Color;   // Shader文件中定义uniform
uniform sampler2D u_Texture;

void main()
{
    vec4 texCoord=texture(u_Texture, v_TexCoord);   // 使用纹理坐标，对纹理进行采样
    color = texCoord;   // 输出从纹理采样中得到的颜色到output color
}