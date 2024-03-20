#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

class RendererLayer :public GLCore::Layer
{
public:
	RendererLayer();
	virtual ~RendererLayer();


	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	std::unique_ptr<GLCore::Utils::Shader> m_Shader;
	GLuint m_QuadVA, m_QuadVB, m_QuadIB;
	GLCore::Utils::OrthographicCameraController m_CameraController;

	GLuint m_JtTex, m_XmTex;
	glm::vec2 m_QuadPosition = { -1.5,-0.5 };
};