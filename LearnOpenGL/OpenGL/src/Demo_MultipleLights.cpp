#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include "glm\gtc\matrix_transform.hpp"

int MultipleLightsDemo()
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

    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 隐藏光标，并捕捉它
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 注册鼠标移动回调
    //glfwSetCursorPosCallback(window, mouse_callback);

    // 注册鼠标滚轮回调事件
    glfwSetScrollCallback(window, scroll_callback);

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;

    //启动深度测试
    glEnable(GL_DEPTH_TEST);

    {
        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };

        VertexArray objVa;
        VertexBuffer objVb(vertices, sizeof(vertices));

        VertexBufferLayout objLayout;
        objLayout.Push<float>(3);
        objLayout.Push<float>(3);
        objLayout.Push<float>(2);
        objVa.AddBuffer(objVb, objLayout);

        Shader colorShader("res/shaders/MultipleLights.shader");
        Shader lightShader("res/shaders/Light.shader");

        Texture diffuseMap("res/textures/container2.png");
        Texture specularMap("res/textures/container2_specular.png");

        colorShader.Bind();
        // 设置纹理贴图
        colorShader.SetUniform1i("material.diffuse", 0);
        colorShader.SetUniform1i("material.specular", 1);
        colorShader.Unbind();

        Renderer renderer;
        float deltaTime = 0.0f;     // 当前帧与上一帧的时间差
        float lastFrame = 0.0f;     // 上一帧时间
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);           // 光源位置

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

        // positions of the point lights
        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  0.0f, -3.0f)
        };

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // 监听键盘上WASD事件
            processInputWASD(window, deltaTime);

            /* Render here */
            renderer.Clear();

            // 进行MVP变换
            glm::mat4 model = glm::mat4(1.0f);

            // 通过改变fov实现滚轮缩放
            glm::mat4 proj = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // 用键盘控制自由移动
            glm::mat4 view = camera.GetViewMatrix();

            GLCall(colorShader.Bind());

            // directional light
            colorShader.SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
            colorShader.SetUniform4f("dirLight.ambient", 0.05f, 0.05f, 0.05f, 1.0f);
            colorShader.SetUniform4f("dirLight.diffuse", 0.4f, 0.4f, 0.4f, 1.0f);
            colorShader.SetUniform4f("dirLight.specular", 0.5f, 0.5f, 0.5f, 1.0f);
            // point light 1
            colorShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
            colorShader.SetUniform4f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f, 1.0f);
            colorShader.SetUniform4f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f, 1.0f);
            colorShader.SetUniform4f("pointLights[0].specular", 1.0f, 1.0f, 1.0f, 1.0f);
            colorShader.SetUniform1f("pointLights[0].constant", 1.0f);
            colorShader.SetUniform1f("pointLights[0].linear", 0.09f);
            colorShader.SetUniform1f("pointLights[0].quadratic", 0.032f);
            // point light 2
            colorShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
            colorShader.SetUniform4f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f, 1.0f);
            colorShader.SetUniform4f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f, 1.0f);
            colorShader.SetUniform4f("pointLights[1].specular", 1.0f, 1.0f, 1.0f,1.0f);
            colorShader.SetUniform1f("pointLights[1].constant", 1.0f);
            colorShader.SetUniform1f("pointLights[1].linear", 0.09f);
            colorShader.SetUniform1f("pointLights[1].quadratic", 0.032f);
            // point light 3
            colorShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
            colorShader.SetUniform4f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f, 1.0f);
            colorShader.SetUniform4f("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f, 1.0f);
            colorShader.SetUniform4f("pointLights[2].specular", 1.0f, 1.0f, 1.0f, 1.0f);
            colorShader.SetUniform1f("pointLights[2].constant", 1.0f);
            colorShader.SetUniform1f("pointLights[2].linear", 0.09f);
            colorShader.SetUniform1f("pointLights[2].quadratic", 0.032f);
            // point light 4
            colorShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
            colorShader.SetUniform4f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f, 1.0f);
            colorShader.SetUniform4f("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f, 1.0f);
            colorShader.SetUniform4f("pointLights[3].specular", 1.0f, 1.0f, 1.0f, 1.0f);
            colorShader.SetUniform1f("pointLights[3].constant", 1.0f);
            colorShader.SetUniform1f("pointLights[3].linear", 0.09f);
            colorShader.SetUniform1f("pointLights[3].quadratic", 0.032f);
            // spotLight
            colorShader.SetVec3("spotLight.position", camera.GetPosition());
            colorShader.SetVec3("spotLight.direction", camera.GetFront());
            colorShader.SetUniform4f("spotLight.ambient", 0.0f, 0.0f, 0.0f, 1.0f);
            colorShader.SetUniform4f("spotLight.diffuse", 1.0f, 1.0f, 1.0f, 1.0f);
            colorShader.SetUniform4f("spotLight.specular", 1.0f, 1.0f, 1.0f, 1.0f);
            colorShader.SetUniform1f("spotLight.constant", 1.0f);
            colorShader.SetUniform1f("spotLight.linear", 0.09f);
            colorShader.SetUniform1f("spotLight.quadratic", 0.032f);
            colorShader.SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            colorShader.SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            colorShader.SetVec3("viewPos", camera.GetPosition());
            // 设置材质
            colorShader.SetUniform1f("material.shininess", 32.0f);

            // 计算法线矩阵，把法向量转为世界空间坐标
            glm::mat3 normalMat = (glm::mat3)glm::transpose(glm::inverse(model));
            colorShader.SetUniformMat3f("normalMat", normalMat);

            // 纹理绑定
            diffuseMap.Bind(0);
            specularMap.Bind(1);

            colorShader.Unbind();

            colorShader.Bind();
            for (unsigned int i = 0; i < 10; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                glm::mat4 mvp = proj * view * model;
                colorShader.SetUniformMat4f("model", model);
                colorShader.SetUniformMat4f("transform", mvp);
                renderer.Draw(objVa, colorShader, 36);
            }
            colorShader.Unbind();

            GLCall(lightShader.Bind());
            for (unsigned int i = 0; i < 4; i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f));

                glm::mat4 mvp = proj * view * model;
                lightShader.SetUniformMat4f("transform", mvp);

                renderer.Draw(objVa, lightShader, 36);
            }
            lightShader.Unbind();
            

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}