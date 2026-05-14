#ifndef LAB1_LINAL_LU_H
#define LAB1_LINAL_LU_H

#include "types.h"

struct LUResult
{
    Matrix L;
    Matrix U;
};

LUResult lu_decompose(const Matrix& A);
Vector forward_substitution(const Matrix& L, const Vector& b);
Vector back_substitution(const Matrix& U, const Vector& y);
Vector solve_lu(const LUResult& lu, Vector b);

#endif //LAB1_LINAL_LU_H
