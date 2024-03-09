#include <iostream>
#include <chrono>
#include <thread>

// 定义一个计时器类
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration{};

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		
		float ms = duration.count() * 1000.0f;	// 转换成毫秒
		std::cout << "Timer took " << ms << "ms" << std::endl;
	}
};

void TimingFunction() {
	Timer timer;
	for (int i = 0; i < 100; i++)
	{
		std::cout << "Hello\n";
	}
}

void TimingDemo() {
	/*using namespace std::literals::chrono_literals;

	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(1s);
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;
	std::cout << duration.count() << "s" << std::endl;*/

	TimingFunction();
}