#include <iostream>
#include <array>


int main() {
	// ջ�ϴ�������
	int example[5]{};  // �������飬�����������ڵ�ǰ������ջ(stack)�ϴ���
	int* ptr = example;
	for (int i = 0; i < 5; i++)
	{
		example[i] = 2;
	}

	example[2] = 5;			// ��������Ϊ2��Ԫ��ֵΪ5
	*(ptr + 2) = 6;			// ͨ��ָ����������Ϊ2��Ԫ��ֵΪ6
	*(int*)((char*)ptr + 8) = 7;	//��������Ϊ2��Ԫ��ֵΪ7
	int count= sizeof(example) / sizeof(int);  //����example�����С��countΪ5
	std::cout << count << std::endl;



	// ���ϴ�������
	static const int anotherSize = 5;		// ���г�����Ҫ�Ǿ�̬��
	int* another = new int[anotherSize];	//�������飬�����������������򡣶�(heap)�ϴ���

	//int count1 = sizeof(another) / sizeof(int);		//count1Ϊ2��ָ����64λ����ϵͳ����8���ֽڣ�32λ����4���ֽڡ�
	//std::cout << count1 << std::endl;

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
	std::cin.get();
}