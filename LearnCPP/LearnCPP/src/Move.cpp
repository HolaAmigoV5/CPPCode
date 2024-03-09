#include <iostream>

namespace MoveSemantics {
	class String
	{
	public:
		String() = default;
		String(const char* string)
		{
			printf("Created!\n");
			m_Size = strlen(string);
			m_Data = new char[m_Size];
			memcpy(m_Data, string, m_Size);
		}

		// 拷贝构造函数
		String(const String& other)
		{
			printf("Copied!\n");
			m_Size = other.m_Size;
			m_Data = new char[m_Size];
			memcpy(m_Data, other.m_Data, m_Size);
		}

		// 移动构造函数。右值引用。进行浅拷贝数据，不进行数据赋值
		String(String&& other) noexcept{
			printf("Moved!\n");
			m_Size = other.m_Size;
			m_Data = other.m_Data;

			other.m_Size = 0;
			other.m_Data = nullptr;
		}

		// 移动赋值运算符
		String& operator=(String&& other) noexcept {
			printf("Moved!\n");

			if (this != &other) {
				delete[] m_Data;
				m_Size = other.m_Size;
				m_Data = other.m_Data;

				other.m_Size = 0;
				other.m_Data = nullptr;
			}
			return *this;
			
		}

		~String()
		{
			printf("Destroyed!\n");
			delete m_Data;
		}

		void Print() {
			for (uint32_t i = 0; i < m_Size; i++)
				printf("%c", m_Data[i]);

			printf("\n");
		}

	private:
		char* m_Data;
		uint32_t m_Size;
	};

	class MoEntity
	{
	public:
		MoEntity(const String& name) :m_Name(name) {}

		// 右值引用的构造函数。需要显示转换参数name
		//MoEntity(String&& name) :m_Name((String&&)name) {}

		// 与上面等效。通常如下方式写代码
		MoEntity(String&& name) :m_Name(std::move(name)) {}

		void PrintName() {
			m_Name.Print();
		}

	private:
		String m_Name;
	};
}

void MoveDemo() {
	//MoveSemantics::MoEntity entity("Cherno");
	//entity.PrintName();

	//MoveSemantics::String string = "Hello";
	////MoveSemantics::String dest((MoveSemantics::String&&)string);
	////MoveSemantics::String dest(std::move(string)); // 和上面一样，移动构造函数

	MoveSemantics::String apple = "Apple";
	MoveSemantics::String dest;

	apple.Print();
	dest.Print();

	dest = std::move(apple);	// 赋值运算符

	apple.Print();
	dest.Print();
}


