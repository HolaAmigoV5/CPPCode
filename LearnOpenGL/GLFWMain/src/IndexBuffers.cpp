#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderHelper.h"
#include "Errors.h"

// ����ASSERT(x)���������x����false�����ж�
#define ASSERT(x) if(!(x)) __debugbreak();

// ����GLCall(x)��������x���а�װ
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__,__LINE__));

int IndexBuffersDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // �󶨻�����
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    // ���ö������ԡ�0�����ã�1��������
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // ���建����
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);  // �󶨻�����
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


    // shader
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);
    // end shader

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //GLClearError();
        //// ����type������GL_UNSIGNED_INT��������GL_INT
        ////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr);
        //ASSERT(GLLogCall());

        // ��ʽ�������ú�
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // �ͷ�
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
