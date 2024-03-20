#version 450 core

layout (location = 0) in vec3 a_Position;	// 顶点位置
layout (location = 1) in vec4 a_Color;		// 顶点颜色
layout (location = 2) in vec2 a_TexCoord;	// 顶点纹理坐标
layout (location = 3) in float a_TexIndex;	// 顶点纹理索引

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1.0f);
}