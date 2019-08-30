#include "NeuralNetwork.h"

#include <iostream>
#include <algorithm>
using namespace std;

#include "MultiplyMatrix.h"
#include "utils.h"

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

void NeuralNetwork::backPropagation()
{
    vector<Matrix *> newWeights;
    Matrix *gradients;

    //Output to hidden
    int outputLayerIndex = this->layers .size() - 1;
    Matrix *derivedValuesYToZ = this->layers.at(outputLayerIndex)->matrixifyDerivedVals();
    Matrix *gradientsYToZ = new Matrix(1, this->layers.at(outputLayerIndex)->getNeurons().size(), false);
    for(unsigned i = 0; i < this->errors.size(); i++)
    {
        double d = derivedValuesYToZ->getValue(0, i);
        double e = this->errors.at(i);
        double g = d * e;
        gradientsYToZ->setValue(0, i, g);
    }

    int lastHiddenLayerIndex = outputLayerIndex - 1;
    Layer *lastHiddenLayer = this->layers.at(lastHiddenLayerIndex);
    Matrix *weightsOutputToHidden = this->weightMatrices.at(outputLayerIndex - 1);


    Matrix *transposedGradientsYToZ = gradientsYToZ->transpose();
    Matrix *activatedValsLastHiddenLayer = lastHiddenLayer->matrixifyActivatedVals();
    //Matrix *deltaOutputToHidden = new Matrix(weightsOutputToHidden->getNumRows(), weightsOutputToHidden->getNumCols(), false);
    //Matrix *deltaOutputToHidden = new Matrix(transposedGradientsYToZ->getNumRows(), activatedValsLastHiddenLayer->getNumCols(), false);
    Matrix *deltaOutputToHiddenMutiplied = new Matrix(transposedGradientsYToZ->getNumRows(), activatedValsLastHiddenLayer->getNumCols(), false);

    //Matrix *deltaOutputToHidden = (new utils::multiplyMatrix(gradientsYToZ->transpose(), lastHiddenLayer->matrixifyActivatedVals() ))->execute() ;
    utils::multiplyMatrix(transposedGradientsYToZ, activatedValsLastHiddenLayer, deltaOutputToHiddenMutiplied);

    Matrix *deltaOutputToHidden = deltaOutputToHiddenMutiplied->transpose();

    Matrix *newWeightsOutputToHidden = new Matrix(deltaOutputToHidden->getNumRows(), deltaOutputToHidden->getNumCols(), false);

    for(int r = 0; r < deltaOutputToHidden->getNumRows(); r++)
    {
        for(int c = 0; c < deltaOutputToHidden->getNumCols(); c++)
        {
            double originalWeight = weightsOutputToHidden->getValue(r, c);
            double deltaWeight = deltaOutputToHidden->getValue(r, c);
            newWeightsOutputToHidden->setValue(r, c, (originalWeight - deltaWeight));
        }
    }

    newWeights.push_back(newWeightsOutputToHidden);

    //cout << "Output to Hidden New Weights" << endl;
    //newWeightsOutputToHidden->printToConsole();

    //Copy gradientsYToZ to gradients
    gradients = new Matrix(gradientsYToZ->getNumCols(), gradientsYToZ->getNumCols(), false);
    for(int r = 0; r < gradientsYToZ->getNumRows(); r++)
    {
        for(int c = 0; c < gradientsYToZ->getNumCols(); c++)
        {
            gradients->setValue(r, c, gradientsYToZ->getValue(r, c) );
        }
    }

    //Moving from last hidden layer to input layer
    for(int i = (outputLayerIndex - 1); i > 0; i--)
    {
        Layer *l = this->layers.at(i);
        Matrix *derivedHidden = l->matrixifyDerivedVals();
        Matrix *derivedGradients = new Matrix(1, l->getNeurons().size(), false);
        Matrix *activatedHidden = l->matrixifyActivatedVals();

        Matrix *weightMatrix = this->weightMatrices.at(i);
        Matrix *originalWeight = this->weightMatrices.at(i - 1);

        for(int r = 0; r < weightMatrix->getNumRows(); r++)
        {
            double sum = 0;
            for(int c = 0; c < weightMatrix->getNumCols(); c++)
            {
                //cout << r << ", " << c << endl;
                //double p = gradients->getValue(r, c) * weightMatrix->getValue(r, c); //WRONG
                double p = gradients->getValue(0, c) * weightMatrix->getValue(r, c);
                sum += p;
            }

            double g = sum * activatedHidden->getValue(0, r);
            derivedGradients->setValue(0, r, g);
        }

        Matrix *leftNeurons = (i - 1 == 0) ? this->layers.at(0)->matrixifyVals() : this->layers.at(i - 1)->matrixifyActivatedVals() ;

        Matrix *transposedDerivedGradients = derivedGradients->transpose();
        Matrix *deltaWeightsMultiplied = new Matrix(transposedDerivedGradients->getNumRows(), leftNeurons->getNumCols(), false);
        utils::multiplyMatrix(transposedDerivedGradients, leftNeurons, deltaWeightsMultiplied);
        Matrix *deltaWeights = deltaWeightsMultiplied->transpose();

        //TODO
        //At 55m 24s

        Matrix *newWeightsHidden = new Matrix(deltaWeights->getNumRows(), deltaWeights->getNumCols(), false);
        for(int r = 0; r < newWeightsHidden->getNumRows(); r++)
        {
            for(int c = 0; c < newWeightsHidden->getNumCols(); c++)
            {
                double w = originalWeight->getValue(r, c);
                double d = deltaWeights->getValue(r, c);
                double n = w - d;
                newWeightsHidden->setValue(r, c, n);
            }
        }

        gradients = new Matrix(derivedGradients->getNumCols(), derivedGradients->getNumCols(), false);
        for(int r = 0; r < derivedGradients->getNumRows(); r++)
        {
            for(int c = 0; c < derivedGradients->getNumCols(); c++)
            {
                gradients->setValue(r, c, derivedGradients->getValue(r, c) );
            }
        }

        newWeights.push_back(newWeightsHidden);

    }

    //cout << "Done with back prop" << endl;

    std::reverse(newWeights.begin(), newWeights.end());
    this->weightMatrices = newWeights;

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
