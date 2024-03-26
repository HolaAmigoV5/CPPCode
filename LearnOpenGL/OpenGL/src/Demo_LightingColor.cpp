#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include "glm\gtc\matrix_transform.hpp"

//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int LightColorDemo()
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

        //VertexArray lightVa;
        //VertexBuffer lightVb(vertices, sizeof(vertices));

        //VertexBufferLayout lightLayout;
        //lightLayout.Push<float>(3);
        //lightLayout.Push<float>(3);
        //lightVa.AddBuffer(lightVb, lightLayout);

       /* unsigned int VBO, cubeVAO;
        glGenVertexArrays(1, &cubeVAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindVertexArray(cubeVAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int lightCubeVAO;
        glGenVertexArrays(1, &lightCubeVAO);

        glBindVertexArray(lightCubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);*/


        Shader colorShader("res/shaders/Colors.shader");
        Shader lightShader("res/shaders/Light.shader");


        Renderer renderer;
        float deltaTime = 0.0f;     // ��ǰ֡����һ֡��ʱ���
        float lastFrame = 0.0f;     // ��һ֡ʱ��
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);           // ��Դλ��
        float ambientStrength = 0.1f;                   // ������ǿ��
        glm::vec4 lightColor = glm::vec4(1.0f);

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

            colorShader.SetVec4("lightColor", lightColor);                     // ��Դ��ɫ
            colorShader.SetUniform4f("objectColor", 1.0f, 0.5f, 0.31f, 1.0f); // ����ɺ����ɫ
            colorShader.SetVec3("lightPos", lightPos);

            // ���㷨�߾��󣬰ѷ�����תΪ����ռ�����
            glm::mat3 normalMat = (glm::mat3)glm::transpose(glm::inverse(model));
            colorShader.SetUniformMat3f("normalMat", normalMat);
            colorShader.SetVec3("viewPos", camera.GetPosition());
            colorShader.Unbind();

            //GLCall(glBindVertexArray(cubeVAO));
            //GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

            GLCall(lightShader.Bind());
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            mvp = proj * view * model;
            lightShader.SetUniformMat4f("transform", mvp);
            lightShader.Unbind();

            //glBindVertexArray(lightCubeVAO);
            //glDrawArrays(GL_TRIANGLES, 0, 36);

            renderer.Draw(objVa, lightShader, 36);
            renderer.Draw(objVa, colorShader, 36);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        //glDeleteVertexArrays(1, &cubeVAO);
        //glDeleteVertexArrays(1, &lightCubeVAO);
        //glDeleteBuffers(1, &VBO);
    }

    

    glfwTerminate();
    return 0;
}