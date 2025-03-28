//
// Created by <3 on 11.03.2025..
//

#include "Layer.h"
#include "Node.h"
#include <vector>
#include <cmath>
#include <iostream>

#include "NeuralNet.h"
using namespace std;

Layer::Layer() {

}
Layer::~Layer() {
}


vector<float> Layer::inputsIntoNodes(vector<float> inputs, int layerIndex) {//error
    vector<float> outputs;
    outputs.reserve(this->nodes.size());
    outputs.resize(this->nodes.size());
    //cout << "nn1" << endl;
    if(layerIndex == 0) {
        outputs = inputs;
        ///cout << "nn2" << endl;
    }else {
        //cout << "nn3" << endl;
        //cout << "layer index" << layerIndex << endl;
        for(int i = 0; i < this->nodes.size(); i ++){
            //cout << "nn4" << endl;
            float sum = 0;

            //cout << "nn5" << endl;
            for(int j = 0; j < inputs.size(); j++) {
                //cout << "nn6" << endl;
                // cout << "sum: " << sum << endl;
                // cout << "i:" << i <<"       j:" << j << endl;
                // cout << "inputs[" << j <<"] " << inputs[j] <<endl;
                //
                // cout << "this->nodes[" << i << "].weights[" << j<<"] " << this->nodes[i].weights[j] << endl;///?????
                sum = sum + inputs[j]*this->nodes[i].weights[j]; //nodeovi se moraju inicijalizirat kako spada-> tezine i funkcije
                //cout << "after the sum line" << endl;
            }
            //tu izracunaj funkciju nodea   MUL_2, DIV_2, SQUARE, SQRT, COS, SIN, TANH
            //cout << "nn8" << endl;
            switch (this->nodes[i].function) {

                case Function::COS:
                    sum = cos(sum);
                break;
                case Function::DIV_2:
                    sum = sum/2;
                break;
                case Function::MUL_2:
                    sum = sum*2;
                break;
                case Function::SIN:
                    sum = sin(sum);
                break;
                case Function::SQRT:
                    sum = sqrt(sum);
                break;
                case Function::TANH:
                    sum = tanh(sum);
                break;
                case Function::SQUARE:
                    sum = sum*sum;
                break;
            }
            //cout << "nn9" << endl;
            //this->nodes[i].value = sum;
            outputs[i] = sum;
            //cout << "nn10" << endl;
        }
    }


    return outputs;
}


