#include <iostream>
#include <string>

//#define WAIT std::cin.get()		// 宏代码，使用WAIT替换std::cin.get()
//#define LOG(x) std::cout<<x<<std::endl	// 宏代码

// 宏代码。debug模式下进行替换，非debug模式下将LOG(x)删除。
#ifdef PR_DEBUG
#define LOG(X) std::cout<<x<<std::endl;
#else
#define LOG(x)
#endif // PR_DEBUG

#if 0		// 表示禁用代码

#endif

void MacrosDemo() {
	//std::cin.get();
	//WAIT;

	//LOG("Hello");
}