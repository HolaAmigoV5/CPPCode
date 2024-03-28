#include "Mesh.h"

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	shader.Bind();
	for (unsigned i = 0; i < m_Textures.size(); i++)
	{
		string number;
		string name = m_Textures[i]->GetName();
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);

		GLCall(shader.SetUniform1i((name + number).c_str(), i));

		m_Textures[i]->Bind(i);
	}

	// draw mesh
	GLCall(va->Bind());
	GLCall(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Indices.size()), GL_UNSIGNED_INT, 0));

	// »¹Ô­
	glActiveTexture(GL_TEXTURE0);
	shader.Unbind();
}
