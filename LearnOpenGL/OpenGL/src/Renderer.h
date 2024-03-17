#pragma once

#include <iostream>
#include <GL\glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// 定义ASSERT(x)，如果函数x返回false，就中断
#define ASSERT(x) if(!(x)) __debugbreak();

// 定义GLCall(x)，将函数x进行包装
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__,__LINE__));

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
    void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
