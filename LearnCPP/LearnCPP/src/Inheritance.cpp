
///****************************************************************************          
/// @brief   : ผฬณะ  
/// @author  : Wby
/// @date    :                                              
///****************************************************************************

#include <iostream>

class BaseEntity
{
public:
	BaseEntity()
	{
	}

	~BaseEntity()
	{
	}

public:
	float X = 0, Y = 0;
	void Move(float xa, float ya) {
		X += xa;
		Y += ya;

		std::cout << "x= " << X << ", " << "Y= " << Y << std::endl;
	}
};

class Player :public BaseEntity
{
public:
	Player()
	{
		Name = "wby";
	}

	~Player()
	{
	}

public:
	const char* Name;

	void PrintName()
	{
		std::cout << Name << std::endl;
	}
};

void CallInheritanceDemo() {
	std::cout << "BaseEntity Size: " << sizeof(BaseEntity) << std::endl;	// 8
	std::cout << "Player Size: " << sizeof(Player) << std::endl;			// 16

	Player player;
	player.Move(5, 5);
	player.X = 2;
}

