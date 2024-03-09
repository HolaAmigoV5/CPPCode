
#include <iostream>
#include <string>

class Entity
{
public:
	 const std::string& GetName() const {
		 m_DebugCount++;
		return m_Name;
	}

private:
	std::string m_Name;
	mutable int m_DebugCount = 0;		//mutable 允许函数是常量方法，但可以修改变量
};



int main()
{
	const Entity e;
	e.GetName();

	int x = 8;
	int y = 6;

	// Lambda 表达式。[]里面可以是x，或者&x，或者=，或者直接&
	// [x]  表示x的值传参
	// [&x] 表示x的引用传参
	// [&] 表示所有变量都可以引用传参
	// [=] 表示所有变量进行值传参
	auto f = [=]() {
		//x++;		//编译错误：x无法在非可变lambda中修改。下面代码可实现
		int a = x;
		a++;

		std::cout << a << std::endl;
		std::cout << y << std::endl;
		};

	f();

	// mutable 在lambda中的使用。（极少使用）
	auto g = [=]() mutable{
		x++;	// 编译成功
		std::cout << x << std::endl;
		std::cout << y << std::endl;
		};

	g();
	std::cout << x << std::endl;		// 8，x按值传参自增不影响外部。按引用传参会改变

	std::cin.get();
}


