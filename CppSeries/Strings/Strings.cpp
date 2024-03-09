
#include <iostream>
#include <string>


// 字符串传值时，使用常量(const)引用(&)的方式，否则只是传了一份拷贝
void PrintString(const std::string& string) {
    std::cout << string << std::endl;
}

int main()
{
    // 字符串定义方式一
    const char* name = "Cherno";      
    std::cout << name << std::endl; // 字符串在内存分配时，最后是以空字符(\0)结尾，故读取到\0后终止
    std::cout << "字符串长度：" << strlen(name) << std::endl;

    //name[2] = 'a';

    // 字符串的本质：char的数组
    char name2[7] = { 'C','h','e','r','n','o',0 };
    std::cout << name2 << std::endl;    //name2 人为的后面加了个0，就可以正确显示出来了


    // 字符串定义二
    std::string name3 = "wby";
    //std::string name3 = "wby" + " Hello!";  // 不能这样写，“+”不能添加两个指针
    //std::string name3 = std::string("wby") + " Hello!";  // 这样可以，string中重载了+和+=操作符
    name3 += " Hello!";      // 也可以这样，name3是string类型，可以用“+=”

    std::cout << name3 << std::endl;
    std::cout << "name3字符串长度：" << name3.size() << std::endl;


    bool constains = name3.find("wb") != std::string::npos;     // 判断name3字符串中是否包含"wb"


    const char name4[8] = "Che\0rno";      // 字符串面量，存储在内存的只读部分，因此不能修改
    std::cout << strlen(name4) << std::endl; // 结果是3，因为遇到\0就认为结束了，因此就是3

    const wchar_t* name5 = L"Cherno";     // 宽字符。一个字符通常2个字节（可能1个或4个，取决于操作系统）
    const char16_t* name6 = u"Cherno";
    const char32_t* name7 = U"Cherno";

    using namespace std::string_literals;
    std::wstring name0 = L"Cherno"s + L" hello";        //可以，宽字符串字面量附加
    std::u32string name01 = U"Cherno"s + U" hello";        //可以，字符串字面量附加

    // 字符串多行显示
    const char* exam = R"(Line1 
            Line2
            Line3)";

    const char* ex = "Line1"
        "Line2"
        "Line3";

    std::cin.get();
}

