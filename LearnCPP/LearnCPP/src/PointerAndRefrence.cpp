#include <iostream>

// ��ֵ���ݣ����ݵ��Ǹ��Ƶ�ֵ��
void IncrementByValue(int value) {
    value++;
}

// ��ָ�봫ֵ�����ݵ��ǵ�ַ��
void IncrementByRefrence(int* value) {
    (*value)++;       // ʹ��*�������õ�ַ��Ӧ��ֵ��Ȼ��������ע�⣺++�ǲ�������ִ�����ȼ��ߣ�������Ҫ�����š�
}

// �����ô�ֵ
void Increment3(int& value) {
    value++;
}

void PointerAndRefrence() {
    std::cout << "================ָ��===================" << std::endl;
    // ����ptrָ���ָ��
    void* ptr = nullptr;    // Ҳ����void* ptr=0;

    int var = 8;
    int* varPtr = &var;     // &var����ȡ����var���ڴ��ַ����ֵ������varPtr
    *varPtr = 10;           // ��ָ��varPtrλ�õ�ֵ�޸�Ϊ10
    std::cout << var << std::endl;

    char* buffer = new char[8];     //����8���ֽڿռ䲢������ʼ�ڴ��ַ
    memset(buffer, 0, 8);       //ʹ��0��bufferλ�ÿ�ʼ���8���ֽڵ��ڴ�

    char** ptr1 = &buffer;  //��buffer���ڴ��ַ��ֵ��ָ��ptr1��** ��ʾָ���ָ�룬˫ָ��
    delete[] buffer;        // ʹ��delete�ͷ��ڴ�buffer��Ҳ������buffer = nullptr;���ͷ��ڴ�


    std::cout << "===============����====================" << std::endl;
    int a = 5;
    //��ֵ����
    IncrementByValue(a);
    std::cout << a << std::endl;        //Increment������ֵ���ݣ����ú�ԭ����a��Ȼ��5
    std::cout << "-------------------------------" << std::endl;

    // �����ô�ֵ(��ָ��)
    IncrementByRefrence(&a);
    std::cout << a << std::endl;    // ����Increment2���������а����ô�ֵ�������a=6

    // �����ô�ֵ
    Increment3(a);
    std::cout << a << std::endl;    // ����Increment3���������а����ô�ֵ�������a=7

    std::cout << "-------------------------------" << std::endl;
    int& ref = a;       // ��a�����ø�ֵ��ref��
    ref = 2;
    std::cout << a << std::endl;
}


