#include <iostream>
#include <fstream>
#include <optional>
#include <variant>

std::optional<std::string> ReadFileAsString(const std::string& filepath) {
	std::ifstream stream(filepath);
	if (stream) {
		std::string result;
		stream.close();
		return result;
	}
	return std::string();
}

void OptionalMain() {
	std::optional<std::string> data = ReadFileAsString("data.txt");
	std::string value = data.value_or("Not present");
	std::cout << value << std::endl;

	if (data.has_value())
		std::cout << "File read successfully!\n";
	else
		std::cout << "File could not be opened!\n";
}


// 单一变量存储多个值。variant只是一个类型安全的union，所有数据存储在union里
void VariantDome() {
	std::variant<std::string, int> data;

	data = "Cherno";
	std::cout << std::get<std::string>(data) << "\n";
	if (auto value = std::get_if<std::string>(&data)) {
		std::string& v = *value;
	}
	else {}

	data = 2;
	std::cout << std::get<std::string>(data) << "\n";
	std::cout << std::get<int>(data) << "\n";
}