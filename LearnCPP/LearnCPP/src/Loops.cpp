#include <iostream>

///****************************************************************************
/// @data    :                                                          
/// @input   :                                                                 
/// @output  :                                                                 
/// @brief   :ѭ����ʹ��                                                             
///****************************************************************************
void Loops()
{
	/*for (int i = 0; i < 5; i++)
	{
		std::cout << "Hello World!\n";
	}*/

	// ��������ͬ���������
	int i = 0;
	bool condition = true;
	for (; condition;) {
		std::cout << "Hello World!\n";
		i++;

		if (!(i < 5))
			condition = false;
	}


	std::cout << "=====================================================\n";
	int j = 0;
	while (j < 5)
	{
		/*if (j % 2 == 0)
			continue;*/
		std::cout << j << std::endl;
		std::cout << "Hello World!\n";
		j++;
	}

	std::cout << "=====================================================\n";
	int k = 0;
	do
	{
		std::cout << k << std::endl;
		std::cout << "Do while, Hello World!\n";
	} while (++k < 5);

	std::cin.get();

	//ע����++������͹�ϵ�����һ����ʱ��
	//	i++             ���ж���++
	//	++i             ��++���ж�
}

