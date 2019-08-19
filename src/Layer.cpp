#include "Layer.h"

//Constructor
Layer::Layer(int size)
{
    this->size = size;

    for(int ix = 0; ix < size; ix++)
    {
        Neuron *n = new Neuron(0.00);
        this->neurons.push_back(n);
    }

}

void Layer::setVal(int i, double v)
{
    this->neurons.at(i)->setVal(v);
}

Matrix *Layer::matrixifyVals()
{
    Matrix *m = new Matrix(1, this->neurons.size(), false);

    for(unsigned ix = 0; ix < this->neurons.size(); ix++)
    {
        m->setValue(0, ix, this->neurons.at(ix)->getVal());
    }

    return m;
}

Matrix *Layer::matrixifyActivatedVals()
{
    Matrix *m = new Matrix(1, this->neurons.size(), false);

    for(unsigned ix = 0; ix < this->neurons.size(); ix++)
    {
        m->setValue(0, ix, this->neurons.at(ix)->getActivatedVal());
    }

    return m;
}

Matrix *Layer::matrixifyDerivedVals()
{
    Matrix *m = new Matrix(1, this->neurons.size(), false);

    for(unsigned ix = 0; ix < this->neurons.size(); ix++)
    {
        m->setValue(0, ix, this->neurons.at(ix)->getDerivedVal());
    }

    return m;
}
