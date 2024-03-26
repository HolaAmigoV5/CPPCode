#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "glm\gtc\matrix_transform.hpp"


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


float deltaTime = 0.0f;     // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f;     // ��һ֡ʱ��
static void ProcessInputWASD(GLFWwindow* window)
{
    // �ı��ƶ��ٶ�
    float cameraSpeed = 2.5f * deltaTime;

    //����û��Ƿ���Esc�����������رճ���
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   // ��ǰ
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // ���
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // ����
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // ���ң�ʹ��cross��˴���������
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

float lastX = 400, lastY = 300; // ���ԭʼλ��
float pitch = 0.0f, yaw = -90.0f; // �����Ǻ�ƫ����
bool firstMouse = true;

// ����¼������ص��������λ��ת��Ϊ�����Ǻ�ƫ���ǣ��Ӷ�ȷ�����ǰ����������
static void Mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;   // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
    lastX = (float)xpos;
    lastY = (float)ypos;

    float sensitivity = 0.1f;  //������
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // �����ǽ�������
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front{};
    //glm::radians() �Ƕ���ת������
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
}

// �����ֻص��������ֹ���ʱ��ʵ�����š����ż���������1.0f��180.0f֮�䡣
float fov = 45.0f;
static void Scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    //std::cout << "Fov = " << fov << std::endl;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 180.0f)
        fov = 45.0f;
}

int CameraCubeDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TexturesDemo", NULL, NULL);
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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // ÿ�δ��ڴ�С����ʱ����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ���ع�꣬����׽��
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // ע������ƶ��ص�
    glfwSetCursorPosCallback(window, Mouse_callback);

    // ע�������ֻص��¼�
    glfwSetScrollCallback(window, Scroll_callback);

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;

    //������Ȳ���
    glEnable(GL_DEPTH_TEST);

    {
        float vertices[] = {
            // ---- λ�� ----     - �������� -
            // ǰ��  
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 0  
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 1  
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 2  
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 3  

             // ����  
              0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 4  
             -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 5  
             -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 6  
              0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 7 
        };


        // ��������
        unsigned int indices[] = {
            // ǰ��  
            0, 1, 2,
            2, 3, 0,
            // ����  
            4, 5, 6,
            6, 7, 4,
            // ����  
            0, 4, 5,
            5, 1, 0,
            // ����  
            3, 7, 6,
            6, 2, 3,
            // ���  
            1, 5, 6,
            6, 2, 1,
            // �Ҳ�  
            0, 3, 7,
            7, 4, 0
        };

        VertexArray va;
        VertexBuffer vb(vertices, sizeof(vertices));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 36);


        // shader
        Shader shader("res/shaders/Cube.shader");
        shader.Bind();
        // end shader

        // Texture
        Texture texture("res/textures/xm.png");
        shader.SetUniform1i("u_Texture", 0);

        Texture texture1("res/textures/mlo.png");
        shader.SetUniform1i("u_Texture1", 1);
        // end Texture

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        glm::vec3 cubePositions[] = {
           glm::vec3(0.0f,  0.0f,  0.0f),
           glm::vec3(2.0f,  5.0f, -15.0f),
           glm::vec3(-1.5f, -2.2f, -2.5f),
           glm::vec3(-3.8f, -2.0f, -12.3f),
           glm::vec3(2.4f, -0.4f, -3.5f),
           glm::vec3(-1.7f,  3.0f, -7.5f),
           glm::vec3(1.3f, -2.0f, -2.5f),
           glm::vec3(1.5f,  2.0f, -2.5f),
           glm::vec3(1.5f,  0.2f, -1.5f),
           glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        float radius = 10.0f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = (float)glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // ����������WASD�¼�
            ProcessInputWASD(window);

            /* Render here */
            renderer.Clear();

            texture.Bind(0);
            texture1.Bind(1);

            // ����MVP�任
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 proj = glm::mat4(1.0f);

            // ͨ���ı�fovʵ�ֹ�������
            proj = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // �ü��̿��������ƶ�
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


            for (unsigned int i = 0; i < 10; i++) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);


                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));

                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("transform", mvp);

                renderer.Draw(va, ib, shader);
            }


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
