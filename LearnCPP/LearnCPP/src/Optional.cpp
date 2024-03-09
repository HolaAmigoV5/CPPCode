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


// ��һ�����洢���ֵ��variantֻ��һ�����Ͱ�ȫ��union���������ݴ洢��union��
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