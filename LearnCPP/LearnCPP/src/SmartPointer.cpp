#include <iostream>
#include <memory>


// ����ָ�룬�����Զ����ն��ϴ����Ķ��������ֶ�delete��
// unique_ptr ��������ָ�룬����������ʱ�����ᱻ���٣����ܸ���
// shared_ptr ����ָ�룬ͨ�����ü�������ָ���ж������ã�������Ϊ0ʱ���ͱ�delete
// weak_ptr �����������ü���


class SmartEntity
{
public:
	SmartEntity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~SmartEntity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print() {
		std::cout << "Print SmartEntity" << std::endl;
	}
};

void SmartPointerDemo() {
	std::shared_ptr<SmartEntity> e1;
	std::weak_ptr<SmartEntity> weakEntity;

	{
		//std::unique_ptr<SmartEntity> entity = new SmartEntity(); //����unique_ptr����ʾת��
		//std::unique_ptr<SmartEntity> entity(new SmartEntity());
		
		// make_unique��c++14�����룬11��֧�֡�
		// �����캯�������׳��쳣���ᰲȫЩ���Ƽ�д����
		std::unique_ptr<SmartEntity> entity = std::make_unique<SmartEntity>();

		// �������캯���Ϳ��������������ʵ�ʱ�ɾ����
		//std::unique_ptr<SmartEntity> e0 = entity;  // �������

		entity->Print();

		// ����ָ�룬���Ը���
		std::shared_ptr<SmartEntity> sharedEntity = std::make_shared<SmartEntity>();
		e1 = sharedEntity;

		weakEntity = sharedEntity; // ���ﲻ���������ü�������������ᱻ����
	}
}
