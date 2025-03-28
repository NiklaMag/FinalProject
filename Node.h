//
// Created by <3 on 11.03.2025..
//

#ifndef NODE_H
#define NODE_H
#include <vector>
using namespace std;

int randomInt(int min, int max);
float randomFloat(float min, float max);

enum class Function{
    MUL_2, DIV_2, SQUARE, SQRT, COS, SIN, TANH
};

class Node {

public:
    vector<float> weights;
    Function function;
    float value;
    Node();
    ~Node();
    Node(int amountOfWeights);
    Node(float input);

};



#endif //NODE_H
