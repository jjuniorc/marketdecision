#ifndef _LAYER_H_
#define _LAYER_H_

#include "Neuron.h"
#include "Matrix.h"
#include <vector>
using namespace std;

class Layer
{
public:

    Layer(int size);

    void setVal(int i, double v);
    Matrix *matrixifyVals();
    Matrix *matrixifyActivatedVals();
    Matrix *matrixifyDerivedVals();

    //vector<double> getActivatedVals();

    vector<Neuron *> getNeurons();
    void setNeuron(vector<Neuron *> neurons);

private:
    int size;
    vector<Neuron *> neurons;
};

#endif
