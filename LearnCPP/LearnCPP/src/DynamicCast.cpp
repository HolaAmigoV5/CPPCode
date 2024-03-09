#include <iostream>
#include <string>

class DyEntity
{
public:
	virtual void PrintName() {}

};

class Player :public DyEntity
{
};

class Enemy :public DyEntity
{
};

void DynamicCastDemo() {
	Player* player = new Player();
	DyEntity* actuallyPlayer = player;
	DyEntity* actuallyEnemy = new Enemy();

	Player* p0 = dynamic_cast<Player*>(actuallyEnemy);	// 转换失败，p0为null
	if (p0) {
		// todo ....
	}
	Player* p1 = dynamic_cast<Player*>(actuallyPlayer);	// 转换成功，p1不为空
}
