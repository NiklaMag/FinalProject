//
// Created by <3 on 01.05.2025..
//
//TODO

#include "FileReader.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;
/*
    input file format:
        i j         ===> input size, i broj redova j broj stupaca
        x x x x x x\n    ===> inputs
        x x x x x x\n
        x x x x x x\n
        x x x x x x\n


    setup file format:
        0/1 0/1 0/1  0/1 ===> random or not, CO index, mut index, functionForRegressionCheck

*/


void FileReader::readInputFile(string pathToInputFile, int blackbox) {//0 yes   1 no

    //prvih n - 1 elemenata u redu su inputovi,
    //zadnji element je ocekivani output za taj input skup
    ifstream myInputFile;
    myInputFile.open(pathToInputFile);

    string line;
    int lineCounter = -1;
    vector<string> segments;
    int numberOfRows;
    int numberOfCollumns;

    if (!myInputFile) {
        cerr << "Unable to open input file";
        exit(1);
    }

    if (myInputFile.is_open()) {
        while (getline(myInputFile, line)) {//cita red po red
            segments = split(line, ' ');

            if(lineCounter == -1) {
                numberOfRows = stoi(segments[0]);
                numberOfCollumns = stoi(segments[1]);

                this->inputs.resize(numberOfRows);
                this->expectedOutputs.resize(numberOfRows);

            }else if(lineCounter > -1 && lineCounter < numberOfRows){

                int lastInputElementIndex;

                if(blackbox == 0) {
                    lastInputElementIndex = numberOfCollumns;
                }else if(blackbox == 1) {
                    lastInputElementIndex = numberOfCollumns - 1;
                    this->expectedOutputs[lineCounter] = stof(segments[lastInputElementIndex]);
                }

                this->inputs[lineCounter].resize(lastInputElementIndex);

                for(int j = 0; j < lastInputElementIndex; j++) {
                    //ide kroz elemnte u redu
                    this->inputs[lineCounter][j] = stof(segments[j]);//inputovi
                }
            }
            lineCounter++;
        }
        myInputFile.close();
    }

}


void FileReader::readSetupFile(string pathToSetupfile) {

    ifstream mySetupFile;

    mySetupFile.open(pathToSetupfile);

    if (!mySetupFile) {
        cerr << "Unable to open setup file";
        exit(1);
    }

    string line;
    vector<string> segments;

    if (mySetupFile.is_open()) {
        while (getline(mySetupFile, line)) {
            segments = split(line, ' ');
            if(segments.size() == 5) {
                this->randomCrossingOversMutations = stoi(segments[0]);
                this->crossingOverIndex = stoi(segments[1]);
                this->mutatingIndex = stoi(segments[2]);
                this->blackBox = stoi(segments[3]);
                this->functionIndex = stoi(segments[4]);
            }else {
                cout <<"reading setup went wrong\n";
            }
        }
        mySetupFile.close();
    }

}












//
// this->randomCrossingOversMutations = stoi(segments[0]);
// this->crossingOverIndex = stoi(segments[1]);
// this->mutatingIndex = stoi(segments[2]);

vector<string> FileReader::split(string oldString, char separator) {
    // , vector<string> newStrings
    vector<string> newStrings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= oldString.size(); i++) {
        // If we reached the end of the word or the end of the input.
        if (oldString[i] == separator || i == oldString.size()) {
            endIndex = i;
            string temp;
            temp.append(oldString, startIndex, endIndex - startIndex);
            newStrings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return newStrings;
}






FileReader::~FileReader() {

}
FileReader::FileReader() {

}
