//
// Created by <3 on 12.03.2025..
//

#include "Population.h"
#include "Constants.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
using namespace std;

Population::Population() {
    this->neuralNetList = {};
    neuralNetList.resize(Constants::POPULATION_SIZE);
}

Population::~Population() {}



void Population::neuralNetFitnessSort() {
    sort(neuralNetList.begin(), neuralNetList.end(),
              [](NeuralNet& n1, NeuralNet& n2)
              {
                  return n1.fitness < n2.fitness;
              });
}

NeuralNet &Population::getBestNeuralNet() {
    return neuralNetList[0];
}

float gaussFunction(float x) {//TODO na mailu je kako se to radi, msm da je sad dobro, provjeri s prof
    normal_distribution<double> N(0, 0.1);//???????????
    std::random_device rd;
    std::mt19937 rng(rd());
    mt19937 engine_= rng;
    double offset = N(engine_);
    double newValue = x + offset;

return newValue;
}


void Population::chooseParents() {
    float r = randomFloat(0,1);
    int halfway = Constants::POPULATION_SIZE / 2;

    if(r < Constants::BETTER_PARENT_ADVANTAGE) {
        int r1 = randomInt(0, halfway - 1);
        int r2 = randomInt(0,halfway - 1);

        parent1 = neuralNetList[r1];
        parent2 = neuralNetList[r2];

    }else if(r >= Constants::BETTER_PARENT_ADVANTAGE) {
        int r1 = randomInt(halfway, Constants::POPULATION_SIZE - 1);
        int r2 = randomInt(halfway,Constants::POPULATION_SIZE -1 );

        parent1 = neuralNetList[r1];
        parent2 = neuralNetList[r2];
    }
}


void Population::crossingOver1() {

    int amountOflayers = this->parent1.amountOfNodesInEachLayer.size();
    this->child1 = NeuralNet();
    this->child1.layers.resize(amountOflayers);
    this->child1.amountOfNodesInEachLayer = this->parent1.amountOfNodesInEachLayer;

    this->child2 = NeuralNet();
    this->child2.layers.resize(amountOflayers);
    this->child2.amountOfNodesInEachLayer = this->parent2.amountOfNodesInEachLayer;


    for(int i = 0; i <amountOflayers; i++) {
        if(i == 0) {
            this->child1.layers[i] = this->parent1.layers[i];
            this->child2.layers[i] = this->parent2.layers[i];
        }else{
            int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
            this->child1.layers[i].nodes.resize(amountOfNodesInLayer);
            this->child2.layers[i].nodes.resize(amountOfNodesInLayer);


            for(int j = 0; j < amountOfNodesInLayer; j++) {
                if(j < amountOfNodesInLayer/2) {
                    this->child1.layers[i].nodes[j] = this->parent1.layers[i].nodes[j];
                    this->child2.layers[i].nodes[j] = this->parent2.layers[i].nodes[j];
                }else {
                    this->child1.layers[i].nodes[j] = this->parent2.layers[i].nodes[j];
                    this->child2.layers[i].nodes[j] = this->parent1.layers[i].nodes[j];
                }
            }
        }
    }
}



void Population::crossingOver2() {
    //novi crossing over
    //co drugacije biraj node
    int amountOflayers = this->parent1.amountOfNodesInEachLayer.size();
    this->child1 = NeuralNet();
    this->child1.layers.resize(amountOflayers);
    this->child1.amountOfNodesInEachLayer = this->parent1.amountOfNodesInEachLayer;

    this->child2 = NeuralNet();
    this->child2.layers.resize(amountOflayers);
    this->child2.amountOfNodesInEachLayer = this->parent2.amountOfNodesInEachLayer;


    for(int i = 0; i <amountOflayers; i++) {
        if(i == 0) {
            this->child1.layers[i] = this->parent1.layers[i];
            this->child2.layers[i] = this->parent2.layers[i];
        }else{
            int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
            this->child1.layers[i].nodes.resize(amountOfNodesInLayer);
            this->child2.layers[i].nodes.resize(amountOfNodesInLayer);

            //ovo je novi dio:
            //gledano svaki node i 50/50 sanse kojeg roditelja biramo
            for(int j = 0; j < amountOfNodesInLayer; j++) {
                float r = randomFloat(0,1);
                if(r <= 0.5) {
                    this->child1.layers[i].nodes[j] = this->parent1.layers[i].nodes[j];
                    this->child2.layers[i].nodes[j] = this->parent2.layers[i].nodes[j];
                }else{
                    this->child1.layers[i].nodes[j] = this->parent2.layers[i].nodes[j];
                    this->child2.layers[i].nodes[j] = this->parent1.layers[i].nodes[j];
                }
            }
        }
    }
}

