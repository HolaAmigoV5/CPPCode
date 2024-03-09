// Vector���Ż�

#include <iostream>
#include <vector>

struct Vertex
{
	float x, y, z;
	Vertex(float x, float y, float z)
		:x(x), y(y), z(z) 
	{

	}

	Vertex(const Vertex& other)
		:x(other.x), y(other.y), z(other.z) 
	{
		std::cout << "Copied!" << std::endl;
	}
};

void OptmizeVectorDemo() {
	std::vector<Vertex> vertices;
	vertices.reserve(4);	// �Ż�1������ָ������Ϊ4,�Ͳ��ö�̬������

	//vertices.push_back(Vertex(1, 2, 3));	// 1������
	//vertices.push_back(Vertex(4, 5, 6));	// 2����������1=2=3�ο���
	//vertices.push_back(Vertex(7, 8, 9));	// 3����������1+2+3=6�ο���
	//vertices.push_back(Vertex(17, 18, 19)); // 4����������1+2+3+4=10��������


	// �Ż�2��ʹ��emplace_back����push_back����ʵ�ʵ�vector�ڴ��й��죬��û�п����ˡ�
	// emplace_back ��ʾ��ʵ�ʵ�vector�ڴ��У�ʹ�����²�������vertex����
	vertices.emplace_back(1.0f, 2.0f, 3.0f);		// 1������
	vertices.emplace_back(4.0f, 5.0f, 6.0f);		// 2����������1=2=3�ο���
	vertices.emplace_back(7.0f, 8.0f, 9.0f);	// 3����������1+2+3=6�ο���
	vertices.emplace_back(17.0f, 18.0f, 19.0f); // 4����������1+2+3+4=10��������
}