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

	// Lambda ���ʽ��[]���������x������&x������=������ֱ��&
	// [x]  ��ʾx��ֵ����
	// [&x] ��ʾx�����ô���
	// [&] ��ʾ���б������������ô���
	// [=] ��ʾ���б�������ֵ����
	auto lambda = [=](int value) {std::cout << "Value: " << a + value << std::endl; };
	ForEach(values, lambda);

	std::cout << "===============================" << std::endl;
	// ����values���飬���ش���3�ĵ�һ����
	auto it = std::find_if(values.begin(), values.end(), [](int value) {return value > 3; });
	std::cout << *it << std::endl;
}

