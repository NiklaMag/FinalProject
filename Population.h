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
    NeuralNet child1;
    NeuralNet child2;

    Population();
    ~Population();

    void neuralNetFitnessSort();
    NeuralNet& getBestNeuralNet();
    void chooseParents();
    void entityFitnessEval();
    int crossingOverAndMutation(Population &NewPop, int index, int crossingOverIndex, int mutationIndex, int randomCrossingOversMutations);
    void crossingOver1();
    void mutation1(int index);
    void crossingOver2();
    void mutation2(int index);


};



#endif //POPULATION_H

