// 虚函数
#include <string>
#include <iostream>

class Printable {
public:
	virtual std::string GetClassName() = 0;		// 纯虚函数，接口
};

class VEntity:public Printable
{
public:
	virtual std::string GetName() { return "VEntity"; }	// virtual虚方法
	std::string GetClassName() override { return "Class name is VEntity"; }
};

class Player :public VEntity
{
public:
	Player(const std::string& name) :m_Name(name) {}

	std::string GetName() override { return m_Name; }	// override重写
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
	//std::cout << e->GetName() << std::endl;		// 输出：VEntity
	PrintName(e);
	Print(e);

	Player* p = new Player("wby");
	//std::cout << p->GetName() << std::endl;		// 输出：wby
	PrintName(p);
	Print(p);

	VEntity* entity = p;
	//std::cout << entity->GetName() << std::endl;  // 输出：entity。基类设置成virtual后，输出：wby
	PrintName(entity);
}

