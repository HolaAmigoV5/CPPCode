#include <iostream>

class Player
{
public:
	int x, y, speed;
	void Move(int xa, int ya) {
		x += xa * speed;
		y += ya * speed;
	}
	Player() :x(0), y(0), speed(0) {}

	~Player()
	{
	}

private:

};

void CallClassDemo() {
	Player player;		// ����һ�����ʵ��player
	player.x = 5;
	player.speed = 2;
	player.Move(2, 3);

	std::cout << "����Move()��x = " << player.x << ", " << "y = " << player.y << std::endl;
}

//static int s_Variable = 5;		//��̬������ֻ��.cpp�ڲ����Ӹñ������ⲿ������
