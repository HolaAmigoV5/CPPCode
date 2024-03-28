#include "Texture.h"
#include "vendor\stb_image\stb_image.h"

/// <summary>
/// 构造函数
/// </summary>
/// <param name="textureType">该纹理的类型</param>
/// <param name="texturePath">该纹理对应图片的路径</param>
/// <param name="flipVertically">是否翻转图片的y轴 默认为true</param>
Texture::Texture(const string& textureType, const char* texturePath, bool flipVertically) {
	//std::cout << "Loading texture......\n" << "Path: " << string(texturePath) << "\nType: " << textureType << "\n\n";

	m_type = textureType;

	// 生成纹理
	GLCall(glGenTextures(1, &m_TextureID));

	// 绑定纹理
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	// 纹理环绕，重复纹理图像
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	// 纹理过滤 缩小
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	// 纹理过滤，放大
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

		// 内部格式(internalformat)：OpenGL存储纹理数据的方式
		// 格式(format)：是提供给OpenGL的数据格式
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));

		// 创建多级渐远纹理。
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	// 纹理已经设置完成了 记得回收读取图片所消耗的内存
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
