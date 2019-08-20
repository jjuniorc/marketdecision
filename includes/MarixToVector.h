#ifndef _MATRIXTOVECTOR_H_
#define _MATRIXTOVECTOR_H_

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

#include "Matrix.h"

class MatrixToVector
{
public:

    MatrixToVector(Matrix *a);

    vector<double> execute();

private:
    Matrix *a;
};

#endif
