#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderHelper.h"
#include "Errors.h"
#include "WindowsWindow.h"

// ����ASSERT(x)���������x����false�����ж�
#define ASSERT(x) if(!(x)) __debugbreak();

// ����GLCall(x)��������x���а�װ
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__,__LINE__));

int UniformsDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Uniforms", NULL, NULL);
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

    // ǰ�������������ƴ������½�λ�ã��������������Ⱦ���ڵĿ��
    glViewport(0, 0, 800, 600);

    // ÿ�δ��ڴ�С����ʱ����
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[8] = {
       -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
       -0.5f,  0.5f
    };

    // ��������
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    // ���ɶ��㻺������������ID
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // �󶨻�����
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    // ���ö������ԡ�0�����ã�1��������
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // ���建����
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);  // �󶨻�����
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


    // shader
    ShaderHelper shaderProgram("res/shaders/Uniform.shader");
    GLCall(shaderProgram.Bind());

    unsigned int shader = shaderProgram.GetShaderID();
    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));
    // end shader

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        // ��Ⱦ
        // �����ɫ����
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ����uniform��ɫ
        float timeValue = (float)glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        GLCall(glUniform4f(location, 0.8f, greenValue, 0.8f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // �ͷ�
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
