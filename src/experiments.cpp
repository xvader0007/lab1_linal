#include "experiments.h"
#include "matrix_util.h"
#include "gaussian.h"
#include "lu.h"
#include "timer.h"
#include <iostream>
#include <iomanip>
#include <vector>

void run_exp_single_system()
{
    std::cout << "\n===========Сравнение по времени===========\n";
    std::cout << std::left << std::setw(6) << "N"
              << std::setw(12) << "Gauss_no" << std::setw(12) << "Gauss_part"
              << std::setw(12) << "LU_total" << std::setw(12) << "LU_secomp"
              << std::setw(12) << "LU_solve\n";

    std::vector<int> sizes = {100, 200, 500, 1000};
    unsigned seed = 42;
    Timer t;

    for (int n : sizes)
    {
        auto A = matrix_random_generate(n, -1.0, 1.0, seed);
        auto b = vector_random_generate(n, -1.0, 1.0, seed + 1);

        t.start();
        gauss_no_pivot(A, b);
        double t1 = t.elapsed_ms();

        t.start();
        gauss_partial_pivot(A, b);
        double t2 = t.elapsed_ms();

        t.start();
        auto lu = lu_decompose(A);
        double t_decomp = t.elapsed_ms();

        t.start();
        solve_lu(lu,b);
        double t_solve = t.elapsed_ms();
        double t3 = t_decomp + t_solve;

        std::cout << std::left << std::setw(6) << n
              << std::fixed << std::setprecision(2)
              << std::setw(12) << t1 << std::setw(12) << t2
              << std::setw(12) << t3 << std::setw(12) << t_decomp
              << std::setw(12) << t_solve << "\n";
    }
}

void run_exp_multiple_rhs()
{
    std::cout << "\n===========Множественные правые части (n=500)===========\n";

    int n = 500;
    std::vector<int> k_values = {1, 10, 100};

    unsigned seed = 42;
    auto A = matrix_random_generate(n, -1.0, 1.0, seed);
    auto lu = lu_decompose(A);
    Timer t;

    std::cout << std::left << std::setw(6) << "K"
    << std::setw(16) << "Gauss_partial" << std::setw(16)
    << "LU_solve\n";

    for (int k : k_values)
    {
        t.start();
        for (int i = 0; i < k; i++)
        {
            auto b = vector_random_generate(n, -1.0, 1.0, seed + i);
            gauss_partial_pivot(A, b);
        }
        double t_gauss = t.elapsed_ms();

        t.start();
        for (int i = 0; i < k; i++)
        {
            auto b = vector_random_generate(n, -1.0, 1.0, seed + i);
            solve_lu(lu, b);
        }
        double t_lu = t.elapsed_ms();

        std::cout << std::left << std::setw(6) << k
        << std::fixed << std::setprecision(2)
        << std::setw(16) << t_gauss << std::setw(16)
        << t_lu << std::endl;
    }
}

void run_exp_hilbert()
{
    std::cout << "\n===========Множественные правые части (n=500)===========\n";
    std::cout << std::left << std::setw(5) << "N"
    << std::setw(22) << "Method" << std::setw(18)
    << "Rel_Error" << std::setw(18) << "Residual\n";

    std::vector<int> sizes = {5, 10, 15};
    for (int n : sizes)
    {
        Vector x_exact(n, 1.0);
        Matrix H = hilbert_matrix_generate(n);
        Vector b = multiply(H, x_exact);

        auto run_test = [&](const std::string& name, Vector x_approx)
        {
            Vector diff(n);
            for (int i = 0; i < n; i++)
            {
                diff[i] = x_approx[i] - x_exact[i];
            }
            double rel_err = l2_norm(diff) / l2_norm(x_exact);
            double res = compute_residual(H, x_approx, b);
            std::cout << std::left << std::setw(5) << n
            << std::setw(22) << name
            << std::scientific << std::setprecision(4)
            << std::setw(18) << rel_err << std::setw(18)
            << res << std::endl;
        };

        try{run_test("Gauss_no_pivot", gauss_no_pivot(H, b));}
        catch (...) {std::cout << std::setw(27) << n << "Gauss_no_pivot" << "FAILED\n";}

        try{run_test("gauss_partial_pivot", gauss_partial_pivot(H, b));}
        catch (...) {std::cout << std::setw(27) << n << "Gauss_partial" << "FAILED\n";}

        try
        {
            auto lu = lu_decompose(H);
            run_test("LU_decompose", solve_lu(lu,b));
        }
        catch (...) {std::cout << std::setw(27) << n << "LU_decompose" << "FAILED\n";}
    }
}