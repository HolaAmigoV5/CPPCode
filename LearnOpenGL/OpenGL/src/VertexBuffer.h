#pragma once

class VertexBuffer
{
public:
	/// <summary>
	/// ���춥�㻺����
	/// </summary>
	/// <param name="data">����</param>
	/// <param name="size">��С</param>
	VertexBuffer(const void* data, unsigned int size);

	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
};
