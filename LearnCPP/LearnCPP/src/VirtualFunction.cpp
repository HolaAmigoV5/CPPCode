// �麯��
#include <string>
#include <iostream>

class Printable {
public:
	virtual std::string GetClassName() = 0;		// ���麯�����ӿ�
};

class VEntity:public Printable
{
public:
	virtual std::string GetName() { return "VEntity"; }	// virtual�鷽��
	std::string GetClassName() override { return "Class name is VEntity"; }
};

class Player :public VEntity
{
public:
	Player(const std::string& name) :m_Name(name) {}

	std::string GetName() override { return m_Name; }	// override��д
	std::string GetClassName() override { return "Class name is Player"; }
private:
	std::string m_Name;
};

void PrintName(VEntity* e) {
	std::cout << e->GetName() << std::endl;
}

void Print(Printable* obj) {
	std::cout << obj->GetClassName() << std::endl;
}

void VirtualFunctionDemo() {
	VEntity* e = new VEntity();
	//std::cout << e->GetName() << std::endl;		// �����VEntity
	PrintName(e);
	Print(e);

	Player* p = new Player("wby");
	//std::cout << p->GetName() << std::endl;		// �����wby
	PrintName(p);
	Print(p);

	VEntity* entity = p;
	//std::cout << entity->GetName() << std::endl;  // �����entity���������ó�virtual�������wby
	PrintName(entity);
}

