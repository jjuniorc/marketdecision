#include "Matrix.h"

#include <iostream>
#include <random>
using namespace std;

//Constructor
Matrix::Matrix(int numRows, int numCols, bool isRandom)
{
    this->numRows = numRows;
    this->numCols = numCols;
    this->isRandom = isRandom;

    for(int i = 0; i < numRows; i++)
    {
        vector<double> colValues;

        for(int j = 0; j < numCols; j++)
        {
            double r = 0.00;
            if(isRandom)
            {
                r = this->generateRandomNumber();
            }

            colValues.push_back(r);
        }

        this->values.push_back(colValues);
    }
}

//Set Value
void Matrix::setValue(int r, int c, double v)
{
    this->values.at(r).at(c) = v;
}

//Get Value
double Matrix::getValue(int r, int c)
{
    return this->values.at(r).at(c);
}

//Show matrix values to console
void Matrix::printToConsole()
{
    for(int i = 0; i < this->getNumRows(); i++)
    {
        for(int j = 0; j < this->getNumCols(); j++)
        {
            cout << this->values.at(i).at(j) << "\t\t";
        }
        cout << endl;
    }
}

//Transpose current matrix values
Matrix *Matrix::transpose()
{
    Matrix *m = new Matrix(this->numCols, this->numRows, false);

    for(int i = 0; i < this->getNumRows(); i++)
    {
        for(int j = 0; j < this->getNumCols(); j++)
        {
            m->setValue(j, i, this->getValue(i, j));
        }
    }

    return m;
}

//Create a random number between 0 and 1
double Matrix::generateRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    //std::uniform_real_distribution<> dis(-.0001, .0001);
    std::uniform_real_distribution<> dis(0, 1);

    return dis(gen);
}
