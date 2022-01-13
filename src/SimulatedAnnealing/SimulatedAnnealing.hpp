#pragma once

#ifndef PEA_PROJECT_2_SIMULATEDANNEALING_HPP
#define PEA_PROJECT_2_SIMULATEDANNEALING_HPP

#include <vector>
#include "../Graph/Graph.hpp"

class SimulatedAnnealing {
public:
    double temperature = 0;
    double coolingRate = 0;
    double timeBound = 0;
    vector<vector<int>> matrix;
    int size{};

    SimulatedAnnealing();
    ~SimulatedAnnealing();

    void solve(const Graph &graph, int time, double cooling_rate, int neighborhood, int age);
    static vector<int> random_permutation(int size);
    double calculateTemperature();
    int calculatePath(vector <int> path);
    static double getProbability(int diff, double temperature);
    static vector<int> insert(vector<int> &permutation, int first, int second);
};


#endif //PEA_PROJECT_2_SIMULATEDANNEALING_HPP
