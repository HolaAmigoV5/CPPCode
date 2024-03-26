#pragma once

#include <iostream>
#include <GL\glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// ����ASSERT(x)���������x����false�����ж�
#define ASSERT(x) if(!(x)) __debugbreak();

// ����GLCall(x)��������x���а�װ
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__,__LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
    void Clear() const;

	/// <summary>
	/// ʹ��������ͼ
	/// </summary>
	/// <param name="va">��������</param>
	/// <param name="ib">����</param>
	/// <param name="shader">��ɫ��</param>
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    /// <summary>
    /// ��ʹ��������ͼ
    /// </summary>
    /// <param name="va"></param>
    /// <param name="shader"></param>
    /// <param name="count"></param>
    void Draw(const VertexArray& va, const Shader& shader, const unsigned int count) const;
};
