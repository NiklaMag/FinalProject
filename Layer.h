//
// Created by <3 on 11.03.2025..
//

#ifndef LAYERS_H
#define LAYERS_H
#include <vector>
#include "Node.h"

using namespace std;


class Layer {
public:

    vector<Node> nodes;
    // vector<float> nodeInputs;
    // vector<float> nodeOutputs;

    Layer();
    ~Layer();
    vector<float> inputsIntoNodes(vector<float> inputs, int layerIndex);
};



#endif //LAYERS_H
