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
