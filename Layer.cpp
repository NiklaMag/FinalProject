//
// Created by <3 on 11.03.2025..
//

#include "Layer.h"
#include "Node.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Layer::Layer() {
    this->nodes = {};
}
Layer::~Layer() {
}


vector<float> Layer::inputsIntoNodes(vector<float> inputs, int layerIndex) {//error
    vector<float> outputs = {};
    outputs.resize(this->nodes.size());

    if(layerIndex == 0) {
        outputs = inputs;
    }else {
        for(int i = 0; i < this->nodes.size(); i ++){

            float sum = 0;

            for(int j = 0; j < inputs.size(); j++) {
                sum = sum + inputs[j]*this->nodes[i].weights[j];
            }
            //tu izracunaj funkciju nodea   MUL_2, DIV_2, SQUARE, SQRT, COS, SIN, TANH

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
                    if(sum < 0) {
                        sum = sum *(-1);
                        sum = sqrt(sum);
                        sum = sum *(-1);
                    }else {
                        sum = sqrt(sum);
                    }
                break;
                case Function::TANH:
                    sum = tanh(sum);
                break;
                case Function::SQUARE:
                    sum = sum*sum;
                break;
            }
            outputs[i] = sum;
        }
    }


    return outputs;
}


