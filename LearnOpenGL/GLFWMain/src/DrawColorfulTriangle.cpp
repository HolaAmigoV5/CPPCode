
#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderHelper.h"
#include "Errors.h"
#include "WindowsWindow.h"


// 定义ASSERT(x)，如果函数x返回false，就中断
#define ASSERT(x) if(!(x)) __debugbreak();

// 定义GLCall(x)，将函数x进行包装
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__,__LINE__));

int DrawColorfulTriangleDemo()
{
    GLFWwindow* window;

    // 初始化GLFW
    if (!glfwInit())
        return -1;

    // 配置OpenGL版本为3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 核心模式运行

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
    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;
    // ***********************************************************

    // 前面两个参数控制窗口左下角位置，后面参数设置渲染窗口的宽高
    glViewport(0, 0, 800, 600);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    // build and compile our shader program
    // -----------------------------------------------------------------------
    ShaderHelper shaderProgram("res/shaders/Colorful.shader");
    GLCall(shaderProgram.Bind());
    GLCall(shaderProgram.Unbind());
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // 定义顶点数据
    float vertices[] = {
        // 位置              // 颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); // 生成VAO
    glGenBuffers(1, &VBO);      // 生成VBO对象
    // 先绑定VAO，然后绑定VBO，最后配置顶点属性
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // VBO缓冲类型设置GL_ARRAY_BUFFER
    // 顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 设置顶点颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // 解绑VBO
    glBindVertexArray(0);               // 解绑VAO

    // 渲染循环：窗口不关闭就不断渲染
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 清除所有颜色，以深蓝绿色填充
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制三角形
        GLCall(shaderProgram.Bind());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换颜色缓冲
        glfwSwapBuffers(window);

        // 检查是否触发事件（如键盘输入，鼠标移动等）
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram.GetShaderID());

    glfwTerminate();    // 释放/删除之前分配的所有资源
    return 0;
}
