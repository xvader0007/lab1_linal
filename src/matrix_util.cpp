#include "matrix_util.h"
#include <random>
#include <cmath>

Matrix generate_random_matrix(int n, double low, double high, unsigned seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(low, high);

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

Vector generate_random_vector(int n, double low, double high, unsigned seed)
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

Vector multiply(Matrix& A, Vector& x)
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
    Vector r = multiply(A, b);

    for (int i = 0; i < b.size(); i++)
    {
        r[i] -= b[i];
    }

    return l2_norm(r);
}