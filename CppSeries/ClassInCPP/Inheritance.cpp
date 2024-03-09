#include <iostream>

class Printable {
public:
	virtual std::string GetClassName() = 0;		// 纯虚函数，接口
};

class BaseEntity :public Printable
{
public:
	BaseEntity();
	~BaseEntity();

public:
	float X = 0, Y = 0;
	void Move(float xa, float ya) {
		X += xa;
		Y += ya;
	}

public:
	virtual std::string GetName() { return "BaseEntity"; }
	std::string GetClassName() override { return "BaseEntity"; }

private:

};

class Player :public BaseEntity
{
public:
	Player();
	~Player();


public:
	/*const char* Name;

	void PrintName() {
		std::cout << Name << std::endl;
	}*/

public:
	Player(const std::string& name) :m_Name(name) {
		// 构造函数使用初始化列表
	}
	std::string GetName() override { return m_Name; }
	std::string GetClassName() override { return "Player"; }
private:
	std::string m_Name;
};

Player::Player()
{
	//Name = "wby";
}

Player::~Player()
{
}

BaseEntity::BaseEntity()
{
}

BaseEntity::~BaseEntity()
{
}

void PrintName(BaseEntity* entity) {
	std::cout << entity->GetName() << std::endl;
}

void Print(Printable* obj) {
	std::cout << obj->GetClassName() << std::endl;
}

//int main() {
//	/*std::cout <<"BaseEntity Size: "<< sizeof(BaseEntity) << std::endl;
//	std::cout << "Player Size: " << sizeof(Player) << std::endl;
//
//
//	Player player;
//	player.Move(5, 3);
//	player.X = 2;*/
//	//player.PrintName();
//
//	/*BaseEntity e;
//	std::cout << e.GetName() << std::endl;
//
//	Player p("wby");
//	std::cout << p.GetName() << std::endl;*/
//
//	BaseEntity* e = new BaseEntity();
//	//std::cout << e->GetName() << std::endl;
//	//PrintName(e);
//	Print(e);
//
//	Player* p = new Player("wby");
//	//PrintName(p);
//	//std::cout << p->GetName() << std::endl;
//	Print(p);
//
//
//	std::cin.get();
//
//}