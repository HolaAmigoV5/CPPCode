#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include "glm\gtc\matrix_transform.hpp"

#include "Model.h"


int ModelLoadingDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LightingColor", NULL, NULL);
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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 隐藏光标，并捕捉它
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 注册鼠标移动回调
    glfwSetCursorPosCallback(window, mouse_callback);

    // 注册鼠标滚轮回调事件
    glfwSetScrollCallback(window, scroll_callback);

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;

    //启动深度测试
    glEnable(GL_DEPTH_TEST);

    {
        Shader ourShader("res/shaders/LoadingModel.shader");
        Model ourModel("res/objects/nanosuit/nanosuit.obj");

        Renderer renderer;
        float deltaTime = 0.0f;     // 当前帧与上一帧的时间差
        float lastFrame = 0.0f;     // 上一帧时间
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);           // 光源位置

        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // 监听键盘上WASD事件
            processInputWASD(window, deltaTime);

            renderer.Clear();

            // 通过改变fov实现滚轮缩放
            glm::mat4 proj = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // 用键盘控制自由移动
            glm::mat4 view = camera.GetViewMatrix();

            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -1.75f, -3.0f));
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            model = glm::rotate(model, glm::radians(camera.GetYaw()), glm::vec3(0.0, 1.0, 0.0));
            model = glm::rotate(model, glm::radians(camera.GetPitch()), glm::vec3(1.0, 0.0, 0.0));
            glm::mat4 mvp = proj * view * model;

            ourShader.Bind();
            // 设置光源
            ourShader.SetVec3("light.position", camera.GetPosition());
            ourShader.SetVec3("light.direction", camera.GetFront());
            ourShader.SetUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
            ourShader.SetUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));
            ourShader.SetVec3("viewPos", camera.GetPosition());

            ourShader.SetUniform4f("light.ambient", 0.3f, 0.3f, 0.3f, 1.0);
            ourShader.SetUniform4f("light.diffuse", 0.8f, 0.8f, 0.8f, 1.0f);
            ourShader.SetUniform4f("light.specular", 1.0f, 1.0f, 1.0f, 1.0f);

            ourShader.SetUniform1f("light.constant", 1.0f);
            ourShader.SetUniform1f("light.linear", 0.09f);
            ourShader.SetUniform1f("light.quadratic", 0.032f);

            // 计算法线矩阵，把法向量转为世界空间坐标
            glm::mat3 normalMat = (glm::mat3)glm::transpose(glm::inverse(model));
            ourShader.SetUniformMat3f("normalMat", normalMat);

            ourShader.SetUniformMat4f("model", model);
            ourShader.SetUniformMat4f("transform", mvp);
            ourShader.Unbind();

            GLCall(ourModel.Draw(ourShader));
            

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}