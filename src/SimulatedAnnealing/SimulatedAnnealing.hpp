//
// Created by Andrzej on 08.12.2021.
//
#pragma once

#ifndef PEA_PROJECT_2_SIMULATEDANNEALING_HPP
#define PEA_PROJECT_2_SIMULATEDANNEALING_HPP

#include <vector>
#include "../Graph/Graph.hpp"

class SimulatedAnnealing {
public:
    std::vector<int> solution;
    double temperatureBuffer = 0;
    double coolingRate = 0;
    double timeBound = 0;
    vector<vector<int>> matrix;
    int size;

    SimulatedAnnealing(Graph graph, int time, double rate);
    ~SimulatedAnnealing();

    void solve();
    vector<int> random_permutation(int size);
    double calculateTemperature();
    int calculatePath(vector <int> path);
    double getProbability(int diff, double temperature);
};


#endif //PEA_PROJECT_2_SIMULATEDANNEALING_HPP
