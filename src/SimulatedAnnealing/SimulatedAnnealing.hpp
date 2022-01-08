#pragma once

#ifndef PEA_PROJECT_2_SIMULATEDANNEALING_HPP
#define PEA_PROJECT_2_SIMULATEDANNEALING_HPP

#include <vector>
#include "../Graph/Graph.hpp"

class SimulatedAnnealing {
public:
    [[maybe_unused]] std::vector<int> solution;
    double temperature = 0;
    double coolingRate = 0;
    double timeBound = 0;
    vector<vector<int>> matrix;
    int size{};

    SimulatedAnnealing();
    ~SimulatedAnnealing();

    void solve(const Graph &graph, int time, double rate);
    static vector<int> random_permutation(int size);
    double calculateTemperature();
    int calculatePath(vector <int> path);
    static double getProbability(int diff, double temperature);
};


#endif //PEA_PROJECT_2_SIMULATEDANNEALING_HPP
