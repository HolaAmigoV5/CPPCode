#include <iostream>
#include <memory>
#include <chrono>
#include <array>

class BenTimer
{
public:
	BenTimer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~BenTimer()
	{
		Stop();
	}

	void Stop() const {
		auto m_EndTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end= std::chrono::time_point_cast<std::chrono::microseconds>(m_EndTimepoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << duration << "us (" << ms << "ms )\n";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};


void BenchmarkingDemo() {
	/*int value = 0;
	{
		BenTimer timer;
		for (int i = 0; i < 1000000000; i++)
		{
			value += 2;
		}
	}
	std::cout << value << std::endl;*/

	struct Vector2
	{
		float x, y;
	};

	std::cout << "Make Shared\n";
	{
		std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
		BenTimer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
		{
			sharedPtrs[i] = std::make_shared<Vector2>();
		}
	}

	
	std::cout << "New Shared\n";	// 用时最长
	{
		std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
		BenTimer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
		{
			sharedPtrs[i] = std::shared_ptr<Vector2>(new Vector2());
		}
	}

	std::cout << "Make Unique\n";	// 用时最短
	{
		std::array<std::unique_ptr<Vector2>, 1000> uniquePtrs;
		BenTimer timer;
		for (int i = 0; i < uniquePtrs.size(); i++)
		{
			uniquePtrs[i] = std::make_unique<Vector2>();
		}
	}
}