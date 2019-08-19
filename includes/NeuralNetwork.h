#ifndef _NEURALNETWORK_
#define _NEURALNETWORK_

#include <vector>
using namespace std;

#include "Matrix.h"
#include "Layer.h"

class NeuralNetwork
{
public:
    //Constructor
    NeuralNetwork(vector<int> topology);

    void setCurrentInput(vector<double> input);

    int getTopologySize();
    void setTopologySize(int topologySize);
    vector<int> getTopology();
    void setTopology(vector<int> topology);
    void printToConsole();

private:
    vector<double>      input;
    int                 topologySize;
    vector<int>         topology;
    vector<Layer *>     layers;
    vector<Matrix *>    weightMatrices;
};

#endif
