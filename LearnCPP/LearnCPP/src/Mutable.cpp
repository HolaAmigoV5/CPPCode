#include <iostream>

class MutableEntity
{
public:
	const std::string& GetName() const {
		m_DebugCount++;
		return m_Name;
	}

private:
	std::string m_Name;
	mutable int m_DebugCount = 0;		//mutable �������ǳ����������������޸ı���
};

void MutableDemo() {
	const MutableEntity e;
	e.GetName();

	int x = 8;
	int y = 6;

	// Lambda ���ʽ��[]���������x������&x������=������ֱ��&
	// [x]  ��ʾx��ֵ����
	// [&x] ��ʾx�����ô���
	// [&] ��ʾ���б������������ô���
	// [=] ��ʾ���б�������ֵ����
	auto f = [=]() {
		//x++;		//�������x�޷��ڷǿɱ�lambda���޸ġ���������ʵ��
		int a = x;
		a++;

		std::cout << a << std::endl;
		std::cout << y << std::endl;
		};

	f();

	// mutable ��lambda�е�ʹ�á�������ʹ�ã�
	auto g = [=]() mutable {
		x++;	// ����ɹ�
		std::cout << x << std::endl;
		std::cout << y << std::endl;
		};

	g();
	std::cout << x << std::endl;		// 8��x��ֵ����������Ӱ���ⲿ�������ô��λ�ı�
}