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
	//	m_Name = "Unknown";		// ���캯���г�ʼ������
	//}*9

	//MemberEntity() :
	//	m_Name("Unknown"), m_Score(0)	// �������ظ�����Example����
	//{
	//	m_Example = Example(8);
	//}


	// ��Ա��ʼ���б�ע��˳��Ҫ�Ͷ������˳��һ��
	// ֻ������һ��Example���󣬱����ظ�����
	MemberEntity() :
		m_Name("Unknown"), m_Score(0), m_Example(Example(8))
	{

	}

	// ���캯�����أ��������Ĺ��캯��
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