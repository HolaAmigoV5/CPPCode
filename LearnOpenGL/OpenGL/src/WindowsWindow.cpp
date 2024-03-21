#include "WindowsWindow.h"

// 每次窗口变换时，视口调整回调
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::processInput(GLFWwindow* window)
{
    //检查用户是否按下Esc，如果按下则关闭程序
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}