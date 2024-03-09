
///****************************************************************************          
/// @brief   : �ֲ���̬(local static)�������������൱����������������ڣ�
/// Ȼ�����÷�Χ�����ں����ڡ�����ֲ���̬�����������ñ������ñ�¶�����汻�����޸�
/// @author  : Wby
/// @date    :                                             
///****************************************************************************

#include <iostream>

void Function() {
	static int i = 0;			// �ֲ���̬����
	i++;
	std::cout << i << std::endl;
}

void CallLocalStaticFunctionDemo() {
	for (int i = 0; i < 5; i++)
	{
		Function();
	}
}


class Singleton
{
public:
	static Singleton& Get() {
		static Singleton s_Instance;	// �ֲ���̬����
		return s_Instance;
	}
	void Hello() {
		std::cout << "Say Hello!" << std::endl;
	}
};

void CallLocalStaticSingletonDemo() {
	Singleton::Get().Hello();
}