#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer.h"
#include <string>

using std::string;

class Texture {
private:
	unsigned int m_TextureID;
	string m_type;
public:
	Texture(const string& path) :Texture("Texture", path, true) {}
	Texture(const string& textureType, const char* texturePath, bool flipVertically);
	Texture(const string& textureType, const string& texturePath, bool flipVertically = true)
		:Texture(textureType, texturePath.c_str(), flipVertically) {}

	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline string GetName() const { return m_type; }
};

#endif // !TEXTURE_H

