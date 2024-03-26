#pragma once
#include <string>
#include <unordered_map>

#include "glm\glm.hpp"
#include <GL\glew.h>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	//caching for uniforms
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);

	~Shader();

	void Bind() const;
	void Unbind() const;


	// Set uniforms
	void SetVec4(const std::string& name, const glm::vec4& value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

	void SetUniform3f(const std::string& name, float f0, float f1, float f2);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLint GetUniformLocation(const std::string& name) const;
};

