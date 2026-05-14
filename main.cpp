#include "experiments.h"
#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== Лабораторная работа ===\n";
    try
    {
        run_exp_multiple_rhs();
        run_exp_multiple_rhs();
        run_exp_hilbert();
        std::cout << "Эксперементы завершены.\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка выполнения: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}