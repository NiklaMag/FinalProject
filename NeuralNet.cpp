//
// Created by <3 on 11.03.2025..
//


#include "NeuralNet.h"
#include <iostream>
#include <vector>
#include "Layer.h"
#include "Node.h"
using namespace std;

NeuralNet::NeuralNet(vector<int> amountOfNodesInEachLayer) {
    //creating a neural net, no inputs
    this->amountOfNodesInEachLayer = amountOfNodesInEachLayer;
    int amountOfLayers = this->amountOfNodesInEachLayer.size();
    for(int i = 0; i < amountOfLayers; i++) {
        int amountOfNodesInLayer = amountOfNodesInEachLayer[i];
        Layer layer = Layer();
        this->layers.push_back(layer);

        if (i == 0) {
            //postavljanje prvog layera
            for(int j = 0; j < amountOfNodesInLayer; j++ ) {
                Node node = Node(); //gereriranje nodea sa random tezinama 0-1 &&ovdje
                this->layers[i].nodes.push_back(node);
            }
        }else if(i > 0) {
            for(int j = 0; j < amountOfNodesInLayer; j++ ) {//ide u krug za svaki node u layeru
                int amountOfWeights = amountOfNodesInEachLayer[i - 1];//kolko ce tezina imati taj node
                Node node = Node(amountOfWeights); //gereriranje nodea sa random tezinama 0-1
                this->layers[i].nodes.push_back(node);//dodamo node u listu nodeova u tom layeru
            }
        }
    }
}


NeuralNet::NeuralNet() {
    this->layers = {}
;
}
NeuralNet::~NeuralNet() {

}

vector<float> NeuralNet::inputsIntoLayers(vector<float> inputs) {
    for(int i = 0; i < this->layers.size(); i++) {
        inputs = layers[i].inputsIntoNodes(inputs, i);
    }
return inputs;
}


float NeuralNet::functionForRegression(vector<float> inputs, int functionIndex) {

    float sum = 0;
    float x;
    float y;


    switch(functionIndex) {
        case 0://log (x + 1) + log (x2 + 1) [0, 20]
            x = inputs[0];
            y = inputs[1];
            sum = log(x + 1) + log(pow(x, 2) + 1);
        break;

        case 1://sin(x) + sin(y 2)       [−10, 10]
            x = inputs[0];
            y = inputs[1];
            sum = sin(x) + sin(pow(y,2));
        break;

        case 2://2·sin(x)·cos(y )       [−10, 10]
            x = inputs[0];
            y = inputs[1];
            sum = 2 * sin(x) * cos(y);
        break;

        case 3://x·y + sin((x + 1)·(y−1))     [−10, 10]
            x = inputs[0];
            y = inputs[1];
            sum = x * y + sin((x + 1)*(y-1));
        break;

        case 4:// Keijzer 15 f(x, y) = 8 / (2 + x^2 + y^2)  [−10, 10]
            x = inputs[0];
            y = inputs[1];
            sum = 8 / (2 + pow(x, 2) + pow(y, 2));
        break;

        case 5:// Keijzer 16 f(x, y) = x^3 / 5 + y^3 / 2 - y - x  [−10, 10]
            x = inputs[0];
            y = inputs[1];
            sum = pow(x, 3)/5 + pow(y, 3)/2 - y - x;
        break;
    }


    return sum;
}


float NeuralNet::getFitness(vector<vector<float>> inputs, int functionIndex, FileReader fileReader) {

    vector<float> expectedOutputs = {};
    vector<float> realOutputs = {};
    expectedOutputs.resize(inputs.size());
    realOutputs.resize(inputs.size());



    for(int i = 0; i < inputs.size(); i++) {//ovo vrti korz sve input "skupove"
        if(fileReader.blackBox == 0) {
            expectedOutputs[i] = functionForRegression(inputs[i], functionIndex);

        }else if(fileReader.blackBox == 1 && expectedOutputs.size() == fileReader.expectedOutputs.size()) {
            expectedOutputs[i] = fileReader.expectedOutputs[i];
        }

        inputs[i] = inputsIntoLayers(inputs[i]);
        realOutputs[i] = inputs[i][0];
    }

    float sum = 0;

    for(int j = 0; j <realOutputs.size(); j++) {
        sum = sum + pow(expectedOutputs[j] - realOutputs[j], 2);
    }
    float fitness = sqrt((1.0f / static_cast<float>(realOutputs.size())) * sum);

return fitness;
}

