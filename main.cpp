#include <iostream>
#include "Population.h"
#include "Constants.h"
//jos jedan nacin mutacije i jos jedan corssingover
//uvijek mjenjamo funkciju nodea
//mutacoja:random broj cvorova uzet i u odredemnom postotku se mjeja funkcoje a u svima tezina ali samo malo (gauss)
//co drugacije biraj node

int main() {

    Population population1 = Population();
    //unsigned int seed = static_cast<unsigned int>(time(NULL));
    //srand(1742771394);
    //cout << "seed  " << seed <<endl;
    srand(time(NULL));  //1742771394  1742771419 1742771447

    vector<float> inputs = {1,2,3,4,5,6,7,8,9};

    vector<int> amountOfNodesInEachLayer = {1,2,3,1};

     for (int i = 0; i < Constants::NUMBER_OF_GENERATIONS; i++) {
         int newPopulationFullness;//TU JOS VRTIT INPUTE

         int input = 0;
         //cout << "a"<<endl;

         cout << "generation: "<< i << "\n";
         if(i == 0){
             //punjenje populacije
             //filling and evaluating initial population ==============================
             for (int j = 0; j < Constants::POPULATION_SIZE; j++) {
                 //cout << "b"<<endl;
                 NeuralNet neuralNet(amountOfNodesInEachLayer, inputs);//not the best
                 //neuralNet.inputs = inputs;
                 neuralNet.amountOfNodesInEachLayer = amountOfNodesInEachLayer;
                 population1.neuralNetList[j] = neuralNet;
             }
             //population1.entityFitnessEval();
             //population1.entityFitnessSort();
         }


         for (int j = 0; j < Constants::POPULATION_SIZE; j++) {
             //cout << "c"<<endl;
             //RACUNANJE FITNESA ZA SVAKI ELEMENT U POPULACIJI
             population1.neuralNetList[j].inputs = inputs;
             //cout << "c"<<endl;
             population1.neuralNetList[j].fitness = population1.neuralNetList[j].getFitness();//nsto oko fitness kalkulacije jebe %%%%%%
             //cout << "c2"<<endl;
             //fitness se razjebe na drugoj generaciji
         }
         //cout << "d"<<endl;
         population1.neuralNetFitnessSort();
         //cout << "e"<<endl;
         Population population2 = Population();

         //izrada i punjenje nove populacije
         newPopulationFullness = 0;

         while (newPopulationFullness < Constants::POPULATION_SIZE && population1.neuralNetList.size() == Constants::POPULATION_SIZE){
             //cout << "f"<<endl;
             population1.chooseParents();
             //cout << "g"<<endl;
             //copy(population1.neuralNetList.begin(), population1.neuralNetList.end(), back_inserter(population2.neuralNetList));
                //sketchy^^^^^
             newPopulationFullness = population1.crossingOverAndMutation(population2, newPopulationFullness);//tu je neki zez
             newPopulationFullness++;
             //cout << "h"<<endl;
         }

         population1.neuralNetList.clear();
         //cout << "i"<<endl;
         copy(population2.neuralNetList.begin(), population2.neuralNetList.end(), back_inserter(population1.neuralNetList));
         //cout << "j"<<endl;
         cout << "fitness: "<<population1.getBestNeuralNet().fitness << "\n";
         //cout << "k"<<endl;
         NeuralNet bestNN = population1.getBestNeuralNet();

     }

    //NeuralNet bestNeuralNet = population1.getBestNeuralNet();


    //isprintat kraj i fitness
    //smislit neku funkciju i to regressat
cout<<"program done";

}
