#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> CreatePerson() {
	return { "Cherno", 24 };
}

void StructuredBindingDemo() {
	/*auto person = CreatePerson();
	std::string& name = std::get<0>(person);
	int age = std::get<1>(person);*/

	// C++17���ṩ�Ľṹ����
	auto [name, age] = CreatePerson();
	std::cout << "name: " << name << " , age: " << age << std::endl;
}