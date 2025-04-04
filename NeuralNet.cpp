//
// Created by <3 on 11.03.2025..
//
//implementiraj get fitness

#include "NeuralNet.h"
#include <iostream>
#include <vector>
#include "Layer.h"
#include "Node.h"
using namespace std;

NeuralNet::NeuralNet(vector<int> amountOfNodesInEachLayer) {
    //creating a neural net, no inputs
    this->amountOfNodesInEachLayer = amountOfNodesInEachLayer;
    int amountOflayers = this->amountOfNodesInEachLayer.size();
    for(int i = 0; i < amountOflayers; i++) {
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

float NeuralNet::functionForRegression(vector<float> inputs) {

    float sum = 0;
    for(int i = 0; i < inputs.size(); i++) {
        sum = sum + (sin(inputs[i]) + cos(2*inputs[i]) + log(1 + pow(inputs[i], 2)));
    }
    return sum;
}




float NeuralNet::getFitness(vector<vector<float>> inputs) {

    vector<float> expectedOutputs = {};
    vector<float> realOutputs = {};
    expectedOutputs.resize(inputs.size());
    realOutputs.resize(inputs.size());

    for(int i = 0; i < inputs.size(); i++) {//ovo vrti korz sve input "skupove"
        // cout << "get fitness(inputs): " << i << endl;
        expectedOutputs[i] = functionForRegression(inputs[i]);
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

