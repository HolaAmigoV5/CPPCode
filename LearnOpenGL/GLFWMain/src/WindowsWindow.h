#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
	// 定义回调
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//定义输入处理
	static void processInput(GLFWwindow* window);
};
