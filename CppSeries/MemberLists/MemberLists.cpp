// 成员初始化列表，推荐使用。如果用赋值方式进行初始化，可能会重复调用构造，重复构造对象

#include <iostream>

class Example
{
public:
	Example() {
		std::cout << "Create 1 Example" << std::endl;
	}

	Example(int x) {
		std::cout << "Create 2 Example " << x << "!" << std::endl;
	}

private:

};


class Entity
{
public:
	//Entity() {
	//	m_Name = "Unknown";		// 构造函数中初始化变量
	//}

	//Entity() :
	//	m_Name("Unknown"), m_Score(0)	// 这样会重复创建Example对象
	//{
	//	m_Example = Example(8);
	//}


	// 成员初始化列表，注意顺序要和定义变量顺序一致
	// 只创建了一个Example对象，避免重复构造
	Entity() :
		m_Name("Unknown"), m_Score(0),m_Example(Example(8))
	{
		
	}

	// 构造函数重载，带参数的构造函数
	/*Entity(const std::string& name) {
		m_Name = name;
	}*/

	Entity(const std::string& name) :
		m_Name(name), m_Score(0)
	{
	}

	const std::string& GetName() const { return m_Name; }

private:
	std::string m_Name;
	int m_Score;
	Example m_Example;
};



int main()
{
	/*Entity e0("Abc");
	std::cout << e0.GetName() << std::endl;*/

	Entity e1;

    std::cin.get();
}
