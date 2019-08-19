#include "Neuron.h"
//#include "math.h"
#include <cmath>
//Constructor
Neuron::Neuron(double val)
{
    /*
    this->val = val;
    activate();
    derive();
    */
    this->setVal(val);
}

void Neuron::setVal(double v)
{
    this->val = v;
    activate();
    derive();
}

//Fast Sigmoid Function
// f(x) = x / (1 + |x|)
void Neuron::activate()
{
    this->activatedVal = this->val / (1 + std::abs(this->val));
}


//Derivative for fast sigmoid funcion
//f'(x) = f(x) * (1 - f(x))
void Neuron::derive()
{
    this->derivedVal = this->activatedVal * (1 - this->activatedVal);
}
