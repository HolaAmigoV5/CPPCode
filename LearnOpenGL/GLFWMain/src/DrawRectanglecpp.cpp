
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"

#include <iostream>

int DrawRectangleDemo()
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
    window = glfwCreateWindow(800, 600, "DrawRectangle", NULL, NULL);
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

    // build and compile our shader program
    // -----------------------------------------------------------------------
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    // ���붥����ɫ��
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // ����Ƿ����ɹ�
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ����Ƭ����ɫ��
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ������ɫ��
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // ���嶥������
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // ���Ͻ�
        0.5f, -0.5f, 0.0f,  // ���½�
       -0.5f, -0.5f, 0.0f,  // ���½�
       -0.5f,  0.5f, 0.0f   // ���Ͻ�
    };
    unsigned int indices[] = {  
        // ע��������0��ʼ! 
        // ����������(0,1,2,3)���Ƕ�������vertices���±꣬
        // �����������±��������ϳɾ���
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // ����VAO
    glGenBuffers(1, &VBO);      // ����VBO����
    glGenBuffers(1, &EBO);      // ����EBO

    // �Ȱ�VAO��Ȼ���VBO��������ö�������
    glBindVertexArray(VAO);

    // ��VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // VBO������������GL_ARRAY_BUFFER
    // �������ݸ��Ƶ�������ڴ���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ��EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ���ö�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // ���VBO
    glBindVertexArray(0);               // ���VAO

    // ��ȡ��󶥵�֧����
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported:" << nrAttributes << std::endl;

    // ��Ⱦѭ�������ڲ��رվͲ�����Ⱦ
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // ���������ɫ����������ɫ���
        glClear(GL_COLOR_BUFFER_BIT);

        // ���ƾ���
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // �߿�ģʽ����
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ������ɫ����
        glfwSwapBuffers(window);

        // ����Ƿ񴥷��¼�����������룬����ƶ��ȣ�
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();    // �ͷ�/ɾ��֮ǰ�����������Դ
    return 0;
}
