#include "Texture.h"
#include "vendor\stb_image\stb_image.h"

/// <summary>
/// ���캯��
/// </summary>
/// <param name="textureType">�����������</param>
/// <param name="texturePath">�������ӦͼƬ��·��</param>
/// <param name="flipVertically">�Ƿ�תͼƬ��y�� Ĭ��Ϊtrue</param>
Texture::Texture(const string& textureType, const char* texturePath, bool flipVertically) {
	//std::cout << "Loading texture......\n" << "Path: " << string(texturePath) << "\nType: " << textureType << "\n\n";

	m_type = textureType;

	// ��������
	GLCall(glGenTextures(1, &m_TextureID));

	// ������
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	// �����ƣ��ظ�����ͼ��
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	// ������� ��С
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	// ������ˣ��Ŵ�
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	int width, height, nrChannels;
	if (flipVertically)
		stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format{};
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		else
		{
			//  c++ error stream
			std::cerr << "Texture image channel numbers error.\n";
			stbi_image_free(data);
			return;
		}

		// �ڲ���ʽ(internalformat)��OpenGL�洢�������ݵķ�ʽ
		// ��ʽ(format)�����ṩ��OpenGL�����ݸ�ʽ
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));

		// �����༶��Զ����
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	// �����Ѿ���������� �ǵû��ն�ȡͼƬ�����ĵ��ڴ�
	stbi_image_free(data);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
