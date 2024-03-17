#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderHelper.h"
#include "Errors.h"

// 定义ASSERT(x)，如果函数x返回false，就中断
#define ASSERT(x) if(!(x)) __debugbreak();

// 定义GLCall(x)，将函数x进行包装
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

    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[8] = {
       -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
       -0.5f,  0.5f
    };

    // 定义索引
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    // 生成顶点缓冲区，并返回ID
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // 绑定缓冲区
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    // 启用顶点属性。0，启用；1，不启用
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // 定义缓冲区
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);  // 绑定缓冲区
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
        //// 这里type必须是GL_UNSIGNED_INT，不能是GL_INT
        ////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr);
        //ASSERT(GLLogCall());

        // 方式二，调用宏
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // 释放
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
