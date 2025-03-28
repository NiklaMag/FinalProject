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
    //cout << "choose parents function\n";
    //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);//random float
    float r = randomFloat(0,1);
    int halfway = Constants::POPULATION_SIZE / 2;

    //cout << "index for choosing parents:" << r << "   halfway point:" << halfway << "\n";

    if(r < Constants::BETTER_PARENT_ADVANTAGE) {
        int r1 = randomInt(0, halfway - 1);
        int r2 = randomInt(0,halfway - 1);

        //cout << "r1: " << r1 << "\n";
        //cout << "r2: " << r2 << "\n";

        parent1 = neuralNetList[r1];
        parent2 = neuralNetList[r2];

    }else if(r >= Constants::BETTER_PARENT_ADVANTAGE) {
        int r1 = randomInt(halfway, Constants::POPULATION_SIZE - 1);
        int r2 = randomInt(halfway,Constants::POPULATION_SIZE -1 );

        //cout << "r1: " << r1 << "\n";
        //cout << "r2: " << r2 << "\n";

        parent1 = neuralNetList[r1];
        parent2 = neuralNetList[r2];
    }
}


int Population::crossingOverAndMutation(Population &NewPop, int index) {
    //vraca zadnji idex na koji je nesto stavljeno u novu populaciju ??

    if(index == 0){
        NewPop.neuralNetList[0] = this->getBestNeuralNet();//dodamo najbolju jedinku u novu populaciju
        // ovo tu bi moglo van ic myb da ovaj idex krece od 1??
        return index;
    }

    //CROSSING_OVER==============================
    NeuralNet child1 = NeuralNet();
    child1.layers.reserve(Constants::AMOUNT_OF_LAYERS);
    child1.layers.resize(Constants::AMOUNT_OF_LAYERS);
    child1.amountOfNodesInEachLayer = parent1.amountOfNodesInEachLayer;

    NeuralNet child2= NeuralNet();
    child2.layers.reserve(Constants::AMOUNT_OF_LAYERS);
    child2.layers.resize(Constants::AMOUNT_OF_LAYERS);
    child2.amountOfNodesInEachLayer = parent2.amountOfNodesInEachLayer;

    //uzet sve nodeove prvog layera i pola nodeova drugog layera
    //mreza ima vektor layera, layer ima vektor nodeova
    for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
        if(i == 0) {
            child1.layers[i] = parent1.layers[i];
            child2.layers[i] = parent2.layers[i];
        }else{
            int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
            child1.layers[i].nodes.reserve(amountOfNodesInLayer);
            child1.layers[i].nodes.resize(amountOfNodesInLayer);
            child2.layers[i].nodes.reserve(amountOfNodesInLayer);
            child2.layers[i].nodes.resize(amountOfNodesInLayer);
            // child1.layers[i] = parent1.layers[i];
            // child2.layers[i] = parent2.layers[i];

            for(int j = 0; j < amountOfNodesInLayer; j++) {

                if(j < amountOfNodesInLayer/2) {

                    child1.layers[i].nodes[j] = parent1.layers[i].nodes[j];
                    child2.layers[i].nodes[j] = parent2.layers[i].nodes[j];
                }else {
                    child1.layers[i].nodes[j] = parent2.layers[i].nodes[j];
                    child2.layers[i].nodes[j] = parent1.layers[i].nodes[j];
                }
            }
        }
    }


    //MUTATION=====================================
    float r = randomFloat(0,1);

    if(r < Constants::MUTATION_PROBABILITY) {
        //mutating
        //counting nodes
        //cout<<"mutating"<<endl;
        int totalNumberOfNodes = 0;
        for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
            int amountOfNodesInLayer = parent1.amountOfNodesInEachLayer[i];
            for(int j = 0; j < amountOfNodesInLayer; j++) {
                totalNumberOfNodes++;
            }
        }//dobro izbroji

        //umjesto ovog moze dobit dva random indexa: index layera i index nodea u tom layeru i onda po tome dohvatit i mutirat
        //============================================================================
        int currentNodeIndex = 0;
        int mutatingNodeIndex1 = randomInt(0, totalNumberOfNodes);
        int mutatingNodeIndex2 = randomInt(0, totalNumberOfNodes);

        for(int i = 0; i <Constants::AMOUNT_OF_LAYERS; i++) {
            int amountOfNodesInLayer = child1.layers[i].nodes.size();
            int amountOfWeights = this->neuralNetList[index].amountOfNodesInEachLayer[i-1];

            for(int j = 0; j < amountOfNodesInLayer; j++) {
                if(currentNodeIndex == mutatingNodeIndex1) {
                    //mutate this node
                    float value = child1.layers[i].nodes[j].value;
                    child1.layers[i].nodes[j] = Node(amountOfWeights);//TU!!!!!!!!!!!
                    child1.layers[i].nodes[j].value = value;
                }
                if(currentNodeIndex == mutatingNodeIndex2) {
                    //mutate this node
                    float value = child2.layers[i].nodes[j].value;
                    child2.layers[i].nodes[j] = Node(amountOfWeights);
                    child2.layers[i].nodes[j].value = value;
                }
                currentNodeIndex++;
            }
        }
        //=============================================================================
        //dva random indexa: index layera i index nodea u tom layeru i onda po tome dohvatit i mutirat
        // int randomLayerIndex1 = randomInt(1, child1.layers.size() - 1);
        // int randomNodeIndex1 = randomInt(0, child1.layers[randomLayerIndex1-1].nodes.size());
        // int amountNodesByLayer1  = child1.layers[randomLayerIndex1 - 1].nodes.size() - 1;
        // child1.layers[randomLayerIndex1].nodes[randomNodeIndex1] = Node(amountNodesByLayer1);
        //
        // int randomLayerIndex2 = randomInt(1, child2.layers.size() - 1);
        // int randomNodeIndex2 = randomInt(0, child2.layers[randomLayerIndex2-1].nodes.size());
        // int amountNodesByLayer2  = child2.layers[randomLayerIndex2 - 1].nodes.size() - 1;
        // child2.layers[randomLayerIndex2].nodes[randomNodeIndex2] = Node(amountNodesByLayer2);
        //DRUGI NACIN

    }else{//child1 u drugom krigu pravljenja djece nema dobar weight.size na kraju
        //not mutating
        //cout <<"not mutating"<< endl;
    }

    NewPop.neuralNetList[index] = child1;
    index++;

    if(index != Constants::POPULATION_SIZE) {
        NewPop.neuralNetList[index] = child2;
    }
    //cout << "exiting CO & Mutation\n";
    return index;
}
