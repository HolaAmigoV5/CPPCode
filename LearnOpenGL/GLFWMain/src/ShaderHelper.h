#pragma once

#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class ShaderHelper
{
private:
	unsigned int m_ShaderID;

public:
	ShaderHelper(const std::string& filepath);
	~ShaderHelper();

	//  π”√/º§ªÓ
	void Bind() const;
	void Unbind() const;

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	inline unsigned int GetShaderID() const { return m_ShaderID; }
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

