#include<iostream>
#include <algorithm>
#include <vector>
#include <functional>

void SortingDemo() {
	std::vector<int> values = { 3,5,1,4,2 };
	//std::sort(values.begin(), values.end());	//默认升序
	//std::sort(values.begin(), values.end(), std::greater<int>());  // 降序排序

	//自定义排序：true，a在前面；false，b在前面
	std::sort(values.begin(), values.end(), [](int a, int b) {
		return a < b;	// 升序
		//return a > b;	// 降序
		});


	for (auto& value : values)
	{
		std::cout << value << std::endl;
	}
}