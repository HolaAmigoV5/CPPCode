#include "WindowsWindow.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// ÿ�δ��ڱ任ʱ���ӿڵ����ص�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    //����û��Ƿ���Esc�����������رճ���
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
    float yoffset = m_LastY - ypos;   // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
    m_LastX = xpos;
    m_LastY = ypos;

    xoffset *= SENSITIVITY;
    yoffset *= SENSITIVITY;

    camera.UpdateCameraYawAndPitch(xoffset, yoffset);
}

void processInputWASD(GLFWwindow* window, float deltaTime)
{
    //����û��Ƿ���Esc�����������رճ���
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   // ��ǰ
        camera.UpdatePosition(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // ���
        camera.UpdatePosition(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // ����
        camera.UpdatePosition(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // ����
        camera.UpdatePosition(RIGHT, deltaTime);
}
