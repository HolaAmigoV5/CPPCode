// Vector �����Ƕ�̬���飨ArrayList��

#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

// ��vertices��Ϊ�������ݵ������������в���ʱ����Ҫ�����ã���ֹ������������
void Function(const std::vector<Vertex>& vertices) {

}

void VectorDemo() {
    // vector�����Ƕ�̬���顣����ʹ�ö���Vertex������ʹ��ָ��Vertex*
    std::vector<Vertex> vertices;
    vertices.push_back({ 1,2,3 });
    vertices.push_back({ 4,5,6 });

    Function(vertices);     // ���ô������飬��ֹ������������

    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i] << std::endl;
    }

    std::cout << "=======================================" << std::endl;

    vertices.erase(vertices.begin() + 1);   // �����ڶ���Ԫ��

    // ������foreach����ʽ���
    for (const Vertex& v : vertices)    // ע��ʹ��&�����ٸ���
        std::cout << v << std::endl;


    //vertices.clear();
}