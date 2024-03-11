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

    // �����ڴ���OpenGL��Ⱦ�����ĺ���ܵ���glewInit()
    if (glewInit() != GLEW_OK)
        std::cout << "Error\n";

    // ��ӡOpenGl�汾��
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
       -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };

    // ���ɶ��㻺������������ID
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // �󶨻�����
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // ���ö������ԡ�0�����ã�1��������
    glEnableVertexAttribArray(0);
    /* ��������
    * index: ������ʵ�����Ե�����������λ������������0λ�ã�����������1������������2
    * size: �ö��ٸ���������������ض��Ķ������ԣ�ֻ����1,2,3,4��������άλ�ã�x,y,z����3������ɫ��2��
    * type: ��ʲô�������ͱ�ʾ
    * normalized: �Ƿ�淶��
    * stride����������Ҫ��ǰ�ƶ�����ڶ���������ֽ�����ÿ������֮����ֽ�����
    * pointer: ����֮���ƫ���������λ�����Ե�����������Ҫƫ��8���ֽڣ��������8
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