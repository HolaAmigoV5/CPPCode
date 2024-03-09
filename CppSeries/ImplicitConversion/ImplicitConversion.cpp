
#include <iostream>
#include <string>

using String = std::string;

class Entity
{
public:
    Entity(const String& name) :m_Age(-1), m_Name(name) {}

    // explicit放在构造函数前面，表示禁止使用隐式转换，得显式转换
    explicit Entity(int age) :m_Name("Unknown"), m_Age(age) {}
    
private:
    String m_Name;
    int m_Age;
};

void PrintEntity(const Entity& entity) {
    // TO do Print
}

int main()
{
    Entity a = Entity("Cherno");
    Entity b = 22;          // 隐式转换，把int类型通过构造函数转成Entity对象

    //Entity b = 22;          // 使用了explicit在构造函数前后，这里就报错，不能隐式转换了

    PrintEntity(String("Cherno"));  // 隐式(implicit)转换+显式(explicit)转换
    PrintEntity(22);

    std::cin.get();
}