void Population::mutation1(int index) {

    float r = randomFloat(0,1);

    if(r < Constants::MUTATION_PROBABILITY) {

        //dva random indexa: index layera i index nodea u tom layeru i onda po tome dohvatit i mutirat
        int randomLayerIndex = randomInt(1, child1.layers.size() - 1);
        int amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
        int randomNodeIndex = randomInt(0, child1.layers[randomLayerIndex].nodes.size()-1);

        child1.layers[randomLayerIndex].nodes[randomNodeIndex] = Node(amountOfWeights);

        randomLayerIndex = randomInt(1, child2.layers.size() - 1);
        amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
        randomNodeIndex = randomInt(0, child2.layers[randomLayerIndex].nodes.size()-1);

        child2.layers[randomLayerIndex].nodes[randomNodeIndex] = Node(amountOfWeights);


    }else{
        //not mutating
        //cout <<"not mutating"<< endl;
    }
}

void Population::mutation2(int index) {
    //nova mutacija
    //uvijek mjenjamo funkciju nodea
    //mutacija:random broj cvorova uzet i u odredemnom postotku se mjeja funkcoje a u svima tezina ali samo malo (gauss)

    float r1 = randomFloat(0,1);
    int amountOfNodesInNet  = 0;

    for(int amountOfNodesInLayer: this->child1.amountOfNodesInEachLayer) {
        amountOfNodesInNet = amountOfNodesInNet + amountOfNodesInLayer;
    }

    if(r1 < Constants::MUTATION_PROBABILITY) {
        int amountOfNodesMutating = amountOfNodesInNet * Constants::PERCENTAGE_OF_NODES_MUTATING;

        for(int i = 0; i < amountOfNodesMutating; i++) {

            int randomLayerIndex1 = randomInt(1, this->child1.layers.size() - 1);
            int amountOfWeights1 = this->child1.amountOfNodesInEachLayer[randomLayerIndex1-1];//int amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
            int randomNodeIndex1 = randomInt(0, this->child1.layers[randomLayerIndex1].nodes.size()-1);

            int randomLayerIndex2 = randomInt(1, this->child2.layers.size() - 1);
            int amountOfWeights2 = this->child2.amountOfNodesInEachLayer[randomLayerIndex2-1];
            int randomNodeIndex2 = randomInt(0, this->child2.layers[randomLayerIndex2].nodes.size()-1);


            //nekim od nodeova promjenit funkciju, svima weight promjenit po gausu
            //tu promjenit tezine
            for(int j = 0; j < amountOfWeights1; j++) {
                this->child1.layers[randomLayerIndex1].nodes[randomNodeIndex1].weights[j] = gaussFunction(this->child1.layers[randomLayerIndex1].nodes[randomNodeIndex1].weights[j]);
            }
            for(int j = 0; j < amountOfWeights2; j++) {
                this->child2.layers[randomLayerIndex2].nodes[randomNodeIndex2].weights[j] = gaussFunction(this->child2.layers[randomLayerIndex2].nodes[randomNodeIndex2].weights[j]);
            }
            //nekim nodeovima promjenit funk

            //imamo random node i promjenili smo weight i sad jos imamo neku sansu da ce se i funkcija promjeniti
            float r2 = randomFloat(0,1);
            float r3 = randomFloat(0,1);

            if(r2 < Constants::CHANCE_OF_NODE_CHANGING_FUNCTIONS) {
                this->child1.layers[randomLayerIndex1].nodes[randomNodeIndex1].function = static_cast<Function>(randomInt(0,Constants::AMOUNT_OF_FUNCTIONS));
            }
            if(r3 < Constants::CHANCE_OF_NODE_CHANGING_FUNCTIONS) {
                this->child2.layers[randomLayerIndex2].nodes[randomNodeIndex2].function = static_cast<Function>(randomInt(0,Constants::AMOUNT_OF_FUNCTIONS));
            }
        }
    }else {
        //not mutating
    }
}



int Population::crossingOverAndMutation(Population &NewPop, int index, int crossingOverIndex, int mutationIndex, int randomCrossingOversMutations) {

    int coIndex;
    int mutIndex;

    if(index == 0){
        NewPop.neuralNetList[0] = this->getBestNeuralNet();//dodamo najbolju jedinku u novu populaciju
        return index;
    }
    //CROSSING_OVER==============================


    if(randomCrossingOversMutations == 0) {
        coIndex = crossingOverIndex;
        mutIndex = mutationIndex;
    }else if(randomCrossingOversMutations == 1) {

        coIndex = randomInt(0,1);
        // cout <<"coIndex:" << coIndex <<endl;
        mutIndex = randomInt(0,1);
        // cout <<"mutIndex:" << mutIndex <<endl;
    }

    // cout << "crossing over index: "<< coIndex << endl;
    // cout << "mutating index: "<< mutIndex << endl;

    if(coIndex == 0) {
        crossingOver1();

    }else if(coIndex == 1) {
        crossingOver2();
    }
    //MUTATION=====================================
    if(mutIndex == 0) {
        mutation1(index);

    }else if(mutIndex == 1) {
        mutation2(index);
    }


    NewPop.neuralNetList[index] = this->child1;
    index++;

    if(index != Constants::POPULATION_SIZE) {
        NewPop.neuralNetList[index] = this->child2;
    }

    return index;
}

