#include <iostream>
#include "Population.h"
#include "Constants.h"


int main() {

    Population population1 = Population();
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    srand(seed);
    //cout << "seed  " << seed <<endl;
    //srand(time(NULL));  //1744484476

    vector<vector<float>> inputs = {
        {25, -14, 3, -8, 19, 44},
        {-22, 6, -17, 28, -4, 0},
        {-39, 12, 9, -24, 18, -10},
        {33, -5, -26, 20, -1, 16},
        {45, -33, 8, -2, 22, -11},
        {0, -27, 17, 13, -6, -18},
        {-50, 11, 24, -3, 10, -15},
        {7, -12, 5, -19, 41, -9},
        {-30, 2, 36, -7, 32, -23}


        // {5, -12, 33, -1, 19, -4, 40, -30},
        // {0, 23, -7, 26, -17, 15, -45, 3},
        // {14, -9, 8, -50, 27, -20, 2, -6},
        // {-39, 24, 1, -10, 35, -22, -11, 41},
        // {17, -18, 44, -33, 6, -25, 0, 7},
        // {-29, 3, 12, -26, 30, -8, -1, 22},
        // {16, -24, 13, -2, 11, -14, -5, 34},
        // {-46, 9, -31, 18, -3, 36, -6, 0},
        // {31, -19, -40, 20, -23, 45, -32, 4}

        // {12, -35, 44, 8},
        // {-7, 19, -22, 50},
        // {0, -13, 32, -4},
        // {-45, 28, -16, 9},
        // {36, -1, 14, -30},
        // {-17, 3, -48, 20},
        // {27, -6, 5, -23},
        // {39, -50, 7, 18},
        // {-2, 11, -10, -33}

        // {12, -7, 25, -33, 0, 18, 45},
        // {-23, 1, -15, 39, 7, -8, 3},
        // {44, -50, 36, 22, -17, 10, -9},
        // {5, 13, -48, -2, 8, -26, 19},
        // {-1, -12, 20, -45, 11, 27, 33},
        // {7, 41, -3, -14, -50, 0, 26},
        // {32, -22, 6, 15, -8, 2, -19},
        // {-40, 9, 13, 17, -4, -28, 38},
        // {3, -3, 30, -10, 24, -12, -33}

        // {1,1,1},
        // {1,2,2},
        // {1,3,3},
        // {1,4,4},
        // {5,1,5},
        // {1,6,6},
        // {7,1,7},
        // {8,1,8},
        // {9,1,9},
        // {0,1,0}
    };

    vector<int> amountOfNodesInEachLayer = {(int)inputs[0].size(),2,3,1};//broj nodova u prvom layeru mora bit isti kao broj stupaca u unputovima

    int crossingOverIndex = 1;
    int mutationIndex = 1;
    int randomCrossingOversMutations = 1;

    cout << "do you want random CrossingOvers and Mutations(0 = NO, 1 = YES)?"<<endl;
    cin >> randomCrossingOversMutations;

    if(randomCrossingOversMutations == 0) {

        cout << "choose crossingOver(1,2): " <<endl;
        cin >> crossingOverIndex;

        cout << "choose mutation(1,2):" << endl;
        cin >> mutationIndex;
    }


     for (int i = 0; i < Constants::NUMBER_OF_GENERATIONS; i++) {
         int newPopulationFullness;

         cout << "generation "<< i << ": ";
         if(i == 0){
             //punjenje populacije
             //filling and evaluating initial population ==============================
             for (int j = 0; j < Constants::POPULATION_SIZE; j++) {
                 //cout << "b"<<endl;
                 NeuralNet neuralNet(amountOfNodesInEachLayer);//not the best
                 //neuralNet.inputs = inputs;
                 neuralNet.amountOfNodesInEachLayer = amountOfNodesInEachLayer;
                 population1.neuralNetList[j] = neuralNet;
             }
         }


         for (int j = 0; j < Constants::POPULATION_SIZE; j++) {
             //RACUNANJE FITNESA ZA SVAKI ELEMENT U POPULACIJI
             population1.neuralNetList[j].fitness = population1.neuralNetList[j].getFitness(inputs);
         }

         population1.neuralNetFitnessSort();
         Population population2 = Population();

         //izrada i punjenje nove populacije
         newPopulationFullness = 0;

         while (newPopulationFullness < Constants::POPULATION_SIZE && population1.neuralNetList.size() == Constants::POPULATION_SIZE){

             population1.chooseParents();
             newPopulationFullness = population1.crossingOverAndMutation(population2, newPopulationFullness, crossingOverIndex, mutationIndex, randomCrossingOversMutations);//tu je neki zez
             newPopulationFullness++;
         }


         population1.neuralNetList.clear();
         copy(population2.neuralNetList.begin(), population2.neuralNetList.end(), back_inserter(population1.neuralNetList));
         cout << "fitness = "<<population1.getBestNeuralNet().fitness << "\n";
         NeuralNet bestNN = population1.getBestNeuralNet();

     }

    //isprintat kraj i fitness
    //smislit neku funkciju i to regressat
cout<<"program done\nfinal fitness: "<< population1.getBestNeuralNet().fitness;

}
