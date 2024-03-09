#include <iostream>
#include <unordered_map>

void IteratorDemo() {
	using ScoreMap = std::unordered_map<std::string, int>;
	ScoreMap map;
	map["Cherno"] = 5;
	map["C++"] = 2;

	for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++)
	{
		auto& key = it->first;
		auto& value = (*it).second;

		std::cout << key << " = " << value << std::endl;
	}

	std::cout << std::endl;

	for (auto kv : map) {
		auto& key = kv.first;
		auto& value = kv.second;

		std::cout << key << " = " << value << std::endl;
	}

	std::cout << std::endl;
	// C++17 ÖÐ¶¨Òå
	for (auto [key, value] : map) {
		std::cout << key << " = " << value << std::endl;
	}
}