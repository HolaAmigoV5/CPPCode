#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include "glm\gtc\matrix_transform.hpp"

int MaterialDemo()
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
            // ----λ��----      ----������----
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        VertexArray objVa;
        VertexBuffer objVb(vertices, sizeof(vertices));

        VertexBufferLayout objLayout;
        objLayout.Push<float>(3);
        objLayout.Push<float>(3);
        objVa.AddBuffer(objVb, objLayout);

        Shader colorShader("res/shaders/Material.shader");
        Shader lightShader("res/shaders/Light.shader");


        Renderer renderer;
        float deltaTime = 0.0f;     // ��ǰ֡����һ֡��ʱ���
        float lastFrame = 0.0f;     // ��һ֡ʱ��
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);           // ��Դλ��

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = (float)glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // ����������WASD�¼�
            processInputWASD(window, deltaTime);

            /* Render here */
            renderer.Clear();

            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // ���������ɫ����������ɫ���
            //GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // �����Ȼ���

            // ����MVP�任
            glm::mat4 model = glm::mat4(1.0f);

            // ͨ���ı�fovʵ�ֹ�������
            glm::mat4 proj = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // �ü��̿��������ƶ�
            glm::mat4 view = camera.GetViewMatrix();
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));

            glm::mat4 mvp = proj * view * model;

            GLCall(colorShader.Bind());
            colorShader.SetUniformMat4f("model", model);
            colorShader.SetUniformMat4f("transform", mvp);

            // ���ò���
            colorShader.SetUniform4f("material.ambient", 1.0f, 0.5f, 0.31f, 1.0f); 
            colorShader.SetUniform4f("material.diffuse", 1.0f, 0.5f, 0.31f, 1.0f); 
            colorShader.SetUniform4f("material.specular", 0.5f, 0.5f, 0.5f, 1.0f); 
            colorShader.SetUniform1f("material.shininess", 32.0f);

            // ���ù�Դ
            glm::vec4 lightColor{};
            lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0f));
            lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7f));
            lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3f));
            glm::vec4 diffuseColor = 0.8f * lightColor;
            glm::vec4 ambientColor = 0.2f * lightColor;


            colorShader.SetVec4("light.ambient", ambientColor);
            colorShader.SetVec4("light.diffuse", diffuseColor);
            colorShader.SetUniform4f("light.specular", 1.0f, 1.0f, 1.0f, 1.0f);
            colorShader.SetVec3("lightPos", lightPos);

            // ���㷨�߾��󣬰ѷ�����תΪ����ռ�����
            glm::mat3 normalMat = (glm::mat3)glm::transpose(glm::inverse(model));
            colorShader.SetUniformMat3f("normalMat", normalMat);
            colorShader.SetVec3("viewPos", camera.GetPosition());
            colorShader.Unbind();

            GLCall(lightShader.Bind());
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            mvp = proj * view * model;
            lightShader.SetUniformMat4f("transform", mvp);
            lightShader.Unbind();

            renderer.Draw(objVa, lightShader, 36);
            renderer.Draw(objVa, colorShader, 36);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}