#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

int TextureDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "TexturesDemo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    glViewport(0, 0, 800, 600);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
           -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f,  0.5f, 1.0f, 1.0f,
           -0.5f,  0.5f, 0.0f, 1.0f
        };

        // 定义索引
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));     // 启用混合
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // 设置混合函数

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);


        // shader
        Shader shader("res/shaders/Texture.shader");
        shader.Bind();
        // end shader

        // Texture
        Texture texture("res/textures/Jt.png");
        texture.Bind();
        //shader.SetUniform1i("u_Texture", 0);
        // end Texture

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            Window::processInput(window);

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
