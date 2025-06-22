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


vector<float> Layer::inputsIntoNodes(vector<float> inputs, int layerIndex) {
    vector<float> outputs = {};
    outputs.resize(this->nodes.size());

    if(layerIndex == 0) {
        outputs = inputs;
    }else {
        for(int i = 0; i < this->nodes.size(); i ++){

            float sum = 0;

            // zbrojimo dve sune od dva razlicita nodea

            if(this->nodes[i].function == Function::COS || this->nodes[i].function == Function::DIV_2 ||
                this->nodes[i].function == Function::MUL_2 || this->nodes[i].function == Function::SQUARE ||
                this->nodes[i].function == Function::SQRT || this->nodes[i].function == Function::SIN ||
                this->nodes[i].function == Function::TANH || this->nodes[i].function == Function::RELU ||
                this->nodes[i].function == Function::PLUS) {

                for(int j = 0; j < inputs.size(); j++) {
                    sum = sum + inputs[j]*this->nodes[i].weights[j];//tu skupi sumu svih tezina koje ulaze u node pomnozene sa outputom tog nnodea?
                }
            }


            int halfwayPoint = inputs.size()/2;
            int part1 = 0;
            int part2 = 0;

            if(this->nodes[i].function == Function::MINUS || this->nodes[i].function == Function::DIV ||
                this->nodes[i].function == Function::MUL) {

                for(int j = 0; j < halfwayPoint; j++) {
                    part1 += inputs[j]*this->nodes[i].weights[j];//tu skupi sumu svih tezina koje ulaze u node pomnozene sa outputom tog nnodea?
                }
                for(int j = halfwayPoint; j < inputs.size(); j++) {
                    part2 += inputs[j]*this->nodes[i].weights[j];
                }
            }

            // tu izracunaj funkciju nodea   MUL_2, DIV_2, SQUARE, SQRT, COS, SIN, TANH, PLUS, MINUS, MUL, DIV

            //TODO dodaj x+y x-y x*y x/y ReLu
            switch (this->nodes[i].function) { //PLUS, MINUS, MUL, DIV

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
                case Function::RELU:
                    if(sum <= 0) {
                        sum = 0;
                    }else {
                        sum = sum;
                    }
                    // cout <<"RELU" <<endl;
                break;
                case Function::PLUS:
                    sum = sum;
                    // cout <<"PLUS" <<endl;
                break;
                case  Function::MINUS:
                    sum = part1 - part2;
                    // cout <<"MINUS" <<endl;
                break;
                case Function::DIV:
                    if(fabs(part2) < 0.0000001) {
                        sum = part1;
                    } else {
                        sum = part1 / part2;
                    }
                    // cout <<"MINUS" <<endl;
                break;
                case Function::MUL:
                    sum = part1 * part2;
                    // cout <<"MUL" <<endl;
                break;
            }
            outputs[i] = sum;
        }
    }


    return outputs;
}


