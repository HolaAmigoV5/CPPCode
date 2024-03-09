#include <iostream>

class Entity;		// 前置声明类，否则后面编译错误
void PrintEntity(Entity* e);		

class Entity
{
public:
	Entity(int x, int y) {
		this->x = x;		//普通函数里this是Entity*。相当于：Entity* e=this;
		this->y = y;

		PrintEntity(this);
	}

	int GetX() const {
		//const Entity* e = this;		// 常函数里面的this是常对象
		return x;
	}


private:
	int x, y;
};


int main()
{
    std::cout << "Hello World!\n";
}

void PrintEntity(Entity* e) {
	// Print
}

