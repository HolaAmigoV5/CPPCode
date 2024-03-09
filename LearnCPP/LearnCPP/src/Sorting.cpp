#include<iostream>
#include <algorithm>
#include <vector>
#include <functional>

void SortingDemo() {
	std::vector<int> values = { 3,5,1,4,2 };
	//std::sort(values.begin(), values.end());	//Ĭ������
	//std::sort(values.begin(), values.end(), std::greater<int>());  // ��������

	//�Զ�������true��a��ǰ�棻false��b��ǰ��
	std::sort(values.begin(), values.end(), [](int a, int b) {
		return a < b;	// ����
		//return a > b;	// ����
		});


	for (auto& value : values)
	{
		std::cout << value << std::endl;
	}
}