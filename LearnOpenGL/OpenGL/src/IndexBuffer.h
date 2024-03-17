#pragma once

class IndexBuffer
{
public:
	/// <summary>
	/// 构造索引缓冲区
	/// </summary>
	/// <param name="data">数据</param>
	/// <param name="count">个数</param>
	IndexBuffer(const unsigned int* data, unsigned int count);

	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
