// Vector的优化

#include <iostream>
#include <vector>

struct Vertex
{
	float x, y, z;
	Vertex(float x, float y, float z) :x(x), y(y), z(z) {

	}

	Vertex(const Vertex& other) :x(other.x), y(other.y), z(other.z) {
		std::cout << "Copied!" << std::endl;
	}
};

int main() {
	std::vector<Vertex> vertices;
	vertices.reserve(4);	// 优化1：设置指定容量为4,就不用动态扩容了

	//vertices.push_back(Vertex(1, 2, 3));	// 1个拷贝
	//vertices.push_back(Vertex(4, 5, 6));	// 2个拷贝，共1=2=3次拷贝
	//vertices.push_back(Vertex(7, 8, 9));	// 3个拷贝，共1+2+3=6次拷贝
	//vertices.push_back(Vertex(17, 18, 19)); // 4个拷贝，共1+2+3+4=10个拷贝。


	// 优化2：使用emplace_back代替push_back，在实际的vector内存中构造，就没有拷贝了。
	// emplace_back 表示在实际的vector内存中，使用以下参数构造vertex对象
	vertices.emplace_back(1, 2, 3);		// 1个拷贝
	vertices.emplace_back(4, 5, 6);		// 2个拷贝，共1=2=3次拷贝
	vertices.emplace_back(7, 8, 9);	// 3个拷贝，共1+2+3=6次拷贝
	vertices.emplace_back(17, 18, 19); // 4个拷贝，共1+2+3+4=10个拷贝。

	std::cin.get();
}