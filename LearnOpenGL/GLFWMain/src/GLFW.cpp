
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"


int GLFWDemo()
{
    GLFWwindow* window;

    // 初始化GLFW
    if (!glfwInit())
        return -1;

    // 配置OpenGL版本为3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 核心模式运行
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Mac OS X系统配置才能起作用

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // 前面两个参数控制窗口左下角位置，后面参数设置渲染窗口的宽高
    glViewport(0, 0, 800, 600);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    // 渲染循环：窗口不关闭就不断渲染
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 清除所有颜色，以深蓝绿色填充
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换颜色缓冲
        glfwSwapBuffers(window);    

        // 检查是否触发事件（如键盘输入，鼠标移动等）
        glfwPollEvents();
    }

    glfwTerminate();    // 释放/删除之前分配的所有资源
    return 0;
}