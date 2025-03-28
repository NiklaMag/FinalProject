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
    neuralNetList.reserve(Constants::POPULATION_SIZE);
    neuralNetList.resize(Constants::POPULATION_SIZE);
}

Population::~Population() {}



void Population::neuralNetFitnessSort() {
    sort(neuralNetList.begin(), neuralNetList.end(),
              [](NeuralNet& n1, NeuralNet& n2)
              {
                  return n1.getFitness() < n2.getFitness();
              });
}

NeuralNet &Population::getBestNeuralNet() {
    return neuralNetList[0];
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

    this->child1 = NeuralNet();
    this->child1.layers.reserve(Constants::AMOUNT_OF_LAYERS);
    this->child1.layers.resize(Constants::AMOUNT_OF_LAYERS);
    this->child1.amountOfNodesInEachLayer = this->parent1.amountOfNodesInEachLayer;

    this->child2 = NeuralNet();
    this->child2.layers.reserve(Constants::AMOUNT_OF_LAYERS);
    this->child2.layers.resize(Constants::AMOUNT_OF_LAYERS);
    this->child2.amountOfNodesInEachLayer = this->parent2.amountOfNodesInEachLayer;


    for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
        if(i == 0) {
            this->child1.layers[i] = this->parent1.layers[i];
            this->child2.layers[i] = this->parent2.layers[i];
        }else{
            int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
            this->child1.layers[i].nodes.reserve(amountOfNodesInLayer);
            this->child1.layers[i].nodes.resize(amountOfNodesInLayer);
            this->child2.layers[i].nodes.reserve(amountOfNodesInLayer);
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
}

void Population::mutation1(int index) {

    float r = randomFloat(0,1);

    if(r < Constants::MUTATION_PROBABILITY) {

        //dva random indexa: index layera i index nodea u tom layeru i onda po tome dohvatit i mutirat
        //sad ovo radi kako treba
        int randomLayerIndex = randomInt(1, child1.layers.size() - 1);
        int amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
        int randomNodeIndex = randomInt(0, child1.layers[randomLayerIndex].nodes.size()-1);

        child1.layers[randomLayerIndex].nodes[randomNodeIndex] = Node(amountOfWeights);

        randomLayerIndex = randomInt(1, child2.layers.size() - 1);
        amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
        randomNodeIndex = randomInt(0, child2.layers[randomLayerIndex].nodes.size()-1);

        child2.layers[randomLayerIndex].nodes[randomNodeIndex] = Node(amountOfWeights);
        //DRUGI NACIN

    }else{
        //not mutating
        //cout <<"not mutating"<< endl;
    }
}

void Population::mutation2(int index) {
    //nova mutacija
    //uvijek mjenjamo funkciju nodea
    //mutacija:random broj cvorova uzet i u odredemnom postotku se mjeja funkcoje a u svima tezina ali samo malo (gauss)

}



int Population::crossingOverAndMutation(Population &NewPop, int index, int crossingOverIndex, int mutationIndex) {

    if(index == 0){
        NewPop.neuralNetList[0] = this->getBestNeuralNet();//dodamo najbolju jedinku u novu populaciju
        return index;
    }
    //CROSSING_OVER==============================
    if(crossingOverIndex == 1) {
        crossingOver1();
    }else if(crossingOverIndex == 2) {
        crossingOver2();
    }
    //MUTATION=====================================
    if(mutationIndex == 1) {
        mutation1(index);
    }else if(mutationIndex == 2) {
        mutation2(index);
    }

    NewPop.neuralNetList[index] = this->child1;
    index++;

    if(index != Constants::POPULATION_SIZE) {
        NewPop.neuralNetList[index] = child2;
    }

    return index;
}








// int Population::crossingOverAndMutation(Population &NewPop, int index) {
//
//     if(index == 0){
//         NewPop.neuralNetList[0] = this->getBestNeuralNet();//dodamo najbolju jedinku u novu populaciju
//         return index;
//     }
//
//     //CROSSING_OVER==============================
//     NeuralNet child1 = NeuralNet();
//     child1.layers.reserve(Constants::AMOUNT_OF_LAYERS);
//     child1.layers.resize(Constants::AMOUNT_OF_LAYERS);
//     child1.amountOfNodesInEachLayer = parent1.amountOfNodesInEachLayer;
//
//     NeuralNet child2= NeuralNet();
//     child2.layers.reserve(Constants::AMOUNT_OF_LAYERS);
//     child2.layers.resize(Constants::AMOUNT_OF_LAYERS);
//     child2.amountOfNodesInEachLayer = parent2.amountOfNodesInEachLayer;
//
//
//     for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
//         if(i == 0) {
//             child1.layers[i] = parent1.layers[i];
//             child2.layers[i] = parent2.layers[i];
//         }else{
//             int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
//             child1.layers[i].nodes.reserve(amountOfNodesInLayer);
//             child1.layers[i].nodes.resize(amountOfNodesInLayer);
//             child2.layers[i].nodes.reserve(amountOfNodesInLayer);
//             child2.layers[i].nodes.resize(amountOfNodesInLayer);
//
//
//             for(int j = 0; j < amountOfNodesInLayer; j++) {
//
//                 if(j < amountOfNodesInLayer/2) {
//
//                     child1.layers[i].nodes[j] = parent1.layers[i].nodes[j];
//                     child2.layers[i].nodes[j] = parent2.layers[i].nodes[j];
//                 }else {
//                     child1.layers[i].nodes[j] = parent2.layers[i].nodes[j];
//                     child2.layers[i].nodes[j] = parent1.layers[i].nodes[j];
//                 }
//             }
//         }
//     }
//
//
//     //MUTATION=====================================
//     float r = randomFloat(0,1);
//
//     if(r < Constants::MUTATION_PROBABILITY) {
//
//         // int totalNumberOfNodes = 0;
//         // for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
//         //     int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
//         //     for(int j = 0; j < amountOfNodesInLayer; j++) {
//         //         totalNumberOfNodes++;
//         //     }
//         // }
//         //
//         // //============================================================================
//         // int currentNodeIndex = 0;
//         // int mutatingNodeIndex1 = randomInt(0, totalNumberOfNodes);
//         // int mutatingNodeIndex2 = randomInt(0, totalNumberOfNodes);
//         //
//         // for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
//         //     int amountOfNodesInLayer = child1.layers[i].nodes.size();
//         //     int amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[i-1];
//         //
//         //     for(int j = 0; j < amountOfNodesInLayer; j++) {
//         //         if(currentNodeIndex == mutatingNodeIndex1) {
//         //
//         //             float value = child1.layers[i].nodes[j].value;
//         //             child1.layers[i].nodes[j] = Node(amountOfWeights);
//         //             child1.layers[i].nodes[j].value = value;
//         //         }
//         //         if(currentNodeIndex == mutatingNodeIndex2) {
//         //             //mutate this node
//         //             float value = child2.layers[i].nodes[j].value;
//         //             child2.layers[i].nodes[j] = Node(amountOfWeights);
//         //             child2.layers[i].nodes[j].value = value;
//         //         }
//         //         currentNodeIndex++;
//         //     }
//         // }
//         //=============================================================================
//         //dva random indexa: index layera i index nodea u tom layeru i onda po tome dohvatit i mutirat
//         //sad ovo radi kako treba
//         int randomLayerIndex = randomInt(1, child1.layers.size() - 1);
//         int amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
//         int randomNodeIndex = randomInt(0, child1.layers[randomLayerIndex].nodes.size()-1);
//
//         child1.layers[randomLayerIndex].nodes[randomNodeIndex] = Node(amountOfWeights);
//
//         randomLayerIndex = randomInt(1, child2.layers.size() - 1);
//         amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[randomLayerIndex-1];
//         randomNodeIndex = randomInt(0, child2.layers[randomLayerIndex].nodes.size()-1);
//
//         child2.layers[randomLayerIndex].nodes[randomNodeIndex] = Node(amountOfWeights);
//         //DRUGI NACIN
//
//     }else{
//         //not mutating
//         //cout <<"not mutating"<< endl;
//     }
//
//     NewPop.neuralNetList[index] = child1;
//     index++;
//
//     if(index != Constants::POPULATION_SIZE) {
//         NewPop.neuralNetList[index] = child2;
//     }
//
//     return index;
// }
