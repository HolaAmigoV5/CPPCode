#include "WindowsWindow.h"

// ÿ�δ��ڱ任ʱ���ӿڵ����ص�
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::processInput(GLFWwindow* window)
{
    //����û��Ƿ���Esc�����������رճ���
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}