#include <iostream>

void MultiArraysDemo() {
	// ��ά���鶨��
	int** a2d = new int* [50];	// ����50��ָ��
	for (int i = 0; i < 50; i++) {
		a2d[i] = new int[50];	// a2d���ÿ��Ԫ�أ�������һ��50Ԫ�ص�����
	}

	// ��ά���鸳ֵ
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			a2d[x][y] = 2;
		}
	}

	// ��ά��������
	for (int i = 0; i < 50; i++)
	{
		delete[] a2d[i];
	}
	delete[] a2d;

	// ��ά�����Ż��������ڴ���ͬһ�е��ڴ�
	int* array = new int[5 * 5];
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			array[x + y * 5] = 2;
		}
	}

	// ��ά����
	int*** a3d = new int** [50];
	for (int i = 0; i < 50; i++) {
		a3d[i] = new int* [50];
		for (int j = 0; j < 50; j++)
		{
			a3d[i][j] = new int[50];
		}
	}
}