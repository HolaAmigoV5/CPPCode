#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	// ����ص�
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//�������봦��
	static void processInput(GLFWwindow* window);
};
