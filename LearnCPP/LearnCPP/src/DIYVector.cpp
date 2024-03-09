#include <iostream>

namespace DSVector {

	template<typename T>

	class Vector
	{
	public:
		Vector()
		{
			ReAlloc(2);
		}

		void PushBack(const T& value) {
			// check the space
			if (m_Size >= m_Capacity) {
				ReAlloc(m_Capacity + m_Capacity / 2);	//扩容
			}

			// push the value back and update the size;
			m_Data[m_Size++] = value;
		}

		// 优化代码：使用move方式，减少Copy
		void PushBack(T&& value) {
			if (m_Size >= m_Capacity) {
				ReAlloc(m_Capacity + m_Capacity / 2);	//扩容
			}
			m_Data[m_Size++] = std::move(value);
		}


		template<typename... Args>
		T& EmplaceBack(Args&&... args) {
			// check the space
			if (m_Size >= m_Capacity) {
				ReAlloc(m_Capacity + m_Capacity / 2);	//扩容
			}


			//m_Data[m_Size] = T(std::forward<Args>(args)...);
			// Placement new
			new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
			return m_Data[m_Size++];
		}

		void PopBack() {
			if (m_Size > 0) {
				m_Size--;
				m_Data[m_Size].~T();
			}
		}

		~Vector()
		{
			Clear();
			::operator delete(m_Data, m_Capacity * sizeof(T));
		}

		void Clear() {
			for (size_t i = 0; i < m_Size; i++)
			{
				m_Data[i].~T();
			}
			m_Size = 0;
		}

		const T& operator[](size_t index) const {
			if (index >= m_Size) {
				// assert
			}

			return m_Data[index];
		}

		T& operator[](size_t index) {
			return m_Data[index];
		}

		size_t Size() const { return m_Size; }

		

	private:
		void ReAlloc(size_t newCapacity) {
			//1. allocate  a new block of memory;
			//2. copy/move old elements into new block
			//3. delete

			// allocate space for new block
			T* newBlock = (T*)::operator new (newCapacity * sizeof(T));

			// ensure no overflow
			if (newCapacity < m_Size)
				m_Size = newCapacity;
			
			// move all the elements to the new block
			for (size_t i = 0; i < m_Size; i++)
			{
				new(&newBlock[i]) T(std::move(m_Data[i]));
				//newBlock[i] = std::move(m_Data[i]);
			}

			// delete the old space and update old members
			for (size_t i = 0; i < m_Size; i++)
			{
				m_Data[i].~T();
			}

			::operator delete(m_Data, m_Capacity * sizeof(T));
			m_Data = newBlock;
			m_Capacity = newCapacity;
		}

	private:
		T* m_Data = nullptr;
		size_t m_Size = 0;
		size_t m_Capacity = 0;
	};

	template<typename T>
	void PrintVector(const Vector<T>& vector) {
		for (size_t i = 0; i < vector.Size(); i++)
		{
			std::cout << vector[i] << std::endl;
		}

		std::cout << "-----------------------------\n";
	}

	struct Vector3
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;
		int* m_MemoryBlock = nullptr;

		Vector3() { m_MemoryBlock = new int[5]; }
		Vector3(float scalar)
			:x(scalar), y(scalar), z(scalar) {
			m_MemoryBlock = new int[5];
		}

		Vector3(float x, float y, float z)
			:x(x), y(y), z(z) {
			m_MemoryBlock = new int[5];
		}

		Vector3(const Vector3& other) = delete;

		Vector3(Vector3&& other) noexcept :x(other.x), y(other.y), z(other.z) {
			std::cout << "Move0\n";
			m_MemoryBlock = other.m_MemoryBlock;
			other.m_MemoryBlock = nullptr;
		}

		~Vector3()
		{
			std::cout << "Destroy\n";
			delete[] m_MemoryBlock;
		}

		Vector3& operator=(const Vector3& other) = delete;

		Vector3& operator=(Vector3&& other) noexcept{
			m_MemoryBlock = other.m_MemoryBlock;
			other.m_MemoryBlock = nullptr;

			std::cout << "Move\n";
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
	};

	template<>
	void PrintVector(const Vector<Vector3>& vector) {
		for (size_t i = 0; i < vector.Size(); i++)
		{
			std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;
		}

		std::cout << "-----------------------------\n";
	}
}

void DIYVectorDemo() {
	/*DSVector::Vector<std::string> vector;
	vector.PushBack("Cherno");
	vector.PushBack("C++");
	vector.PushBack("Vector");

	DSVector::PrintVector(vector);

	std::cout << "===========================\n";*/

	{
		//DSVector::Vector<DSVector::Vector3> vec3;
		/*vec3.PushBack(DSVector::Vector3(1.0f));
		vec3.PushBack(DSVector::Vector3(2, 3, 4));
		vec3.PushBack(DSVector::Vector3());*/

		/*vec3.EmplaceBack(1.0f);
		vec3.EmplaceBack(2.0f, 3.0f, 4.0f);
		DSVector::PrintVector(vec3);*/
	}

	DSVector::Vector<int> intVector;
	intVector.PushBack(5);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	intVector.EmplaceBack(2);
	DSVector::PrintVector(intVector);
	intVector.PopBack();
	DSVector::PrintVector(intVector);
	intVector.Clear();
}

