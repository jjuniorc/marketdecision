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
    void setCurrentTarget(vector<double> target);

    int getTopologySize();
    void setTopologySize(int topologySize);
    vector<int> getTopology();
    void setTopology(vector<int> topology);
    void feedForward();
    void printToConsole();

    Matrix *getNeuronMatrix(int index);
    Matrix *getActivatedNeuronMatrix(int index);
    Matrix *getDerivedNeuronMatrix(int index);
    Matrix *getWeightMatrix(int index);

    void setNeuronValue(int indexLayer, int indexNeuron, double val);

    double getTotalError();
    vector<double> getErrors();
    void setErrors();


private:
    int                 topologySize;
    vector<int>         topology;
    vector<Layer *>     layers;
    vector<double>      input;
    vector<Matrix *>    weightMatrices;
    vector<double>      target;
    double              error;
    vector<double>      errors;
    vector<double>      historicalErrors;
};

#endif
