#include <iostream>
#include <GLFW/glfw3.h>     // <> 通常引用外部第三方的库，" "则是解决方案里面的库引用

//extern "C" int glfwInit();    // glfw3.h不include时，可以这样定义，运行

int main()
{
    int a = glfwInit();
    std::cout << a << std::endl;

    std::cin.get();
}
