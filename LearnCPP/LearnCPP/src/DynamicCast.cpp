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

	Player* p0 = dynamic_cast<Player*>(actuallyEnemy);	// ת��ʧ�ܣ�p0Ϊnull
	if (p0) {
		// todo ....
	}
	Player* p1 = dynamic_cast<Player*>(actuallyPlayer);	// ת���ɹ���p1��Ϊ��
}
