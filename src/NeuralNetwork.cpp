#include "NeuralNetwork.h"

#include <iostream>
using namespace std;

#include "MultiplyMatrix.h"

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

    // Initialize empty errors
    for(int i = 0; i < topology.at(topology.size() - 1); i++)
    {
        errors.push_back(0.00);
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

void NeuralNetwork::setCurrentTarget(vector<double> target)
{
    this->target = target;
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


        if(ix < this->layers.size() - 1)
        {
            cout << "=====================" << endl;
            cout << "Weight Matrix: " << ix << endl;
            this->getWeightMatrix(ix)->printToConsole();
            cout << "=====================" << endl;
        }

    }
}

void NeuralNetwork::feedForward()
{
    for(unsigned i = 0; i < (this->layers.size() - 1); i++ )
    {
        Matrix *a = this->getNeuronMatrix(i);

        if(i != 0)
        {
            a = this->getActivatedNeuronMatrix(i);
        }

        Matrix *b = this->getWeightMatrix(i);
        Matrix *c = (new MultiplyMatrix(a, b))->execute();

        //vector<double> vals;
        for(int c_index = 0; c_index < c->getNumCols(); c_index++)
        {
            //vals.push_back(c->getValue(0, c_index));
            int nextLayerIndex = i + 1;
            this->setNeuronValue(nextLayerIndex, c_index, c->getValue(0, c_index));
        }
    }
}

/*
Matrix NeuralNetwork::getNeuronMatrix(int index)
{
    return this->layers.at(index)->matrixifyVals();
}

Matrix NeuralNetwork::getActivatedNeuronMatrix(int index)
{
    return this->layers.at(index)->matrixifyDerivedVals();
}

Matrix NeuralNetwork::getWeightMatrix(int index)
{
    return this->weightMatrices.at(index);
}
*/

Matrix *NeuralNetwork::getNeuronMatrix(int index)
{
    return this->layers.at(index)->matrixifyVals();
}

Matrix *NeuralNetwork::getActivatedNeuronMatrix(int index)
{
    return this->layers.at(index)->matrixifyActivatedVals();
}

Matrix *NeuralNetwork::getDerivedNeuronMatrix(int index)
{
    return this->layers.at(index)->matrixifyDerivedVals();
}

Matrix *NeuralNetwork::getWeightMatrix(int index)
{
    return this->weightMatrices.at(index);
}

void NeuralNetwork::setNeuronValue(int indexLayer, int indexNeuron, double val)
{
    this->layers.at(indexLayer)->setVal(indexNeuron, val);
}

double NeuralNetwork::getTotalError()
{
    return this->error;
}

vector<double> NeuralNetwork::getErrors()
{
    return this->errors;
}

void NeuralNetwork::setErrors()
{
    if(this->target.size() == 0)
    {
        cerr << "No target for this neural network" << endl;
        assert(false);
    }

    if(this->target.size() != this->layers.at(this->layers.size() - 1)->getNeurons().size())
    {
        cerr << "Target size is not the same as output layer size: " << this->layers.at(this->layers.size() -1)->getNeurons().size() << endl;
        assert(false);
    }

    this->error = 0.00;
    int outputLayerIndex = this->layers .size() - 1;
    vector<Neuron *> outputNeurons = this->layers.at(outputLayerIndex)->getNeurons();

    for(unsigned i = 0; i < target.size(); i++)
    {
        //Determine how far the activated value is from target value
        double tempErr = (outputNeurons.at(i)->getActivatedVal() - target.at(i));
        errors.at(i) = tempErr;
        this->error += tempErr;
    }

    historicalErrors.push_back(this->error);
}
