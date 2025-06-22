#include <iostream>
#include "Population.h"
#include "Constants.h"
#include "FileReader.h"
//PAZI
//6 FUNCTIONS FOR REGRESSION:
//  index 0 : arbitrary sized vector, domain [-50, 50]
//  index 1 : x, domain [0, 20]
//  index 2 : x y, domain [-10,10]
//  index 3 : x y, domain [-10,10]
//  index 4 : x y, domain [-10,10]
//  index 5 : x y, domain [-10,10]
/*

*/
int main() {
    for(int z = 0; z < Constants::NUMBER_OF_RUNS; z++){

        cout << "XXXXXX+++++++RUN: "<<z<<"+++++++XXXXXXX"<<endl;;
        Population population1 = Population();
        unsigned int seed = static_cast<unsigned int>(time(NULL));
        // unsigned int seed = 1749525174; // 1749525174
        srand(seed);// 1749525174
        NeuralNet bestNet;
        cout << "seed  " << seed <<endl;

        vector<string> pathToFiles = { "/Users/nikson/Documents/GitHub/FinalProject/inputs/data_file_2.txt"

        };
        vector<string> pathToSetupFile = {"/Users/nikson/Documents/GitHub/FinalProject/setup/runSetup_CO0_MUT0",
            "/Users/nikson/Documents/GitHub/FinalProject/setup/runSetup_CO0_MUT1",
             "/Users/nikson/Documents/GitHub/FinalProject/setup/runSetup_CO1_MUT0",
             "/Users/nikson/Documents/GitHub/FinalProject/setup/runSetup_CO1_MUT1",
             "/Users/nikson/Documents/GitHub/FinalProject/setup/runSetup_COR_MUTR"

        };

        for(int x = 0; x < pathToSetupFile.size(); x++) {
            // cout << "NEW SETUP FILE"<<endl;
            string pathToFile = pathToFiles[0];

            FileReader fileReader = FileReader();


            fileReader.readSetupFile(pathToSetupFile[x]);

            // cout << "NEW FILE"<<endl;
            fileReader.readInputFile(pathToFile, fileReader.blackBox);
            // cout << "NEW FILE"<<endl;
            //28514.9
            //13234.7       {(int)inputs[0].size(),2,4,1}; 00002,
            //16817.3       {(int)inputs[0].size(),4,10,2 ,1};00002,
            //13035.6       {(int)inputs[0].size(),4,10,3 ,2,1};
            //11316.5       {(int)inputs[0].size(),4,10, 10,2,1};
            //21074.4       {(int)inputs[0].size(),4,10,20,15, 10,2,1};
            //13023.3       {(int)inputs[0].size(),5,15,20,35, 10,2,1};
            //15239.6       {(int)inputs[0].size(),50,30,20,1};

            vector<vector<float>> inputs = fileReader.inputs;
            vector<float> expectedOutputs = fileReader.expectedOutputs;

            vector<int> amountOfNodesInEachLayer = {(int)inputs[0].size(),4,10,10,2,1};//broj nodova u prvom layeru mora bit isti kao broj stupaca u unputovima

            int crossingOverIndex = fileReader.crossingOverIndex;
            int mutationIndex = fileReader.mutatingIndex;
            int randomCrossingOversMutations = fileReader.randomCrossingOversMutations;
            int functionIndex = fileReader.functionIndex; //0-6 PAZI STA TREBA KOME

            for (int i = 0; i < Constants::NUMBER_OF_GENERATIONS; i++) {
                int newPopulationFullness;

                if(i == 0){
                    //punjenje populacije
                    //filling and evaluating initial population ==============================
                    for (int j = 0; j < Constants::POPULATION_SIZE; j++) {
                        // cout << "filling population: "<<endl;
                        NeuralNet neuralNet(amountOfNodesInEachLayer);//not the best

                        population1.neuralNetList[j] = neuralNet;
                        // cout << j <<endl;
                    }
                }





                for (int j = 0; j < Constants::POPULATION_SIZE; j++) {
                    //RACUNANJE FITNESA ZA SVAKI ELEMENT U POPULACIJI
                    // cout << "getting fitness for entity: ";
                    population1.neuralNetList[j].fitness = population1.neuralNetList[j].getFitness(inputs, functionIndex, fileReader);
                    // cout << j << endl;
                }
                // cout << "done getting initial fitness"<<endl;

                population1.neuralNetFitnessSort();
                NeuralNet bestNN = population1.getBestNeuralNet();
                // cout << "sorting done" <<endl;
                Population population2 = Population();

                //izrada i punjenje nove populacije
                newPopulationFullness = 0;

                while (newPopulationFullness < Constants::POPULATION_SIZE && population1.neuralNetList.size() == Constants::POPULATION_SIZE){
                    population1.chooseParents();
                    // cout << "parents chosen" <<endl;
                    newPopulationFullness = population1.crossingOverAndMutation(population2, newPopulationFullness, crossingOverIndex, mutationIndex, randomCrossingOversMutations);
                    // cout << "CO and mutation done"<<endl;
                    newPopulationFullness++;
                }


                population1.neuralNetList.clear();
                copy(population2.neuralNetList.begin(), population2.neuralNetList.end(), back_inserter(population1.neuralNetList));

                if(i % 100 == 0) {
                    cout << "generation "<< i << ": ";
                    cout << "fitness = "<<population1.getBestNeuralNet().fitness << "\n";
                }
                // cout << "generation "<< i << ": ";
                // // cout << "fitness = "<<population1.getBestNeuralNet().fitness << "\n";
                // cout << "fitness = "<< bestNN.fitness << "\n";
            }

            // string fileName = fileReader.split(pathToFile, '/')[fileReader.split(pathToFile, '/').size()-1];
            bestNet = population1.getBestNeuralNet();

            if(randomCrossingOversMutations == 0) {
                cout << "crossingOverIndex: " << crossingOverIndex <<endl;
                cout << "mutationIndex: " << mutationIndex <<endl;
            }else {
                cout << "random CO and MUT"<<endl;
            }
            cout << "functionIndex: " << functionIndex <<endl;
            cout << "final fitness: " << bestNet.fitness <<endl<<endl;
        }

        cout<<"program done";

    }
}