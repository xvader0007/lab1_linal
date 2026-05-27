#include "matrix_util.h"
#include <random>
#include <cmath>
#include <iostream>
#include <iomanip>

Matrix matrix_random_generate(int n, double low, double high, unsigned seed)
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(low, high);

    Matrix A(n, Vector(n));
    for (auto& row : A)
    {
        for (auto& val : row) val = dist(gen);
    }

    for (int i = 0; i < n; i++)
    {
        double row_sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (i != j) row_sum += std::abs(A[i][j]);
        }
        A[i][i] += row_sum + 1.0;
    }

    return A;
}

Vector vector_random_generate(int n, double low, double high, unsigned seed)
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(low, high);

    Vector b(n);

    for (auto& val : b) val = dist(gen);

    return b;
}

Matrix hilbert_matrix_generate(int n)
{
    Matrix H(n, Vector(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            H[i][j] = 1.0 / (i + j + 1);
        }
    }

    return H;
}

Vector multiply(const Matrix& A, const Vector& x)
{
    int n = A.size();
    Vector res(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i] += A[i][j] * x[j];
        }
    }

    return res;
}

double l2_norm(const Vector& x)
{
    double sum = 0.0;

    for (double val : x) sum += val * val;

    return std::sqrt(sum);
}

double compute_residual(const Matrix& A, const Vector& b, const Vector& x)
{
    Vector r = multiply(A, x);

    for (int i = 0; i < b.size(); i++)
    {
        r[i] -= b[i];
    }

    return l2_norm(r);
}

void print_matrix(const std::string& title, const Matrix& m)
{
    std::cout << "\n" << title << "\n";
    std::cout << std::fixed << std::setprecision(4);

    for (const auto& row : m)
    {
        for (double val : row)
        {
            // setw(12) выравнивает столбцы
            std::cout << std::setw(12) << val;
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------------------------------\n";
}