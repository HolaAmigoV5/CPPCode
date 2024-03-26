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

    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    glViewport(0, 0, 800, 600);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float vertices[] = {
            // ---- 位置 ----       ---- 颜色 ----    - 纹理坐标 -
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
        };


        // 定义索引
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

            // 对纹理进行变换
            glm::mat4 transform = glm::mat4(1.0f); // 定义4X4单位矩阵

            // 创建位移矩阵，传入单位矩阵和位移向量
            //transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f)); 
            // 创建旋转矩阵，绕Z轴旋转
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

            // 先旋转，再位移，旋转效果会影响位移。
            transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));

            // 循环缩放
            float scaleFactor = 1.0f + 0.8f * sin((float)glfwGetTime());    // 计算缩放因子
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
