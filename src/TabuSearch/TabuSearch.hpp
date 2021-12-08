//
// Created by Andrzej on 22.11.2021.
//
#pragma once

#ifndef PEA_PROJECT_2_TABUSEARCH_HPP
#define PEA_PROJECT_2_TABUSEARCH_HPP

#include "../Graph/Graph.hpp"
#include <vector>

class TabuSearch {
public:
    vector<vector<int>> matrix;
    vector<vector<int>> tabuMatrix;
    int number_of_vertexes = 0;
    int searchTime = 0;

    TabuSearch();

    ~TabuSearch();

    static vector<int> randomPermutation(int size);

    int calculatePath(const vector <int>& path);

    void solve(const Graph& graph, int timeForSearch);
};


#endif //PEA_PROJECT_2_TABUSEARCH_HPP
