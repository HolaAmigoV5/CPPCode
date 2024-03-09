#include <iostream>
#include <vector>

void PrintValue(int value) {
	std::cout << "Value: " << value << std::endl;
}

// 将方法作为参数进行传递调用
void ForEach(const std::vector<int>& values, void(*func)(int)) {
	for (int value : values)
		func(value);
}

void HelloWorld(int a) {
	std::cout << "Hello World! Value: " << a << std::endl;
}

void FunctionPointers() {
	//auto function = HelloWorld;	// 返回函数的指针
	//void(*function)() = HelloWorld;	// 和上面代码等效

	//function();
	//function();

	typedef void(*HelloWorldFunction)(int);
	HelloWorldFunction function = HelloWorld;
	function(8);

	std::vector<int> values = { 1,3,4,6,7,0 };
	//ForEach(values, PrintValue);

	// lambda表达式
	/*ForEach(values, [](int value) {
		std::cout << "Value: " << value << std::endl;
		});*/

	auto lambda = [](int value) {std::cout << "Value: " << value << std::endl; };
	ForEach(values, lambda);
}