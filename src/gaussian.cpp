#include "gaussian.h"
#include <cmath>
#include <stdexcept>
#include <utility>

Vector gauss_no_pivot(Matrix A, Vector b)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double m = A[j][i] / A[i][i];
            b[j] -= m * b[i];

            for (int k = i; k < n; k++)
            {
                A[j][k] -= m * A[i][k];
            }
        }
    }
    Vector x(n);
    for (int i = n - 1; i>= 0; i--)
    {
        double sum = b[i];
        for (int j = i + 1; j < n; j++)
        {
            sum -= A[i][j] * x[j];
        }

        x[i] = sum / A[i][i];
    }
    return x;
}

Vector gauss_partial_pivot(Matrix A, Vector b)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        int max_row = 0;
        double max_val = std::abs(A[i][i]);
        for (int k = i + 1; k < n; k++)
        {
            double val = std::abs(A[k][i]);
            if (val > max_val) {max_val = val; max_row = k;}
        }
        if (max_val < eps) throw std::runtime_error("Zero pivot (partial pivot)");

        if (max_row != i)
        {
            std::swap(A[i],A[max_row]);
            std::swap(b[i], b[max_row]);
        }

        for (int j = i + 1; j < n; j++)
        {
            double m = A[j][i] / A[i][i];
            b[j] -= m * b[i];
            for (int h = i; h < n; h++) A[j][h] -= m * A[i][h];
        }
    }
    Vector x(n);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = b[i];
        for (int j = i + 1; j < n; j++) sum -= A[i][j] * x[j];
        x[i] = sum / A[i][i];
    }

    return x;
}