#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include "glm\gtc\matrix_transform.hpp"

int LightCasterDemo()
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

    // �����ڴ���OpenGL��Ⱦ�����ĺ���ܵ���glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


    // ÿ�δ��ڴ�С����ʱ����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ���ع�꣬����׽��
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // ע������ƶ��ص�
    //glfwSetCursorPosCallback(window, mouse_callback);

    // ע�������ֻص��¼�
    glfwSetScrollCallback(window, scroll_callback);

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;

    //������Ȳ���
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

        Shader colorShader("res/shaders/LightCaster.shader");
        //Shader lightShader("res/shaders/Light.shader");

        Texture diffuseMap("res/textures/container2.png");
        Texture specularMap("res/textures/container2_specular.png");

        colorShader.Bind();
        // ����������ͼ
        colorShader.SetUniform1i("material.diffuse", 0);
        colorShader.SetUniform1i("material.specular", 1);
        colorShader.Unbind();

        Renderer renderer;
        float deltaTime = 0.0f;     // ��ǰ֡����һ֡��ʱ���
        float lastFrame = 0.0f;     // ��һ֡ʱ��
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);           // ��Դλ��

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


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // ����������WASD�¼�
            processInputWASD(window, deltaTime);

            /* Render here */
            renderer.Clear();

            // ����MVP�任
            glm::mat4 model = glm::mat4(1.0f);

            // ͨ���ı�fovʵ�ֹ�������
            glm::mat4 proj = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // �ü��̿��������ƶ�
            glm::mat4 view = camera.GetViewMatrix();

            GLCall(colorShader.Bind());

            // ���ù�Դ
            colorShader.SetVec3("light.position", camera.GetPosition());
            colorShader.SetVec3("light.direction", camera.GetFront());
            colorShader.SetUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
            colorShader.SetUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));
            colorShader.SetVec3("viewPos", camera.GetPosition());

            colorShader.SetUniform4f("light.ambient", 0.1f, 0.1f, 0.1f, 1.0);
            colorShader.SetUniform4f("light.diffuse", 0.8f, 0.8f, 0.8f, 1.0f);
            colorShader.SetUniform4f("light.specular", 1.0f, 1.0f, 1.0f, 1.0f);

            colorShader.SetUniform1f("light.constant", 1.0f);
            colorShader.SetUniform1f("light.linear", 0.09f);
            colorShader.SetUniform1f("light.quadratic", 0.032f);

            // ���ò���
            colorShader.SetUniform1f("material.shininess", 32.0f);

            // ���㷨�߾��󣬰ѷ�����תΪ����ռ�����
            glm::mat3 normalMat = (glm::mat3)glm::transpose(glm::inverse(model));
            colorShader.SetUniformMat3f("normalMat", normalMat);
           

            // �����
            diffuseMap.Bind(0);
            specularMap.Bind(1);

            colorShader.Unbind();

            for (unsigned int i = 0; i < 10; i++)
            {
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                glm::mat4 mvp = proj * view * model;

                colorShader.Bind();
                colorShader.SetUniformMat4f("model", model);
                colorShader.SetUniformMat4f("transform", mvp);
                renderer.Draw(objVa, colorShader, 36);
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