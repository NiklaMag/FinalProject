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

float gaussFunction(float x) {
    //f(x) = exp(-x^2);
    return exp(pow(-x, 2));
    //mozda je ovjde: exp(-pow(x, 2)); ????????
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
    this->child1.layers.reserve(amountOflayers);
    this->child1.layers.resize(amountOflayers);
    this->child1.amountOfNodesInEachLayer = this->parent1.amountOfNodesInEachLayer;

    this->child2 = NeuralNet();
    this->child2.layers.reserve(amountOflayers);
    this->child2.layers.resize(amountOflayers);
    this->child2.amountOfNodesInEachLayer = this->parent2.amountOfNodesInEachLayer;


    for(int i = 0; i <amountOflayers; i++) {
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
    //cout << "co1"<<endl;
}



void Population::crossingOver2() {
    //novi crossing over
    //co drugacije biraj node
    int amountOflayers = this->parent1.amountOfNodesInEachLayer.size();
    this->child1 = NeuralNet();
    this->child1.layers.reserve(amountOflayers);
    this->child1.layers.resize(amountOflayers);
    this->child1.amountOfNodesInEachLayer = this->parent1.amountOfNodesInEachLayer;

    this->child2 = NeuralNet();
    this->child2.layers.reserve(amountOflayers);
    this->child2.layers.resize(amountOflayers);
    this->child2.amountOfNodesInEachLayer = this->parent2.amountOfNodesInEachLayer;


    for(int i = 0; i <amountOflayers; i++) {
        if(i == 0) {
            this->child1.layers[i] = this->parent1.layers[i];
            this->child2.layers[i] = this->parent2.layers[i];
        }else{
            int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
            this->child1.layers[i].nodes.reserve(amountOfNodesInLayer);
            this->child1.layers[i].nodes.resize(amountOfNodesInLayer);
            this->child2.layers[i].nodes.reserve(amountOfNodesInLayer);
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
    //cout << "co2"<<endl;
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

    float r1 = randomFloat(0,1);
    int amountOfNodesInNet  = 0;

    for(int amountOfNodesInLayer: this->child1.amountOfNodesInEachLayer) {
        amountOfNodesInNet = amountOfNodesInNet + amountOfNodesInLayer;
        //cout << amountOfNodesInNet << endl;
    }

    if(r1 < Constants::MUTATION_PROBABILITY) {
        int amountOfNodesMutating = amountOfNodesInNet * Constants::PERCENTAGE_OF_NODES_MUTATING;
        for(int i = 0; i < amountOfNodesMutating; i++) {//bilo bi dobro da se nekako prati koji nodeovi su vec mutirani koji ne i da se samo njih mutira(oni koji nisu), mozda neki flag mutated i ond stavimo na true kd se izmutira i ond preskocimo ako je taj node mutiran vec

            int randomLayerIndex1 = randomInt(1, this->child1.layers.size() - 1);
            int amountOfWeights1 = this->child1.amountOfNodesInEachLayer[randomLayerIndex1-1];
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
                this->child1.layers[randomLayerIndex1].nodes[randomNodeIndex1].function = static_cast<Function>(randomInt(0,6));
            }
            if(r3 < Constants::CHANCE_OF_NODE_CHANGING_FUNCTIONS) {
                this->child2.layers[randomLayerIndex2].nodes[randomNodeIndex2].function = static_cast<Function>(randomInt(0,6));
            }
        }
    }else {
        //not mutating
    }
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
        NewPop.neuralNetList[index] = this->child2;
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
