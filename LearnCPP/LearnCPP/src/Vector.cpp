// Vector 本质是动态数组（ArrayList）

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

// 将vertices作为参数传递到其他方法进行操作时，需要传引用，防止复制整个数组
void Function(const std::vector<Vertex>& vertices) {

}

void VectorDemo() {
    // vector本质是动态数组。尽量使用对象Vertex，而不使用指针Vertex*
    std::vector<Vertex> vertices;
    vertices.push_back({ 1,2,3 });
    vertices.push_back({ 4,5,6 });

    Function(vertices);     // 引用传递数组，防止复制整个数组

    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i] << std::endl;
    }

    std::cout << "=======================================" << std::endl;

    vertices.erase(vertices.begin() + 1);   // 擦除第二个元素

    // 类似于foreach的形式输出
    for (const Vertex& v : vertices)    // 注意使用&，减少复制
        std::cout << v << std::endl;


    //vertices.clear();
}