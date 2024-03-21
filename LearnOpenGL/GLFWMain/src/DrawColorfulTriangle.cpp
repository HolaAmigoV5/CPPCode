
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

int DrawColorfulTriangleDemo()
{
    GLFWwindow* window;

    // ��ʼ��GLFW
    if (!glfwInit())
        return -1;

    // ����OpenGL�汾Ϊ3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ����ģʽ����

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "DrawColorfulTriangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // *************************GLEW******************************
    // �����ڴ���OpenGL��Ⱦ�����ĺ���ܵ���glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;
    // ***********************************************************

    // ǰ�������������ƴ������½�λ�ã��������������Ⱦ���ڵĿ��
    glViewport(0, 0, 800, 600);

    // ÿ�δ��ڴ�С����ʱ����
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    // build and compile our shader program
    // -----------------------------------------------------------------------
    ShaderHelper shaderProgram("res/shaders/Colorful.shader");
    GLCall(shaderProgram.Bind());
    GLCall(shaderProgram.Unbind());
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // ���嶥������
    float vertices[] = {
        // λ��              // ��ɫ
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); // ����VAO
    glGenBuffers(1, &VBO);      // ����VBO����
    // �Ȱ�VAO��Ȼ���VBO��������ö�������
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // VBO������������GL_ARRAY_BUFFER
    // �������ݸ��Ƶ�������ڴ���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ���ö���λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ���ö�����ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // ���VBO
    glBindVertexArray(0);               // ���VAO

    // ��Ⱦѭ�������ڲ��رվͲ�����Ⱦ
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // ���������ɫ����������ɫ���
        glClear(GL_COLOR_BUFFER_BIT);

        // ����������
        GLCall(shaderProgram.Bind());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ������ɫ����
        glfwSwapBuffers(window);

        // ����Ƿ񴥷��¼�����������룬����ƶ��ȣ�
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram.GetShaderID());

    glfwTerminate();    // �ͷ�/ɾ��֮ǰ�����������Դ
    return 0;
}
