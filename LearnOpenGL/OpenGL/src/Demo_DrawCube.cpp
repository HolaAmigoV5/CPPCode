#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "glm\gtc\matrix_transform.hpp"

int DrawCubeDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TexturesDemo", NULL, NULL);
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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;

    //启动深度测试
    glEnable(GL_DEPTH_TEST);

    {
        float vertices[] = {
            // ---- 位置 ----     - 纹理坐标 -
            // 前面  
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 0  
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 1  
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 2  
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 3  

             // 后面  
              0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 4  
             -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 5  
             -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 6  
              0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 7 
        };


        // 定义索引
        unsigned int indices[] = {
             // 前面  
             0, 1, 2,
             2, 3, 0,
             // 后面  
             4, 5, 6,
             6, 7, 4,
             // 上面  
             0, 4, 5,
             5, 1, 0,
             // 下面  
             3, 7, 6,
             6, 2, 3,
             // 左侧  
             1, 5, 6,
             6, 2, 1,
             // 右侧  
             0, 3, 7,
             7, 4, 0
        };

        VertexArray va;
        VertexBuffer vb(vertices, sizeof(vertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 36);


        // shader
        Shader shader("res/shaders/Cube.shader");
        shader.Bind();
        // end shader

        // Texture
        Texture texture("res/textures/xm.png");
        shader.SetUniform1i("u_Texture", 0);

        Texture texture1("res/textures/mlo.png");
        shader.SetUniform1i("u_Texture1", 1);
        // end Texture

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        glm::vec3 cubePositions[] = {
           glm::vec3(0.0f,  0.0f,  0.0f),
           glm::vec3(2.0f,  5.0f, -15.0f),
           glm::vec3(-1.5f, -2.2f, -2.5f),
           glm::vec3(-3.8f, -2.0f, -12.3f),
           glm::vec3(2.4f, -0.4f, -3.5f),
           glm::vec3(-1.7f,  3.0f, -7.5f),
           glm::vec3(1.3f, -2.0f, -2.5f),
           glm::vec3(1.5f,  2.0f, -2.5f),
           glm::vec3(1.5f,  0.2f, -1.5f),
           glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        float radius = 10.0f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            /* Render here */
            renderer.Clear();

            texture.Bind(0);
            texture1.Bind(1);

            // 进行MVP变换
            glm::mat4 view  = glm::mat4(1.0f);
            glm::mat4 proj  = glm::mat4(1.0f);
            
            proj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            float camX = (float)sin(glfwGetTime()) * radius;
            float camZ = (float)cos(glfwGetTime()) * radius;

            //定义LookAt矩阵，让场景转动。参数分别是：摄像机位置，目标位置，上向量
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


            for (unsigned int i = 0; i < 10; i++) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                

                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));

                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("transform", mvp);

                renderer.Draw(va, ib, shader);
            }
            

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
