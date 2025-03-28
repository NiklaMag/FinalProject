//
// Created by <3 on 11.03.2025..
//

#ifndef NEURALNET_H
#define NEURALNET_H
#include <vector>
#include "Layer.h"
using namespace std;
class NeuralNet {
public:
    vector<int> amountOfNodesInEachLayer;
    vector<Layer> layers;
    vector<float> inputs;
    vector<float> outputs;
    float fitness;
    NeuralNet();
    ~NeuralNet();
    NeuralNet( vector<int> amountOfNodesInEachLayer, vector<float> inputs);


    vector<float> inputsIntoLayers(vector<float> inputs);
    float getFitness();
    float functionForRegression(float input);
    void runInputs(vector<float> inputs);
};



#endif //NEURALNET_H
