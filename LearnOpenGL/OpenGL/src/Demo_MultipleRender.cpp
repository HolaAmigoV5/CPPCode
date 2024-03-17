#include "Texture.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm\gtc\matrix_transform.hpp"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

int MultipleDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // Enable vsync

    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;
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

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        // 模型-视图-投影变换
        // 定义投影范围
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        // 相机坐标向左移动100单位（等效于对象坐标向右移动100单位）
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


        Shader shader("res/shaders/Maths.shader");
        shader.Bind();
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

        // ImGui
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            // 第一次变换MVP，并绘制
            {
                // 模型右上移动
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }

            // 第二次变换MVP，并绘制
            {
                // 模型右上移动
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }

            {
                ImGui::Begin("Hello, world!");
                ImGui::SliderFloat3("A", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("B", &translationB.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }


            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
