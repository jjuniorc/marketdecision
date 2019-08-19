#include "NeuralNetwork.h"

#include <iostream>
using namespace std;

//Constructor
NeuralNetwork::NeuralNetwork(vector<int> topology)
{
    setTopology(topology);
    setTopologySize(topology.size());

    for(int ix = 0; ix < getTopologySize(); ix++)
    {
        Layer *l = new Layer(getTopology().at(ix));
        this->layers.push_back(l);
    }

    for(int ix = 0; ix < getTopologySize() - 1; ix++)
    {
        Matrix *m = new Matrix(getTopology().at(ix), getTopology().at(ix + 1), true);
        this->weightMatrices.push_back(m);
    }

}

void NeuralNetwork::setCurrentInput(vector<double> input)
{
    this->input = input;

    //Configure first layer (at 0) with input values
    for(unsigned ix = 0; ix < input.size(); ix++)
    {
        this->layers.at(0)->setVal(ix, input.at(ix));
    }
}

int NeuralNetwork::getTopologySize()
{
    return this->topologySize;
}

void NeuralNetwork::setTopologySize(int topologySize)
{
    this->topologySize = topologySize;
}

vector<int> NeuralNetwork::getTopology()
{
    return this->topology;
}

void NeuralNetwork::setTopology(vector<int> topology)
{
    this->topology = topology;
}

void NeuralNetwork::printToConsole()
{
    for(unsigned ix = 0; ix < this->layers.size(); ix++)
    {
        cout << "LAYER: " << ix << endl;
        Matrix *m;
        if(ix == 0)
        {
            m = this->layers.at(ix)->matrixifyVals();
            m->printToConsole();
        }
        else
        {
            m = this->layers.at(ix)->matrixifyActivatedVals();
            m->printToConsole();
        }
    }
}
