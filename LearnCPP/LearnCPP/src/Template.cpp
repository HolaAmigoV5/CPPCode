#include <iostream>
#include <string>

template<typename T>

// 方法调用时才会使用模板进行创建，否则不会创建
void Print(T value) {
	std::cout << value << std::endl;
}

// 模板中定义T为Array元素类型，N为int类型的元素个数
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

