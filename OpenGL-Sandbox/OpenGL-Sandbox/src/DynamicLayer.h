#pragma once


#include <GLCore.h>
#include <GLCoreUtils.h>

class DynamicLayer:public GLCore::Layer
{
public:
	DynamicLayer();
	virtual ~DynamicLayer();


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
	float m_QuadPosition[2] = { -1.5,-0.5 };
};

