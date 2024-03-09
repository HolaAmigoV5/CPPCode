#include <iostream>
#include <array>


int main() {
	// 栈上创建数组
	int example[5]{};  // 定义数组，生命周期在于当前方法。栈(stack)上创建
	int* ptr = example;
	for (int i = 0; i < 5; i++)
	{
		example[i] = 2;
	}

	example[2] = 5;			// 设置索引为2的元素值为5
	*(ptr + 2) = 6;			// 通过指针设置索引为2的元素值为6
	*(int*)((char*)ptr + 8) = 7;	//设置索引为2的元素值为7
	int count= sizeof(example) / sizeof(int);  //计算example数组大小，count为5
	std::cout << count << std::endl;



	// 堆上创建数组
	static const int anotherSize = 5;		// 类中常量需要是静态的
	int* another = new int[anotherSize];	//定义数组，生命周期在整个程序。堆(heap)上创建

	//int count1 = sizeof(another) / sizeof(int);		//count1为2。指针在64位操作系统中是8个字节，32位中是4个字节。
	//std::cout << count1 << std::endl;

	for (int i = 0; i < anotherSize; i++)
	{
		another[i] = 2;
	}
	delete[] another;		// 释放数组another


	// c++ 11中创建数组。上面的方式可能会更快，这种方式有边界检查，更安全
	std::array<int, 5> thired{};
	for (int i = 0; i < thired.size(); i++)
	{
		thired[i] = 3;
	}
	std::cin.get();
}