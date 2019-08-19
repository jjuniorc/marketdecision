#include "general.h"

int main(int argc, char **argv)
{
    //First explanation
    /*
    //Input
    Neuron *n1 = new Neuron(0.9);
    Neuron *n2 = new Neuron(0.5);
    Neuron *n3 = new Neuron(0.1);

    //Output
    Neuron *outputNeuron = new Neuron(0.0);

    //90% confident that [0.9, 0.5, 0.1] is a dog
    */

    //Second explanation
    /*
    Neuron *n = new Neuron(1.5);

    cout << "Val: " << n->getVal() << endl;
    cout << "Activated Val: " << n->getActivatedVal() << endl;
    cout << "Derived Val: " << n->getDerivedVal() << endl;
    */

    //3rd explanation
    /*
    Matrix *m = new Matrix(3, 2, true);
    m->printToConsole();

    cout << "---------------" << endl;

    Matrix *mT = m->transpose();
    mT->printToConsole();
    */

    //4th explanation
    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    vector<double> input;
    input.push_back(1.0);
    input.push_back(0.0);
    input.push_back(1.0);

    NeuralNetwork *nn = new NeuralNetwork(topology);

    nn->setCurrentInput(input);

    nn->printToConsole();



    return 0;
}
// Function definition
int add(int a, int b)
{
    int add;
    add = a + b;
    // Return statement
    return add;
}
