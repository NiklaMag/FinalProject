cmake_minimum_required(VERSION 3.28)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0 -g")


add_executable(FinalProject main.cpp
        NeuralNet.h
        NeuralNet.cpp
        Layer.h
        Layer.cpp
        Node.h
        Node.cpp
        Constants.h
        Population.h
        Population.cpp
        FileReader.h
        FileReader.cpp
)