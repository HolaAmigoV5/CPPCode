#pragma once

class VertexBuffer
{
public:
	/// <summary>
	/// 构造顶点缓冲区
	/// </summary>
	/// <param name="data">数据</param>
	/// <param name="size">大小</param>
	VertexBuffer(const void* data, unsigned int size);

	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
};
