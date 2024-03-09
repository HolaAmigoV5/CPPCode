// ���ؼ�ͷ������
// ʹ�ü�ͷ���������ȡ�ڴ���ĳ��ֵ��ƫ����

#include <iostream>

class ArrowEntity
{
public:
	int x;
	void Print() const {
		std::cout << "Hello!" << std::endl;
	}
};

class ScopedPtr
{
public:
	ScopedPtr(ArrowEntity* entity)
		:m_Obj(entity) {
	}

	~ScopedPtr() {
		delete m_Obj;
	}

	// ���ز�����->
	ArrowEntity* operator->() {
		return m_Obj;
	}

	// ���ز�����
	const ArrowEntity* operator->() const {
		return m_Obj;
	}

private:
	ArrowEntity* m_Obj;
};

struct Vector3
{
	float x, y, z;
};

void ArrowEntityDemo() {
	// ָ�뺯������
	ScopedPtr entity = new ArrowEntity();
	entity->Print();

	// ��ȡ�ڴ�ƫ����
	// &((Vector3*)nullptr)->z Ȼ��ǿ��ת��Ϊint
	float* offset = (float*)&((Vector3*)nullptr)->z;		//��ȡz���ڴ��ַ��Ϊ8
	std::cout << offset << std::endl;  // x,y,z��ַ����Ϊ0,4,8
}