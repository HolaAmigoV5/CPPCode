#include <iostream>
#include <string>

void StringsDemo() {
    // �ַ������巽ʽһ
    const char* name = "Cherno";
    std::cout << name << std::endl; // �ַ������ڴ����ʱ��������Կ��ַ�(\0)��β���ʶ�ȡ��\0����ֹ
    std::cout << "�ַ������ȣ�" << strlen(name) << std::endl;

    //name[2] = 'a';

    // �ַ����ı��ʣ�char������
    char name2[7] = { 'C','h','e','r','n','o',0 };
    std::cout << name2 << std::endl;    //name2 ��Ϊ�ĺ�����˸�0���Ϳ�����ȷ��ʾ������


    // �ַ��������
    std::string name3 = "wby";
    //std::string name3 = "wby" + " Hello!";  // ��������д����+�������������ָ��
    //std::string name3 = std::string("wby") + " Hello!";  // �������ԣ�string��������+��+=������
    name3 += " Hello!";      // Ҳ����������name3��string���ͣ������á�+=��

    std::cout << name3 << std::endl;
    std::cout << "name3�ַ������ȣ�" << name3.size() << std::endl;


    bool constains = name3.find("wb") != std::string::npos;     // �ж�name3�ַ������Ƿ����"wb"


    // �ַ�������������˫����֮���һ���ַ����洢���ڴ��ֻ�����֣���˲����޸�
    // "Cherno";    // �ַ���������
    const char name4[8] = "Che\0rno";
    std::cout << strlen(name4) << std::endl; // �����3����Ϊ����\0����Ϊ�����ˣ���˾���3

    // const char* myName = "wby";
    // myName[1] = 'c';    // myName�ǳ���ָ�룬���ܸ�ֵ�޸�
    
    // ��������ʵ�����¿�����һ���ռ�洢�ַ�������ָ�������"wby"�������޸�
    char myName[4] = "wby";  // ���Ͷ�������飬������ָ��Ϳ����޸��ַ�����
    myName[1] = 'c';
    std::cout << myName << std::endl;   // �����wcy

    const wchar_t* name5 = L"Cherno"; // ���ַ���һ���ַ�ͨ��2���ֽڣ�����1��4����ȡ���ڲ���ϵͳ��
    const char16_t* name6 = u"Cherno";
    const char32_t* name7 = U"Cherno";

    // �ַ�������
    using namespace std::string_literals;
    std::string name00 = "wby"s + " Hello";     // c++ 14�У��ַ������
    std::wstring name0 = L"Cherno"s + L" hello";        //���ԣ����ַ�������������
    std::u32string name01 = U"Cherno"s + U" hello";        //���ԣ��ַ�������������

    // �ַ���������ʾ
    const char* exam = R"(Line1 
            Line2
            Line3)";

    const char* ex = "Line1"
        "Line2"
        "Line3";
}