#include <iostream>
#include <vector>

void PrintValue(int value) {
	std::cout << "Value: " << value << std::endl;
}

// ��������Ϊ�������д��ݵ���
void ForEach(const std::vector<int>& values, void(*func)(int)) {
	for (int value : values)
		func(value);
}

void HelloWorld(int a) {
	std::cout << "Hello World! Value: " << a << std::endl;
}

void FunctionPointers() {
	//auto function = HelloWorld;	// ���غ�����ָ��
	//void(*function)() = HelloWorld;	// ����������Ч

	//function();
	//function();

	typedef void(*HelloWorldFunction)(int);
	HelloWorldFunction function = HelloWorld;
	function(8);

	std::vector<int> values = { 1,3,4,6,7,0 };
	//ForEach(values, PrintValue);

	// lambda���ʽ
	/*ForEach(values, [](int value) {
		std::cout << "Value: " << value << std::endl;
		});*/

	auto lambda = [](int value) {std::cout << "Value: " << value << std::endl; };
	ForEach(values, lambda);
}