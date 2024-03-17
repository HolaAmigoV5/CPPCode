#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm\gtc\matrix_transform.hpp"

#include <GLFW/glfw3.h>

int MVPMatricesDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // �����ڴ���OpenGL��Ⱦ�����ĺ���ܵ���glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        // ��������ȡ����ԭ�㣨0,0�������£�1,0�������ϣ�1,1�������ϣ�0,1��
        float positions[] = {
           100.0f, 100.0f, 0.0f, 0.0f,      // �������꣨x,y��+ ��������(x, y)
           200.0f, 100.0f, 1.0f, 0.0f,
           200.0f, 200.0f, 1.0f, 1.0f,
           100.0f, 200.0f, 0.0f, 1.0f
        };

        // ��������
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));     // ���û��
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // ���û�Ϻ���

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        // ģ��-��ͼ-ͶӰ�任
        // ����ͶӰ��Χ
        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        // ������������ƶ�100��λ����Ч�ڶ������������ƶ�100��λ��
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        // ģ�������ƶ�
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

        glm::mat4 mvp = proj * view * model;

        Shader shader("res/shaders/Maths.shader");
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        // MVP end

        // Texture
        Texture texture("res/textures/Jt.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        // end Texture

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
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