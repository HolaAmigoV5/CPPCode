#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"
#include <iostream>

// 使用着色器将三角形绘制成红色
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // 错误处理
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // _malloca是C语言的函数，用于在栈上动态分配
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();   // 创建程序，返回程序对象ID引用
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);    // 着色器附加到程序
    glAttachShader(program, fs);
    glLinkProgram(program);         // 链接程序
    glValidateProgram(program);     // 程序验证

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int ShadersDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
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

    // 打印OpenGl版本号
    std::cout << glGetString(GL_VERSION) << std::endl;

    // 前面两个参数控制窗口左下角位置，后面参数设置渲染窗口的宽高
    glViewport(0, 0, 800, 600);

    // 每次窗口大小调整时调用
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);

    float positions[6] = {
       -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };

    // 生成顶点缓冲区，并返回ID
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // 绑定缓冲区
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // 启用顶点属性。0，启用；1，不启用
    glEnableVertexAttribArray(0);
    /* 顶点属性
    * index: 缓冲区实际属性的索引。比如位置属性在索引0位置，坐标索引是1，法线索引是2
    * size: 用多少个浮点数代表这个特定的顶点属性，只能是1,2,3,4。比如三维位置（x,y,z）用3个，颜色用2个
    * type: 用什么数据类型表示
    * normalized: 是否规范化
    * stride：步长，需要向前移动到达第二个顶点的字节数。每个顶点之间的字节数。
    * pointer: 属性之间的偏移量。如从位置属性到纹理属性需要偏移8个字节，这里就是8
    */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // shader
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position=position;\n"
        "}\n";

    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color=vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);   // 激活程序对象
    // end shader

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Window::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 清除所有颜色，以深蓝绿色填充
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // 释放
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
