#include <iostream>
#include <string>

class Example
{
public:
	Example() {
		std::cout << "Create 1 Example" << std::endl;
	}

	Example(int x) {
		std::cout << "Create 2 Example " << x << "!" << std::endl;
	}
};

class MemberEntity
{
private:
	std::string m_Name;
	int m_Score;
	Example m_Example;

public:
	//MemberEntity() {
	//	m_Name = "Unknown";		// 构造函数中初始化变量
	//}*9

	//MemberEntity() :
	//	m_Name("Unknown"), m_Score(0)	// 这样会重复创建Example对象
	//{
	//	m_Example = Example(8);
	//}


	// 成员初始化列表，注意顺序要和定义变量顺序一致
	// 只创建了一个Example对象，避免重复构造
	MemberEntity() :
		m_Name("Unknown"), m_Score(0), m_Example(Example(8))
	{

	}

	// 构造函数重载，带参数的构造函数
	/*MemberEntity(const std::string& name) {
		m_Name = name;
	}*/

	MemberEntity(const std::string& name) :
		m_Name(name), m_Score(0)
	{
	}

	const std::string& GetName() const { return m_Name; }
};

void MemberListsDemo() {
	/*MemberEntity e0("Abc");
	std::cout << e0.GetName() << std::endl;*/

	MemberEntity e1;
}