#include <iostream>

// 按值传递（传递的是复制的值）
void IncrementByValue(int value) {
    value++;
}

// 按指针传值（传递的是地址）
void IncrementByRefrence(int* value) {
    (*value)++;       // 使用*解析引用地址对应的值，然后自增。注意：++是操作符，执行优先级高，所以需要加括号。
}

// 按引用传值
void Increment3(int& value) {
    value++;
}

void PointerAndRefrence() {
    std::cout << "================指针===================" << std::endl;
    // 定义ptr指向空指针
    void* ptr = nullptr;    // 也可以void* ptr=0;

    int var = 8;
    int* varPtr = &var;     // &var：获取变量var的内存地址，赋值给变量varPtr
    *varPtr = 10;           // 将指针varPtr位置的值修改为10
    std::cout << var << std::endl;

    char* buffer = new char[8];     //分配8个字节空间并返回起始内存地址
    memset(buffer, 0, 8);       //使用0从buffer位置开始填充8个字节的内存

    char** ptr1 = &buffer;  //将buffer的内存地址赋值给指针ptr1。** 表示指针的指针，双指针
    delete[] buffer;        // 使用delete释放内存buffer。也可以用buffer = nullptr;来释放内存


    std::cout << "===============引用====================" << std::endl;
    int a = 5;
    //按值传递
    IncrementByValue(a);
    std::cout << a << std::endl;        //Increment方法按值传递，调用后，原来的a依然是5
    std::cout << "-------------------------------" << std::endl;

    // 按引用传值(传指针)
    IncrementByRefrence(&a);
    std::cout << a << std::endl;    // 调用Increment2方法，进行按引用传值，则最后a=6

    // 按引用传值
    Increment3(a);
    std::cout << a << std::endl;    // 调用Increment3方法，进行按引用传值，则最后a=7

    std::cout << "-------------------------------" << std::endl;
    int& ref = a;       // 把a的引用赋值给ref。
    ref = 2;
    std::cout << a << std::endl;
}


