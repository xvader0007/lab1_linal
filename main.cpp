#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    while(1)
    {
        std::cout << "Ваня, привет!" << std::endl;
    }

    //return 0;
}