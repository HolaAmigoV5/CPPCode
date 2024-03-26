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


float deltaTime = 0.0f;     // 当前帧与上一帧的时间差
float lastFrame = 0.0f;     // 上一帧时间
static void ProcessInputWASD(GLFWwindow* window)
{
    // 改变移动速度
    float cameraSpeed = 2.5f * deltaTime;

    //检查用户是否按下Esc，如果按下则关闭程序
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   // 向前
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // 向后
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // 向左
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // 向右，使用cross叉乘创建右向量
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

float lastX = 400, lastY = 300; // 鼠标原始位置
float pitch = 0.0f, yaw = -90.0f; // 俯仰角和偏航角
bool firstMouse = true;

// 鼠标事件监听回调，将鼠标位置转换为俯仰角和偏航角，从而确定相机前方方向向量
static void Mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;   // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = (float)xpos;
    lastY = (float)ypos;

    float sensitivity = 0.1f;  //灵敏度
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // 俯仰角进行限制
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front{};
    //glm::radians() 角度制转弧度制
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
}

// 鼠标滚轮回调，鼠标滚轮滚动时，实现缩放。缩放级别限制在1.0f到180.0f之间。
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

    // 必须在创建OpenGL渲染上下文后才能调用glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 隐藏光标，并捕捉它
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 注册鼠标移动回调
    glfwSetCursorPosCallback(window, Mouse_callback);

    // 注册鼠标滚轮回调事件
    glfwSetScrollCallback(window, Scroll_callback);

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;

    //启动深度测试
    glEnable(GL_DEPTH_TEST);

    {
        float vertices[] = {
            // ---- 位置 ----     - 纹理坐标 -
            // 前面  
             0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 0  
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 1  
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 2  
             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 3  

             // 后面  
              0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 4  
             -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 5  
             -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 6  
              0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 7 
        };


        // 定义索引
        unsigned int indices[] = {
            // 前面  
            0, 1, 2,
            2, 3, 0,
            // 后面  
            4, 5, 6,
            6, 7, 4,
            // 上面  
            0, 4, 5,
            5, 1, 0,
            // 下面  
            3, 7, 6,
            6, 2, 3,
            // 左侧  
            1, 5, 6,
            6, 2, 1,
            // 右侧  
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

            // 监听键盘上WASD事件
            ProcessInputWASD(window);

            /* Render here */
            renderer.Clear();

            texture.Bind(0);
            texture1.Bind(1);

            // 进行MVP变换
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 proj = glm::mat4(1.0f);

            // 通过改变fov实现滚轮缩放
            proj = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            // 用键盘控制自由移动
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
