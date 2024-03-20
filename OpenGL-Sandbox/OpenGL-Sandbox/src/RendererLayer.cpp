#include "RendererLayer.h"
#include "Renderer.h"

using namespace GLCore;
using namespace GLCore::Utils;

RendererLayer::RendererLayer()
	:m_CameraController(16.0f / 9.0f), m_QuadIB(0), m_QuadVA(0), m_QuadVB(0), m_JtTex(0), m_XmTex(0)
{

}

RendererLayer::~RendererLayer()
{
	Renderer::Shutdown();
}

static GLuint LoadTexture(const std::string& path) {
	// ���ز���������
	int w, h, bits;
	stbi_set_flip_vertically_on_load(1);	// ��תY��
	auto* pixes = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);	// ��ȡ��������


	GLuint textureID;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Ϊ��ǰ�󶨵�����������û��ƣ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixes);

	// �ͷ�ͼ���ڴ�
	stbi_image_free(pixes);

	return textureID;
}

void RendererLayer::OnAttach()
{
	EnableGLDebugging();

	// Init here

	m_Shader = std::unique_ptr<Shader>(Shader::FromGLSLTextFiles(
		"assets/shaders/glsl.vert.shader",
		"assets/shaders/glsl.frag.shader"
	));

	glUseProgram(m_Shader->GetRendererID());
	auto loc = glGetUniformLocation(m_Shader->GetRendererID(), "u_Textures");
	int samplers[32]{};
	for (int i = 0; i < 32; i++)
	{
		samplers[i] = i;
	}
	glUniform1iv(loc, 32, samplers);

	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	// Ĭ�ϱ������ڣ����ô���


	Renderer::Init();

	// ��������
	m_JtTex = LoadTexture("assets/xm.png");
	m_XmTex = LoadTexture("assets/mlo.png");
}

void RendererLayer::OnDetach()
{
	// Shutdown here
	Renderer::Shutdown();
}

void RendererLayer::OnEvent(Event& event)
{
	// Events here
	m_CameraController.OnEvent(event);

	if (event.GetEventType() == EventType::WindowResize) {
		WindowResizeEvent& e = (WindowResizeEvent&)event;
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
	}
}

static void SetUniformMat4(uint32_t shader, const char* name, const glm::mat4& matrix) {
	int loc = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void RendererLayer::OnUpdate(Timestep ts)
{
	// Render here
	m_CameraController.OnUpdate(ts);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(m_Shader->GetRendererID());

	auto& vp = m_CameraController.GetCamera().GetViewProjectionMatrix();
	SetUniformMat4(m_Shader->GetRendererID(), "u_ViewProj", vp);
	SetUniformMat4(m_Shader->GetRendererID(), "u_Transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

	Renderer::ResetStats();
	Renderer::BeginBatch();

	// ���Ʊ���С����
	//glm::vec4 color = { 1.0f,1.0f,0.0f,1.0f };	// ��ɫ
	for (float y = -10.0f; y < 10.0f; y += 0.25f)
	{
		for (float x = -10.0f; x < 10.0f; x += 0.25f)
		{
			glm::vec4 color = { (x + 10) / 20.0f, 0.2f, (y + 10) / 20.0f, 1.0f };
			Renderer::DrawQuad({ x,y }, { 0.2f,0.2f }, color);
		}
	}

	// ʹ������ͼƬ���� 5 X 5
	for (float y = 0; y < 5; y++)
	{
		for (float x = 0; x < 5; x++)
		{
			GLuint tex = (int)(x + y) % 2 == 0 ? m_XmTex : m_JtTex;
			Renderer::DrawQuad({ x,y }, { 1.0f,1.0f }, tex);
		}
	}

	Renderer::DrawQuad(m_QuadPosition, { 1.0f,1.0f }, m_JtTex);
	Renderer::EndBatch();
	Renderer::Flush();
}

void RendererLayer::OnImGuiRender()
{
	// ImGui here
	ImGui::Begin("Controls");
	ImGui::DragFloat2("Quad Position", glm::value_ptr(m_QuadPosition), 0.1f);
	ImGui::Text("Quads: %d", Renderer::GetStats().QuadCount);
	ImGui::Text("Draws: %d", Renderer::GetStats().DrawCount);
	ImGui::End();
}
