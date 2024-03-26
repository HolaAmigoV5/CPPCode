#include "WindowsWindow.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// 每次窗口变换时，视口调整回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    //检查用户是否按下Esc，如果按下则关闭程序
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


bool m_FirstMouse = true;
float m_LastX = 0.0f;
float m_LastY = 0.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll((float)yoffset);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (m_FirstMouse) {
        m_LastX = xpos;
        m_LastY = ypos;
        m_FirstMouse = false;
    }

    float xoffset = xpos - m_LastX;
    float yoffset = m_LastY - ypos;   // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    m_LastX = xpos;
    m_LastY = ypos;

    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    camera.UpdateCameraYawAndPitch(xoffset, yoffset);
}

void processInputWASD(GLFWwindow* window, float deltaTime)
{
    //检查用户是否按下Esc，如果按下则关闭程序
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   // 向前
        camera.UpdatePosition(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // 向后
        camera.UpdatePosition(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // 向左
        camera.UpdatePosition(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // 向右
        camera.UpdatePosition(RIGHT, deltaTime);
}
