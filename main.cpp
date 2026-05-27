#include <iostream>
#include <limits>
#include <string>
#include <windows.h>
#include "experiments.h"
#include "matrix_util.h"
#include "lu.h"
#include "gaussian.h"

//Утилиты ввода/вывода
void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void wait_for_enter() {
    std::cout << "\nНажмите Enter для возврата в меню...";
    clear_input_buffer();
    std::cin.get();
}

void print_header() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "    Лабораторная работа: Сравнение методов решения СЛАУ\n";
    std::cout << "========================================================\n";
}

void print_menu() {
    print_header();
    std::cout << " 1. Эксперимент 4.1: Время решения одной системы\n";
    std::cout << " 2. Эксперимент 4.2: Множественные правые части (n=500)\n";
    std::cout << " 3. Эксперимент 4.3: Точность на матрице Гильберта\n";
    std::cout << " 4. Запустить все эксперименты последовательно\n";
    std::cout << " 0. Выход\n";
    std::cout << "========================================================\n";
    std::cout << " >>> Выбор: ";
}

//ДЕМОНСТРАЦИЯ
void run_matrix_demo()
{
    std::cout << "\n\n========== ДЕМОНСТРАЦИЯ АЛГОРИТМОВ (n=4) ==========\n";
    std::cout << "Генерируем случайную матрицу 4x4 и показываем процесс разложения.\n\n";

    int n = 4;
    Matrix A = matrix_random_generate(n, -5.0, 5.0, 42);
    Vector b = vector_random_generate(n, -5.0, 5.0, 43);

    // 1. Исходная матрица
    print_matrix("Исходная матрица A", A);

    // 2. LU Разложение
    auto lu = lu_decompose(A);
    print_matrix("Матрица L (Нижняя треугольная)", lu.L);
    print_matrix("Матрица U (Верхняя треугольная)", lu.U);

    wait_for_enter();
}

//Главный цикл
void run_interactive_menu() {
    int choice = -1;
    while (true) {
        print_menu();

        if (!(std::cin >> choice)) {
            std::cout << "Введите число от 0 до 5.\n";
            clear_input_buffer();
            continue;
        }

        switch (choice) {
            case 1: run_exp_single_system(); break;
            case 2: run_exp_multiple_rhs(); break;
            case 3: run_exp_hilbert(); break;
            case 4:
                run_exp_single_system();
                run_exp_multiple_rhs();
                run_exp_hilbert();
                break;
            case 0:
                return;
            default:
                std::cout << "Неверный выбор. Доступные пункты: 0–5.\n";
        }

        if (choice != 0) wait_for_enter();
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    run_matrix_demo();

    run_interactive_menu();
    return 0;
}