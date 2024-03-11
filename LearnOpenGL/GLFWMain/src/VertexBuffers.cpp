#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int VertexBuffersDemo()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
