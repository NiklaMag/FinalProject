//
// Created by <3 on 01.05.2025..
//
#include <iostream>
#include <vector>
#ifndef FILEREADER_H
#define FILEREADER_H

using namespace std;

class FileReader {
public:
    vector<vector<float>> inputs;
    int crossingOverIndex;// 0 -> first CO // 1 -> second CO
    int mutatingIndex;// 0 -> first Mut // 1 -> second Mut
    int randomCrossingOversMutations;// if 0 then manual, if 1 then random
    int blackBox;// 0 -> yes // 1 -> no
    int functionIndex; // 0-6 this is the function for regression
    vector<float> expectedOutputs;//outputs that are expected when theres no function for regression

    FileReader();
    ~FileReader();
    void readInputFile(string pathToInputFile, int blackbox);
    void readSetupFile(string pathToSetupFile);
    vector<string> split(string oldString, char separator);
};



#endif //FILEREADER_H
