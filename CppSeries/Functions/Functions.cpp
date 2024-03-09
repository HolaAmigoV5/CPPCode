#include <iostream>

int Multiply(int a, int b) {
    return a * b;
}

void MultiplyAndLog(int a, int b) {
    std::cout << Multiply(a, b) << std::endl;
}

int main()
{
    /*std::cout << "Hello World!\n";*/
   /* std::cout << Multiply(3, 5) << std::endl;

    std::cout << Multiply(4, 6);*/

    MultiplyAndLog(7, 8);
    MultiplyAndLog(2, 8);
    MultiplyAndLog(3, 8);


    std::cin.get();
}
