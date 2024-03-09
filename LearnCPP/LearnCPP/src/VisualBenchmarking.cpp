#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <thread>

#include <cmath>


struct ProfileResult
{
	std::string Name;
	long long Start, End;
	uint32_t ThreadID;
};

struct InstrumentationSession
{
	std::string Name;
};

class Instrumentor
{
public:
	Instrumentor() :m_CurrentSession(nullptr), m_ProfileCount(0)
	{
	}

	void BeginSession(const std::string& name, const std::string& filepath = "results.json") {
		m_OutputStream.open(filepath);
		WriteHeader();
		m_CurrentSession = new InstrumentationSession{ name };
	}

	void EndSession() {
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;
	}

	void WriteProfile(const ProfileResult& result) {
		if (m_ProfileCount++ > 0)
			m_OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.ThreadID << ",";
		m_OutputStream << "\"ts\":" << result.Start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	void WriteHeader() {
		m_OutputStream << "{\"otherData\":{},\"traceEvents\":[";
		m_OutputStream.flush();
	}

	void WriteFooter() {
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	static Instrumentor& Get() {
		static Instrumentor* instance = new Instrumentor();
		return *instance;
	}

	~Instrumentor()
	{
	}

private:
	InstrumentationSession* m_CurrentSession;
	std::ofstream m_OutputStream;
	int m_ProfileCount;
};



class VBenTimer
{
public:
	VBenTimer(const char* name) :m_Name(name), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}


	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

		//std::cout << m_Name << ": " << (end - start) << " ms\n";
		Instrumentor::Get().WriteProfile({ m_Name , start,end,threadID });
		m_Stopped = true;
	}

	~VBenTimer()
	{
		if (!m_Stopped)
			Stop();
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) VBenTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#endif // PROFILING


namespace Benchmark {
	void Function1() {
		//PROFILE_SCOPE("Function1");
		PROFILE_FUNCTION();

		for (int i = 0; i < 10000; i++)
		{
			std::cout << "Hello World #" << i << std::endl;
		}
	}


	void Function2() {
		//PROFILE_SCOPE("Function2");
		PROFILE_FUNCTION();

		for (int i = 0; i < 10000; i++)
		{
			std::cout << "Hello World #" << sqrt(i) << std::endl;
		}
	}

	void RunBenchmarks() {
		//PROFILE_SCOPE("RunBenchmarks");
		PROFILE_FUNCTION();

		std::cout << "Running Benchmarks...\n";
		std::thread a([]() {Function1(); });
		//std::thread b([]() {Function2(); });
		Function2();
		a.join();
		//b.join();

		//Function1();
		//Function2();
	}
}

void VisualBenchmarking() {
	Instrumentor::Get().BeginSession("Profile");
	Benchmark::RunBenchmarks();
	Instrumentor::Get().EndSession();
}

