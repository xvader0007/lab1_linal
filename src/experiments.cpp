#include "experiments.h"
#include "matrix_util.h"
#include "gaussian.h"
#include "lu.h"
#include "timer.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <sstream>

// Вспомогательная функция для безопасного вывода чисел (заменяет inf/nan на строку)
std::string fmt_val(double v) {
    if (!std::isfinite(v)) return "FAILED/INF";
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(4) << v;
    return oss.str();
}

void run_exp_single_system()
{
    std::cout << "\n=== 4.1 Сравнение времени решения одной системы ===\n";
    std::cout << std::left
              << std::setw(6) << "N"
              << std::setw(16) << "Gauss (no pivot)"
              << std::setw(16) << "Gauss (partial)"
              << std::setw(16) << "LU (total)"
              << std::setw(16) << "LU (decomp)"
              << std::setw(16) << "LU (solve)" << "\n";
    std::cout << std::string(86, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    std::vector<int> sizes = {100, 200, 500, 1000};
    unsigned seed = 42;
    Timer t;

    for (int n : sizes)
    {
        auto A = matrix_random_generate(n, -1.0, 1.0, seed);
        auto b = vector_random_generate(n, -1.0, 1.0, seed + 1);

        t.start(); gauss_no_pivot(A, b); double t1 = t.elapsed_ms();
        t.start(); gauss_partial_pivot(A, b); double t2 = t.elapsed_ms();

        t.start(); auto lu = lu_decompose(A); double t_decomp = t.elapsed_ms();
        t.start(); solve_lu(lu, b); double t_solve = t.elapsed_ms();
        double t3 = t_decomp + t_solve;

        std::cout << std::left << std::setw(6) << n
                  << std::setw(16) << t1
                  << std::setw(16) << t2
                  << std::setw(16) << t3
                  << std::setw(16) << t_decomp
                  << std::setw(16) << t_solve << "\n";
    }
}

void run_exp_multiple_rhs()
{
    std::cout << "\n=== 4.2 Экономия времени при множественных правых частях ===\n";
    std::cout << std::left
              << std::setw(6) << "K"
              << std::setw(18) << "Gauss (partial)"
              << std::setw(18) << "LU (solve only)" << "\n";
    std::cout << std::string(42, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);

    int n = 500;
    std::vector<int> k_values = {1, 10, 100};
    unsigned seed = 42;
    auto A = matrix_random_generate(n, -1.0, 1.0, seed);
    auto lu = lu_decompose(A);
    Timer t;

    for (int k : k_values)
    {
        t.start();
        for (int i = 0; i < k; ++i) {
            auto b = vector_random_generate(n, -1.0, 1.0, seed + i);
            gauss_partial_pivot(A, b);
        }
        double t_gauss = t.elapsed_ms();

        t.start();
        for (int i = 0; i < k; ++i) {
            auto b = vector_random_generate(n, -1.0, 1.0, seed + i);
            solve_lu(lu, b);
        }
        double t_lu = t.elapsed_ms();

        std::cout << std::left << std::setw(6) << k
                  << std::setw(18) << t_gauss
                  << std::setw(18) << t_lu << "\n";
    }
}

void run_exp_hilbert()
{
    std::cout << "\n=== 4.3 Проверка точности на матрице Гильберта ===\n";
    std::cout << std::left
              << std::setw(5) << "N"
              << std::setw(20) << "Method"
              << std::setw(18) << "Rel_Error"
              << std::setw(18) << "Residual" << "\n";
    std::cout << std::string(61, '-') << "\n";

    std::vector<int> sizes = {5, 10, 15};
    for (int n : sizes)
    {
        Vector x_exact(n, 1.0);
        Matrix H = hilbert_matrix_generate(n);
        Vector b = multiply(H, x_exact);

        auto run_test = [&](const std::string& name, Vector x_approx)
        {
            Vector diff(n);
            for (int i = 0; i < n; ++i) diff[i] = x_approx[i] - x_exact[i];
            double rel_err = l2_norm(diff) / l2_norm(x_exact);
            double res = compute_residual(H, b, x_approx);

            std::cout << std::left << std::setw(5) << n
                      << std::setw(20) << name
                      << std::setw(18) << fmt_val(rel_err)
                      << std::setw(18) << fmt_val(res) << "\n";
        };

        try { run_test("Gauss (no pivot)", gauss_no_pivot(H, b)); }
        catch (...) {
            std::cout << std::left << std::setw(5) << n
                      << std::setw(20) << "Gauss (no pivot)"
                      << std::setw(18) << "FAILED"
                      << std::setw(18) << "FAILED" << "\n";
        }

        try { run_test("Gauss (partial)", gauss_partial_pivot(H, b)); }
        catch (...) {
            std::cout << std::left << std::setw(5) << n
                      << std::setw(20) << "Gauss (partial)"
                      << std::setw(18) << "FAILED"
                      << std::setw(18) << "FAILED" << "\n";
        }

        try {
            auto lu = lu_decompose(H);
            run_test("LU (decompose)", solve_lu(lu, b));
        } catch (...) {
            std::cout << std::left << std::setw(5) << n
                      << std::setw(20) << "LU (decompose)"
                      << std::setw(18) << "FAILED"
                      << std::setw(18) << "FAILED" << "\n";
        }
    }
}