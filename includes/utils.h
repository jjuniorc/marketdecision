#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
using namespace std;

#include "Matrix.h"

class utils
{
    public:
    static void multiplyMatrix(Matrix *a, Matrix *b, Matrix *c);
};


#endif
