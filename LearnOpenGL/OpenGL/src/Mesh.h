#pragma once
#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

#include <string>
#include <vector>


using namespace std;

// ��������
struct Vertex
{
	glm::vec3 Position;		// λ��
	glm::vec3 Normal;		// ������
	glm::vec2 TexCoords;	// ��������
};

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<std::shared_ptr<Texture>> textures)
	: m_Vertices(vertices),m_Indices(indices), m_Textures(textures)
	{
		setupMesh();
	}

	void Draw(Shader& shader);

private:
	VertexArray* va;

	// ��������
	vector<Vertex> m_Vertices;
	vector<unsigned int> m_Indices;
	vector<std::shared_ptr<Texture>> m_Textures;

	void setupMesh() {
		va = new VertexArray();
		VertexBuffer vb(&m_Vertices[0], static_cast<unsigned int>(m_Vertices.size()) * sizeof(Vertex));

		VertexBufferLayout layout{};
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		va->AddBuffer(vb, layout);
		IndexBuffer ib(&m_Indices[0], static_cast<unsigned int>(m_Indices.size()));

		glBindVertexArray(0);
	}
};
#endif
