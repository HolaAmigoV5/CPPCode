#include <iostream>		// #��ʾԤ����(preprocessor)ָ���������������֮ǰ
//#include "Log.h"		// includeԤ����ָ�����include���ļ�����ǰ�ļ���
#include "Main.h"
#include "LogClass.h"
#include "Log.h"	// ����Common/logͷ�ļ�

/* 
* << ��ʾ������(Operator)�����Ա����أ������Ǹ�����(function)
* windows�������У�cpp�ļ��ȱ����������������obj�ļ���Ȼ�󱻡������������ӵ���ִ��(exe)�ļ���
* �������������cpp�ļ������obj�ļ�
* �����������������obj�ļ��ù�����Ȼ���������ϵ����
*/

/*
* �������ó�static����ʾMultiplyֻ�ڵ�ǰ�ļ���Main.cpp����ʹ�ã�
* ������Main()�����в�����Multiply()�������������Ͳ�������Log()����
* ���������Log������
*/
// static int Multiply(int a, int b) {
//	Log("wby");
//	return a * b;
//}

 // ��ʾ��LNK1169: �ҵ�һ���������ض���ķ���
 // void Log(const char* message) {
	// std::cout << message << std::endl;
 //}



// main() Ϊ��ں�������������Ŀ�����н����޸�
int main() {
	//std::cout << Multiply(4, 5) << std::endl;

	// ����
	//std::cout << "****************************����************************" << std::endl;
	//Variables();

	//std::cout << "***************************ѭ��*************************" << std::endl;
	//Loops();

	//std::cout << "***********************ָ�������*************************" << std::endl;
	//PointerAndRefrence();

	//std::cout << "***********************��*************************" << std::endl;
	//CallClassDemo();

	/*LogClass log;
	log.SetLevel(Level::Levelinfo);
	log.Warn("Hello!");
	log.Error("Hello!");
	log.Info("Hello!");*/

	// ��̬��
	//CallStaticDemo();

	// �ֲ���̬
	//CallLocalStaticFunctionDemo();
	//CallLocalStaticSingletonDemo();

	// ���캯��
	//CallConstructorDemo();

	// �̳�
	//CallInheritanceDemo();

	// �麯��
	//VirtualFunctionDemo();

	// ����
	//ArraysDemo();

	// �ַ���
	//StringsDemo();

	//����
	//ConstDemo();

	// Mutable
	//MutableDemo();

	// ��Ա��ʼ���б�
	//MemberListsDemo();

	// ������
	//OperatorDemo();

	// ����ָ��
	//SmartPointerDemo();


	// ���ƺͿ������캯��
	//CopyConstructors();

	// ��ͷ����������
	//ArrowEntityDemo();

	// ��̬����Vector
	//VectorDemo();

	// ��̬�����Ż�
	//OptmizeVectorDemo();

	// ���ñ����Ŀ�е�Log
	// Common::Log log;
	// log.SetLevel(Common::Level::Levelinfo);
	// log.Error("�����ˣ�");

	//std::cout << "***********************ģ��*************************" << std::endl;
	//TemplateDemo();

	// ��
	//MacrosDemo();

	// ��̬����
	//ArrayDemo();

	// ����ָ��
	//FunctionPointers();

	// Lambda ���ʽ
	//LambdaDemo();

	// �߳�
	//ThreadDemo();

	//��ʱ
	//TimingDemo();

	//����
	//SortingDemo();


	// ����˫��
	//TypePunningDemo();

	// ������
	//UnionDemo();

	// ��̬ת��
	//DynamicCastDemo();

	// ��׼����
	//BenchmarkingDemo();

	// ��������
	//StructuredBindingDemo();


	//OptionalMain();


	// string �Ż�����
	//StringFastDemo();

	// ���ݿ��ӻ�
	//VisualBenchmarking();

	// ��������˳��
	//ArgumentEvOrder();

	// move �ƶ�
	//MoveDemo();

	// DIY Array
	//DIYArrayDemo();

	// DIY Vector
	//DIYVectorDemo();

	// ������
	IteratorDemo();

	std::cin.get();
}

#if 0	// 0��ʾ�����õĴ���, 1��ʾ���õĴ���
void PrintToConsole() {

}
#endif // 



