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
    /*
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
    */

    //5th explanation
    /*
    vector<double> input;
    input.push_back(1);
    input.push_back(0);
    input.push_back(1);

    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    nn->feedForward();

    nn->printToConsole();
    */

    //6th explanation
    vector<double> input;
    input.push_back(1);
    input.push_back(0);
    input.push_back(1);

    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    nn->setCurrentTarget(input);

    //Training process
    //Training for 1000 times
    for(int i = 0; i < 1000; i++)
    {
        cout << "Epoch: " << i << endl;
        nn->feedForward();
        nn->setErrors();
        //nn->printToConsole();
        cout << "Total Error: " << nn->getTotalError() << endl;
        nn->backPropagation();

        cout << "=========================" << endl;
        cout << "OUTPUT: ";
        nn->printOutputToConsole();

        cout << "TARGET: ";
        nn->printTargetToConsole();

        cout << "INPUT: ";
        nn->printInputToConsole();
        cout << "=========================" << endl;
    }

    //nn->printHistoricalErrors();

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
