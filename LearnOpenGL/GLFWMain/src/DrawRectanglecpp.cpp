
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"

#include <iostream>

int DrawRectangleDemo()
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
    window = glfwCreateWindow(800, 600, "DrawRectangle", NULL, NULL);
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

    // 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 检查是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 编译片段着色器
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

    // 链接着色器
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

    // 定义顶点数据
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
       -0.5f, -0.5f, 0.0f,  // 左下角
       -0.5f,  0.5f, 0.0f   // 左上角
    };
    unsigned int indices[] = {  
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // 生成VAO
    glGenBuffers(1, &VBO);      // 生成VBO对象
    glGenBuffers(1, &EBO);      // 生成EBO

    // 先绑定VAO，然后绑定VBO，最后配置顶点属性
    glBindVertexArray(VAO);

    // 绑定VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // VBO缓冲类型设置GL_ARRAY_BUFFER
    // 顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // 解绑VBO
    glBindVertexArray(0);               // 解绑VAO

    // 获取最大顶点支持数
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported:" << nrAttributes << std::endl;

    // 渲染循环：窗口不关闭就不断渲染
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 清除所有颜色，以深蓝绿色填充
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制矩形
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 线框模式绘制
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 交换颜色缓冲
        glfwSwapBuffers(window);

        // 检查是否触发事件（如键盘输入，鼠标移动等）
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();    // 释放/删除之前分配的所有资源
    return 0;
}
