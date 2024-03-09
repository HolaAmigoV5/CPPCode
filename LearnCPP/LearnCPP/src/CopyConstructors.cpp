// ������������������ݺ�ָ�룬���Ǹ�������������
// ǳ������ֻ������ָ�룬��������������
// ���ǰ����÷�ʽ����

#include <iostream>
#pragma warning(disable:4267)

class String
{
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1]; // ʹ��strcpy�Ͳ���+1����Ϊ�Ѿ������˿���ֹ��
		memcpy(m_Buffer, string, m_Size + 1);
	}


	// ��ʽһ��ǳ������C++Ĭ���ṩ�������캯����
	/*String(const String& other)
	   :m_Buffer(other.m_Buffer), m_Size(other.m_Size) {
	}*/

	// ��ʽ����ǳ�������캯��
	/* String(const String& other) {
	   memcpy(this, &other, sizeof(String));
	}*/

	// �����������캯�����Ͳ���������
	//String(const String& other) = delete;

	// ������캯��
	String(const String& other)
		:m_Size(other.m_Size) {
		std::cout << "Copied String!" << std::endl;

		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}


	~String()
	{
		delete[] m_Buffer;
	}

	char& operator[](unsigned int index) {
		return m_Buffer[index];
	}

	// ��Ԫ
	friend std::ostream& operator<<(std::ostream& stream, const String& string);

private:
	char* m_Buffer;		// �����и���ʱ���ڴ�����������ͬ��char*��ֵ
	unsigned int m_Size;
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
	//��ǰ������ΪString�����Ԫ���������String���˽�б���m_Buffer
	stream << string.m_Buffer;
	return stream;
}

// ���·�ʽ���ûᵼ�µ��ü��θ÷������ֶ༸�ο�������string��
void PrintString(String string) {
    std::cout << string << std::endl;
}

// ���ǰ����÷�ʽ���Σ������ظ�����string�����ԣ�����Ҫ��const����ȥ���ݶ���
//void PrintString(const String& string) {
//	std::cout << string << std::endl;
//}

void CopyConstructors() {
	String string = "Cherno";
	String second = string;
	second[2] = 'a';

	//ǳ�����У�������������Ϊ������string����string��second����
	//char* m_buffer���������ã���string������������ʱ��m_bufferָ������ݱ����٣�
	//second�ٵ�����������ʱ��m_bufferָ��������ֱ����٣��ᵼ�³��������
	//������캯���ܽ���������
	//ǳ����ʱ�������charno�����ʱ�����cherno��charno��
	/*std::cout << string << std::endl;
	std::cout << second << std::endl;	*/

	PrintString(string);
	PrintString(second);
}
