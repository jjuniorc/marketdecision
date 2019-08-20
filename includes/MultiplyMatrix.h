#ifndef _MULTIPLYMATRIX_H_
#define _MULTIPLYMATRIX_H_

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

#include "Matrix.h"

class MultiplyMatrix
{
public:

    MultiplyMatrix(Matrix *a, Matrix *b);

    Matrix *execute();

private:
    Matrix *a;
    Matrix *b;
    Matrix *c;
};

#endif
