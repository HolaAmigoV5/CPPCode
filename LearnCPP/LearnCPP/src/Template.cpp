#include <iostream>
#include <string>

template<typename T>

// ��������ʱ�Ż�ʹ��ģ����д��������򲻻ᴴ��
void Print(T value) {
	std::cout << value << std::endl;
}

// ģ���ж���TΪArrayԪ�����ͣ�NΪint���͵�Ԫ�ظ���
template<typename T, int N>

class Array
{
public:
	int GetSize() const { return N; }

private:
	T m_Array[N];
};


void TemplateDemo() {
	Print(5);
	Print("Hello");
	Print(5.5f);

	Array<int,5> array;
	std::cout << array.GetSize() << std::endl;
}

