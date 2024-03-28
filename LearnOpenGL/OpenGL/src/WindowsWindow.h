#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern Camera camera;

extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
extern void processInput(GLFWwindow* window);

extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
extern void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
extern void processInputWASD(GLFWwindow* window, float deltaTime);
