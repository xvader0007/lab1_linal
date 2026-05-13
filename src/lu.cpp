#include "lu.h"
#include <cmath>
#include <stdexcept>

LUResult lu_decompose(const Matrix &A)
{
    int n = A.size();
    Matrix L(n, Vector(n, 0.0));
    Matrix U(n, Vector(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double sum = 0.0;
            for (int m = 0; m < i; m++)
            {
                sum += L[i][m] * U[m][j];
            }

            U[i][j] = A[i][j] - sum;
        }

        for (int k = i + 1; k < n; k++)
        {
            double sum = 0.0;
            for (int m = 0; m < k; m++)
            {
                sum += L[k][m] * U[m][i];
            }
            L[i][i] = 1.0;
        }

        return {L, U};
    }
}

Vector forward_substitution(const Matrix& L, const Vector& b)
{
    int n = L.size();
    Vector y(n);

    for (int i = 0; i < n; i++)
    {
        double sum = b[i];
        for (int j = 0; j < i; j++)
        {
            sum -= L[i][j] * y[j];
        }
        y[i] = sum / L[i][i];
    }

    return y;
}

Vector back_substitution(const Matrix& U, const Vector& y)
{
    int n = U.size();
    Vector x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = y[i];
        for (int j = i + 1; j < n; j++)
        {
            sum -= U[i][j] * x[j];
        }

        if (std::abs(U[i][i]) < eps) throw std::runtime_error("Zero diagonal in U");
        x[i] = sum / U[i][i];
    }

    return x;
}

Vector solve_lu(const LUResult &lu, const Vector &b)
{
    return back_substitution(lu.U, forward_substitution(lu.L, b));
}
