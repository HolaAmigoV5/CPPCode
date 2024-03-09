
#include <iostream>

int main()
{
    const char* ptr = "Hello";
    if (ptr)
        std::cout << "Hello World!\n";
    else if (ptr == "Hello")
    {
        std::cout << "Ptr is Hello!\n";
    }
    else
    {
        std::cout << "Ptr is null!\n";
    }

    std::cin.get();
}

