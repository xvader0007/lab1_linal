#include "gaussian.h"
#include <cmath>

Vector gauss_no_pivot(Matrix A, Vector b)
{
    int n = A.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double m = A[j][i] / A[i][i];
            b[i] -= m * b[i];

            for (int k = i; k < n; k++)
            {
                A[j][k] -= m * A[i][k];
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
}