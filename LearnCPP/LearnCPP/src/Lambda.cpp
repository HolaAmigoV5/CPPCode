#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

void ForEach(const std::vector<int>& values, const std::function<void(int)>& func) {
	for (auto& value : values)
	{
		func(value);
	}
}

void LambdaDemo() {
	std::vector<int> values = { 1,4,5,6,7,8 };
	int a = 5;

	// Lambda 表达式。[]里面可以是x，或者&x，或者=，或者直接&
	// [x]  表示x的值传参
	// [&x] 表示x的引用传参
	// [&] 表示所有变量都可以引用传参
	// [=] 表示所有变量进行值传参
	auto lambda = [=](int value) {std::cout << "Value: " << a + value << std::endl; };
	ForEach(values, lambda);

	std::cout << "===============================" << std::endl;
	// 遍历values数组，返回大于3的第一个数
	auto it = std::find_if(values.begin(), values.end(), [](int value) {return value > 3; });
	std::cout << *it << std::endl;
}

