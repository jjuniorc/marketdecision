#ifndef _NEURON_H_
#define _NEURON_H_

class Neuron
{
public:
    //Constructor
    Neuron(double val);

    void setVal(double v);

    //Fast Sigmoid Function
    // f(x) = x / (1 + |x|)
    void activate();

    //Derivative for fast sigmoid funcion
    //f'(x) = f(x) * (1 - f(x))
    void derive();

    //Getter
    double getVal() { return this->val; }
    double getActivatedVal() { return this->activatedVal; }
    double getDerivedVal() { return this->derivedVal; }

private:
    // Example of value = 1.5
    double val;

    // Example of value = between 0 to 1 (range for normalization by fast sigmoid function)
    double activatedVal;

    // Applied for sigmoid function
    double derivedVal;
};

#endif
