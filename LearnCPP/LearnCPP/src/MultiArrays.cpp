#include <iostream>

void MultiArraysDemo() {
	// 二维数组定义
	int** a2d = new int* [50];	// 设置50个指针
	for (int i = 0; i < 50; i++) {
		a2d[i] = new int[50];	// a2d里的每个元素，都分配一个50元素的数组
	}

	// 二维数组赋值
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			a2d[x][y] = 2;
		}
	}

	// 二维数组销毁
	for (int i = 0; i < 50; i++)
	{
		delete[] a2d[i];
	}
	delete[] a2d;

	// 二维数组优化。访问内存中同一行的内存
	int* array = new int[5 * 5];
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			array[x + y * 5] = 2;
		}
	}

	// 三维数组
	int*** a3d = new int** [50];
	for (int i = 0; i < 50; i++) {
		a3d[i] = new int* [50];
		for (int j = 0; j < 50; j++)
		{
			a3d[i][j] = new int[50];
		}
	}
}