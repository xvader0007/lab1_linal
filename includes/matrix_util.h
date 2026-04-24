#ifndef LAB1_LINAL_MATRIX_UTIL_H
#define LAB1_LINAL_MATRIX_UTIL_H

#include "types.h"

Matrix matrix_random_generate(int n, double low, double high, unsigned seed);
Vector vector_random_generate(int n, double low, double high, unsigned seed);
Matrix hilbert_matrix_generate(int n);
Vector multiply(const Matrix& a, const Vector& b);
double l2_norm(const Vector& a);
double compute_residual(const Matrix& a, const Vector& b, const Vector& x);

#endif //LAB1_LINAL_MATRIX_UTIL_H