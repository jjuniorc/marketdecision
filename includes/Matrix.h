#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
using namespace std;

class Matrix
{
public:

    Matrix(int numRows, int numCols, bool isRandom);

    Matrix *transpose();
    void setValue(int r, int c, double v);
    double getValue(int r, int c);

    double generateRandomNumber();
    void printToConsole();

    //Getters
    int getNumRows() { return this->numRows; }
    int getNumCols() { return this->numCols; }


private:
    int numRows;
    int numCols;
    bool isRandom;

    vector<vector<double>> values;
};

#endif
