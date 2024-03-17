#include "TestTexture2D.h"

#include "imgui\imgui.h"
#include "glm\gtc\matrix_transform.hpp"

namespace test {
    TestTexture2D::TestTexture2D()
        :m_TranslationA(200, 200, 0), m_TranslationB(400, 400, 0),
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    {
        // 纹理坐标取左下原点（0,0），右下（1,0），右上（1,1），左上（0,1）
        float positions[] = {
           -50.0f, -50.0f, 0.0f, 0.0f,      // 顶点坐标（x,y）+ 纹理坐标(x, y)
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f,  50.0f, 1.0f, 1.0f,
           -50.0f,  50.0f, 0.0f, 1.0f
        };

        // 定义索引
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));     // 启用混合
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // 设置混合函数

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 16 * sizeof(float));
        m_VA = std::make_unique<VertexArray>();
        m_VA->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("res/shaders/Maths.shader");
        m_Shader->Bind();

        m_Texture = std::make_unique<Texture>("res/textures/Jt.png");

        m_Shader->SetUniform1i("u_Texture", 0);
    }

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		/*GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		GLCall(glClear(GL_COLOR_BUFFER_BIT));*/

        Renderer renderer;
        m_Texture->Bind();

        // 第一次变换MVP，并绘制
        {
            // 模型右上移动
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VA, *m_IndexBuffer, *m_Shader);
        }

        // 第二次变换MVP，并绘制
        {
            // 模型右上移动
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VA, *m_IndexBuffer, *m_Shader);
        }
	}

	void TestTexture2D::OnImGuiRender()
	{
        ImGui::Begin("Hello, world!");
        ImGui::SliderFloat3("A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("B", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
	}
}
