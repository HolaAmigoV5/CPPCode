
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"


int GLFWDemo()
{
    GLFWwindow* window;

    // ��ʼ��GLFW
    if (!glfwInit())
        return -1;

    // ����OpenGL�汾Ϊ3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ����ģʽ����
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Mac OS Xϵͳ���ò���������

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // ��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // ǰ�������������ƴ������½�λ�ã��������������Ⱦ���ڵĿ��
    glViewport(0, 0, 800, 600);

    // ÿ�δ��ڴ�С����ʱ����
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    // ��Ⱦѭ�������ڲ��رվͲ�����Ⱦ
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // ���������ɫ����������ɫ���
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ɫ����
        glfwSwapBuffers(window);    

        // ����Ƿ񴥷��¼�����������룬����ƶ��ȣ�
        glfwPollEvents();
    }

    glfwTerminate();    // �ͷ�/ɾ��֮ǰ�����������Դ
    return 0;
}