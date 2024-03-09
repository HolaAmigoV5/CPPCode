#include <iostream>
#include <array>

template <typename T, int N>

void PrintArray(const std::array<T, N>& data) {
	for (int i = 0; i < N; i++)
	{
		std::cout << data[i] << std::endl;
	}
}

void ArrayDemo() {
	std::array<int, 5> data;  // 新的定义
	for (int i = 0; i < 5; i++) {
		data[i] = i;
	}

	PrintArray(data);

	std::array<char, 2> charData;
	charData[0] = 'a';
	charData[1] = 'b';
	PrintArray(charData);

	char dataOld[5];	 // 旧的定义
	dataOld[0] = 'a';

}