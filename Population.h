//
// Created by <3 on 12.03.2025..
//

#ifndef POPULATION_H
#define POPULATION_H
#include <vector>
#include "NeuralNet.h"
using namespace std;

class Population {

public:
    vector<NeuralNet> neuralNetList;
    NeuralNet parent1;
    NeuralNet parent2;

    Population();
    ~Population();

    void neuralNetFitnessSort();
    NeuralNet& getBestNeuralNet();
    void chooseParents();
    void entityFitnessEval();
    int crossingOverAndMutation(Population &NewPop, int index);

};



#endif //POPULATION_H

