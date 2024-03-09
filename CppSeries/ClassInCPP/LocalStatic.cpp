#include <iostream>

class Singleton
{
public:
	//static Singleton& Get() { return *s_Instance; }

	static Singleton& Get() {
		static Singleton s_Instance;
		return s_Instance;
	}
	void Hello() {
		std::cout << "Say Hello!" << std::endl;
	}
//private:
//	static Singleton* s_Instance;
};

//Singleton* Singleton::s_Instance = nullptr;		//全局变量


//void Function() {
//	static int i = 0;
//	i++;
//	std::cout << i << std::endl;
//}

//int main() {
//	/*for (int i = 0; i < 5; i++)
//	{
//		Function();
//	}*/
//	Singleton::Get().Hello();
//
//	std::cin.get();
//}