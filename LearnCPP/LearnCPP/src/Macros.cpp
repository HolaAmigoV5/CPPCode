#include <iostream>
#include <string>

//#define WAIT std::cin.get()		// ����룬ʹ��WAIT�滻std::cin.get()
//#define LOG(x) std::cout<<x<<std::endl	// �����

// ����롣debugģʽ�½����滻����debugģʽ�½�LOG(x)ɾ����
#ifdef PR_DEBUG
#define LOG(X) std::cout<<x<<std::endl;
#else
#define LOG(x)
#endif // PR_DEBUG

#if 0		// ��ʾ���ô���

#endif

void MacrosDemo() {
	//std::cin.get();
	//WAIT;

	//LOG("Hello");
}