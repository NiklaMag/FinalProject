//
// Created by <3 on 11.03.2025..
//
//implementiraj get fitness

#include "NeuralNet.h"

#include <iostream>
#include <ostream>
#include <vector>
#include "Constants.h"
#include "Layer.h"
#include "Node.h"
using namespace std;

NeuralNet::NeuralNet(vector<int> amountOfNodesInEachLayer, vector<float> inputs) {//dodat jos input i onda to prosljedit prvom nodeu i to ubacit u value&&
    //creating a neural net, no inputs
    //tu treba reserve and resize napravit za this->layers
    this->amountOfNodesInEachLayer = amountOfNodesInEachLayer;
    for(int i = 0; i < Constants::AMOUNT_OF_LAYERS; i++) {//ide od 1 - 3
        int amountOfNodesInLayer = amountOfNodesInEachLayer[i];
        Layer layer = Layer();
        this->layers.push_back(layer);

        if (i == 0) {
            //postavljanje prvog layera
            for(int j = 0; j < amountOfNodesInLayer; j++ ) {
                Node node = Node(); //gereriranje nodea sa random tezinama 0-1 &&ovdje
                node.value = inputs[0];//eh.....ovdje da ima vise inputova bi tu islo od j
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

}
NeuralNet::~NeuralNet() {

}

vector<float> NeuralNet::inputsIntoLayers(vector<float> inputs) {
    //cout <<"inputsIntoLayers this->layers.size():" <<this->layers.size() << endl;

    for(int i = 0; i < this->layers.size(); i++) {
        inputs = layers[i].inputsIntoNodes(inputs, i);
    }
return inputs;
}

float NeuralNet::functionForRegression(float input) {
    //f(x) = (e^-x )sin(2x) + (x^2)/4 + cos(3x) + ln(1+x^2)
    // float firstPart = exp(-input) * sin(2*input);
    // float secondPart = pow(input, 2)/4;
    // float thirdpart = cos(3*input) + log(1 + pow(input,2));
    return exp(-input) * sin(2*input) + pow(input, 2)/4 + cos(3*input) + log(1 + pow(input,2));
}




float NeuralNet::getFitness() {

    // float fitness;
    //cout << "c1"<<endl;
    vector<float> expectedOutputs;
    vector<float> in;

    expectedOutputs.reserve(this->inputs.size());
    expectedOutputs.resize(this->inputs.size());

    this->outputs.reserve(this->inputs.size());
    this->outputs.resize(this->inputs.size());
    //cout << "c2"<<endl;
    for(int i = 0; i < this->inputs.size(); i++) {
       // cout << "c3"<<endl;
        expectedOutputs[i] = functionForRegression(this->inputs[i]);
        //cout << "c4"<<endl;
        in = {this->inputs[i]};

        //cout << "c5 "<<this->inputs[i]<<endl; //pukne kd je this->inputs[i] == 1
        //this->inputs = in;//kad unosimo inpute treba ih bit kolko ima nodeova u prvom layeru
        in = inputsIntoLayers(in);
        //cout << "c6"<<endl;
        this->outputs[i] =  in[0];//this->outputs shoudl be a vector of vectors so if we have more outputs its handles########
        //cout << "c7"<<endl;
        //fine all before this
    }//this gives expectedResults and gotten results
    float sum = 0;
    //cout << "c8"<<endl;
    for(int i = 0; i <this->outputs.size(); i++) {//ovdje greska prvo se moraju izvrtit svi inputi pa tek onda ova greska racunat
        //cout << "c9"<<endl;
        sum = sum + pow(expectedOutputs[i] - this->outputs[i], 2);
        //cout << "c10"<<endl;
    }
    //cout << "c11"<<endl;
    //error function:
    //sqrt( (1/numberOfInputs) * sum((expectedRes - gottenRes)^2) )
    // float fitness = sqrt((1/outputs.size())*sum);//ovjde ne valja, ZASTO, sve do tud je ok
    float fitness = sqrt((1.0f / static_cast<float>(outputs.size())) * sum);
    //cout << "c12"<<endl;

return fitness;
}


// void NeuralNet::runInputs(vector<float> inputs) {
//     //za svaki input vrati odgovarajuci output mreze
//     vector<float> in;
//
//     for(int i = 0; i < inputs.size(); i++) {
//         in = {inputs[i]};
//         this->inputs = in;
//         in = inputsIntoLayers(in);
//         this->outputs.push_back(in[0]);
//         //vrati vektor outputa, prvi element nakon zadnje iteracije je output mreze
//     }
//
// }
