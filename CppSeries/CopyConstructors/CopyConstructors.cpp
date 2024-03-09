// 深拷贝：拷贝了数据内容和指针，就是复制了整个对象
// 浅拷贝：只拷贝了指针，不拷贝数据内容

#include <iostream>

class String
{
public:
    String(const char* string) {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];    // 使用strcpy就不用+1，因为已经包含了空终止符
        memcpy(m_Buffer, string, m_Size + 1);
    }

    // C++默认提供拷贝构造函数。浅拷贝
    /*String(const String& other)
        :m_Buffer(other.m_Buffer), m_Size(other.m_Size) {
    }*/

    // 方式二：浅拷贝构造函数
   /* String(const String& other) {
        memcpy(this, &other, sizeof(String));
    }*/

    // 不允许拷贝构造函数，就不允许复制了
    //String(const String& other) = delete;

    // 深拷贝构造函数
    String(const String& other) :m_Size(other.m_Size) {
        std::cout << "Copied String!" << std::endl;

        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    ~String() {
        delete[] m_Buffer;
    }

    char& operator[](unsigned int index) {
        return m_Buffer[index];
    }

    // 友元
    friend std::ostream& operator<<(std::ostream& stream, const String& string);

private:
    char* m_Buffer;
    unsigned int m_Size;
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream << string.m_Buffer;  //当前函数作为String类的友元，允许访问String里的私有变量m_Buffer
    return stream;
}

// 以下方式调用会导致调用几次该方法，又多几次拷贝对象string。
//void PrintString(String string) {
//    std::cout << string << std::endl;
//}

// 按引用方式传参，避免重复创建string。所以：总是要用const引用去传递对象
void PrintString(const String& string) {
    std::cout << string << std::endl;
}

int main()
{
    int a = 2;
    int b = a;      // 内存地址拷贝a，赋值给b


    String string = "Cherno";
    //std::cout << string << std::endl;
    PrintString(string);

    String second = string;
    second[2] = 'a';
    //std::cout << second << std::endl;  //浅拷贝中，程序会崩溃，因为m_Buffer被free两次了
    PrintString(second);

    std::cin.get();
}

