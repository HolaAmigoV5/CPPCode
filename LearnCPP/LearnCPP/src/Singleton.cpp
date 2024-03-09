#include <iostream>

class Random
{
public:
	Random(const Random&) = delete;

	static Random& Get() {
		static Random instance;
		return instance;
	}

	static float Float() { return Get().IFloat(); }
private:
	float IFloat() const { return m_RandomGenerator; }
	Random() {}
	float m_RandomGenerator = 0.5f;
	
};

//Random Random::s_Instance;


void RandomDemo() {
	Random& instance = Random::Get();
	float number = instance.Float();
	std::cout << number << std::endl;

	//Random::Get().Function();
}