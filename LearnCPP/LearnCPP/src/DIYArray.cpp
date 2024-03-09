#include <iostream>

namespace DSArray {
	template<typename T, size_t S>

	class Array
	{
	public:
		constexpr size_t Size() const { return S; }
		//Array(int size)
		///*{
		//	m_Data = (int*)_malloca(size * sizeof(int));
		//}*/

		T& operator[](size_t index) {
			if (!(index < S)) {
				__debugbreak();
			}
			return m_Data[index];
		}

		const T& operator[](size_t index) const {
			return m_Data[index];
		}

		T* Data() { return m_Data; }
		const T* Data() const { return m_Data; }

	private:
		T m_Data[S];
	};
}

void DIYArrayDemo() {
	constexpr int size = 5;
	//DSArray::Array data(size);

	DSArray::Array<int, size> data;

	memset(&data[0], 0, data.Size() * sizeof(int));		// Êý×é¸³Öµ

	const auto& arrayReference = data;

	static_assert(data.Size() < 10, "Size is too small!");

	for (size_t i = 0; i < data.Size(); i++)
	{
		//data[i] = 2;
		//std::cout << arrayReference[i] << std::endl;

		std::cout << data[i] << std::endl;
	}
}



