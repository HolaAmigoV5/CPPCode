
///****************************************************************************          
/// @brief   : 局部静态(local static)变量的生存期相当于整个程序的生存期，
/// 然而作用范围限制在函数内。定义局部静态变量，可以让变量不用暴露在外面被随意修改
/// @author  : Wby
/// @date    :                                             
///****************************************************************************

#include <iostream>

void Function() {
	static int i = 0;			// 局部静态变量
	i++;
	std::cout << i << std::endl;
}

void CallLocalStaticFunctionDemo() {
	for (int i = 0; i < 5; i++)
	{
		Function();
	}
}


class Singleton
{
public:
	static Singleton& Get() {
		static Singleton s_Instance;	// 局部静态变量
		return s_Instance;
	}
	void Hello() {
		std::cout << "Say Hello!" << std::endl;
	}
};

void CallLocalStaticSingletonDemo() {
	Singleton::Get().Hello();
}