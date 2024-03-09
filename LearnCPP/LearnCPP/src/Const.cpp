#include <iostream>

void ConstDemo() {
    // const�÷�һ
    const int a = 5;       // ���峣��int
    //a = 2;              //�������a�ǳ����������޸�

    // const�÷���
    const int MAX_AGE = 90;     // ����int
    int* b = new int;
    *b = 2;                     // ������b(dereference)������Ϊ2
    b = (int*)&MAX_AGE;         // ���·�����ָ���ָ��
    std::cout << *b << std::endl;   // 90

    // ����ָ���ָ�볣��
    const int* c = new int;     // ����ָ�룬�����޸ĸ�ָ��ָ������ݣ����Ը�ָ��
    //int const* c = new int;   // ����ָ�룬д����ͬ
    //*c = 3;                   // ������󣬲����޸ĳ���ָ��ָ�������
    c = (int*)&MAX_AGE;         // ����ɹ������޸�ָ�롣
    std::cout << "����ָ�����ֵ��" << *c << std::endl;   // 90

    int* const d = new int;     // ָ�볣���������޸�ָ�򣬿����޸�����
    *d = 3;                     // ����������޸ĳ���ָ��ָ�������
    //d = (int*)&MAX_AGE;       // ����ʧ�ܡ������޸�ָ�롣
    std::cout << "ָ�볣�������" << *d << std::endl;   // 3
}

// const�÷���������ʹ�á�������ֻ�ܵ��ó�����
class ConstEntity
{
public:
    int GetX() const {
        //m_X = 3;         // ������󣬳�����GetX()�������޸�Entity��Ա

        var = 2;           // ����ɹ����ɱ�����var֧���޸�
        return m_X;
    }

    void SetX(int x) const {
        //m_X = x;        // ������󣬳����������޸�    
    }

    // ָ�룬���ݻ������Ա�������޸�
    const int* const GetSpeed() const {
        return m_Speed;
    }

private:
    //int* m_X, m_Y;      // m_X��intָ�룬m_Y��int����
    //int* m_X, *m_Y;       // m_Yǰ���*������ָ��

    int m_X, m_Y;
    int* m_Speed;

    // mutable �������ǳ����������������޸ı���
    mutable int var;        // �ɱ�int����var
};