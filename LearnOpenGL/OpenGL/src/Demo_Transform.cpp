#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "glm\gtc\matrix_transform.hpp"

int TransformDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "TexturesDemo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // �����ڴ���OpenGL��Ⱦ�����ĺ���ܵ���glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    glViewport(0, 0, 800, 600);

    // ÿ�δ��ڴ�С����ʱ����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float vertices[] = {
            // ---- λ�� ----       ---- ��ɫ ----    - �������� -
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
        };


        // ��������
        unsigned int indices[] = {
            0,1,3,
            1,2,3
        };

        VertexArray va;
        VertexBuffer vb(vertices, 8 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);


        // shader
        Shader shader("res/shaders/Transform.shader");
        shader.Bind();
        // end shader

        // Texture
        Texture texture("res/textures/zq.png");
        shader.SetUniform1i("u_Texture", 0);

        Texture texture1("res/textures/mlo.png");
        shader.SetUniform1i("u_Texture1", 1);
        // end Texture

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            /* Render here */
            renderer.Clear();

            texture.Bind(0);
            texture1.Bind(1);

            // ��������б任
            glm::mat4 transform = glm::mat4(1.0f); // ����4X4��λ����

            // ����λ�ƾ��󣬴��뵥λ�����λ������
            //transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f)); 
            // ������ת������Z����ת
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

            // ����ת����λ�ƣ���תЧ����Ӱ��λ�ơ�
            transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));

            // ѭ������
            float scaleFactor = 1.0f + 0.8f * sin((float)glfwGetTime());    // ������������
            transform = glm::scale(transform, scaleFactor * glm::vec3(1.0, 1.0, 1.0));

            shader.Bind();
            shader.SetUniformMat4f("transform", transform);

            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
