//
// Created by <3 on 11.03.2025..
//

#include "Node.h"
#include <random>
using namespace std;
#include "Constants.h"

int randomInt(int min, int max) {
    return min + (rand() % (int)(max - min + 1));//0-6
}

float randomFloat(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

Node::Node(float input) {
    //kako svakom nodeu odredit kolko spojeva ima???
    this->value = input;
    this->function = static_cast<Function>(randomInt(0,6));

}

Node::Node(int amountOfWeights) {
    this->weights.reserve(amountOfWeights);
    this->weights.resize(amountOfWeights);
    this->function = static_cast<Function>(randomInt(0,6));

    for(int i = 0; i < amountOfWeights; i++) {
        this->weights[i] = randomFloat(0,1);
    }

}

Node::Node() {
    this->function = static_cast<Function>(randomInt(0,6));

}

Node::~Node() {

}

