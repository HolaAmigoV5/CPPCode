// ����
#include <iostream>
#include <array>

void ArraysDemo() {
	// ջ�ϴ������飨�Ƽ�����ֹ�ڴ���Ѱַ��
	int example[5]{};
	int* ptr = example;		// ����ʵ���Ǹ�����ָ��

	int count = sizeof(example) / sizeof(int);	// ��������Ԫ�ظ�����cout=5;
	std::cout << "����Ĵ�СΪ��" << sizeof(example) << std::endl;	// 20
	std::cout << "����Ԫ�ظ���Ϊ��" << count << std::endl;	// 5
	
	for (int i = 0; i < 5; i++)
	{
		example[i] = 2;
	}

	*(ptr + 2) = 6;			// ͨ��ָ����������Ϊ2��Ԫ��ֵΪ6
	*(int*)((char*)ptr + 8) = 7;	//��������Ϊ2��Ԫ��ֵΪ7


	// ���ϴ�������
	static const int anotherSize = 5;		// ���г�����Ҫ�Ǿ�̬��
	int* another = new int[anotherSize];	//�������飬�����������������򡣶�(heap)�ϴ���

	// ָ����64λ����ϵͳ����8���ֽڣ�32λ����4���ֽڡ�
	//int count1 = sizeof(another) / sizeof(int);
	//std::cout << count1 << std::endl;		// count1Ϊ2��

	for (int i = 0; i < anotherSize; i++)
	{
		another[i] = 2;
	}
	delete[] another;		// �ͷ�����another

	// c++ 11�д������顣����ķ�ʽ���ܻ���죬���ַ�ʽ�б߽��飬����ȫ
	std::array<int, 5> thired{};
	for (int i = 0; i < thired.size(); i++)
	{
		thired[i] = 3;
	}
}