#include <iostream>
#include <experiments.h>

int main()
{
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