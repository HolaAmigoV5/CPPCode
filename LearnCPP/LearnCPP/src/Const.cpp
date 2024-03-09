#include <iostream>

void ConstDemo() {
    // const用法一
    const int a = 5;       // 定义常量int
    //a = 2;              //编译错误，a是常量，不能修改

    // const用法二
    const int MAX_AGE = 90;     // 常量int
    int* b = new int;
    *b = 2;                     // 逆引用b(dereference)，设置为2
    b = (int*)&MAX_AGE;         // 重新分配了指针的指向
    std::cout << *b << std::endl;   // 90

    // 常量指针和指针常量
    const int* c = new int;     // 常量指针，不能修改该指针指向的内容，可以改指向
    //int const* c = new int;   // 常量指针，写法不同
    //*c = 3;                   // 编译错误，不能修改常量指针指向的内容
    c = (int*)&MAX_AGE;         // 编译成功。能修改指针。
    std::cout << "常量指针输出值：" << *c << std::endl;   // 90

    int* const d = new int;     // 指针常量，不能修改指向，可以修改内容
    *d = 3;                     // 编译错误，能修改常量指针指向的内容
    //d = (int*)&MAX_AGE;       // 编译失败。不能修改指针。
    std::cout << "指针常量输出：" << *d << std::endl;   // 3
}

// const用法三：类中使用。常对象只能调用常函数
class ConstEntity
{
public:
    int GetX() const {
        //m_X = 3;         // 编译错误，常函数GetX()方法不修改Entity成员

        var = 2;           // 编译成功，可变整型var支持修改
        return m_X;
    }

    void SetX(int x) const {
        //m_X = x;        // 编译错误，常量对象不能修改    
    }

    // 指针，内容还有类成员都不能修改
    const int* const GetSpeed() const {
        return m_Speed;
    }

private:
    //int* m_X, m_Y;      // m_X是int指针，m_Y是int整型
    //int* m_X, *m_Y;       // m_Y前面加*，定义指针

    int m_X, m_Y;
    int* m_Speed;

    // mutable 允许函数是常量方法，但可以修改变量
    mutable int var;        // 可变int整型var
};