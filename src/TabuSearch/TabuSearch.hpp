#pragma once

#ifndef PEA_PROJECT_2_TABUSEARCH_HPP
#define PEA_PROJECT_2_TABUSEARCH_HPP

#include "../Graph/Graph.hpp"
#include <vector>

struct TabuElement {
    int i;
    int j;
    int lifetime;
};

class TS {
public:
    std::string tabuSearch(const Graph& graph, int timeForSearch, bool diversification, int neighborhood);
private:
    vector<vector<int>> matrix;
    int number_of_vertexes = 0;
    bool diversification = false; //diversification is turned on, 0 - no, 1 - yes
    double stopCriterion = 10; // time in seconds
    int currentNeighbourhood = 0;
    std::vector<TabuElement> tabuList;
    int start = 0;

    TabuElement newSolution(int *result_permutation);
    int countPath(int *permutation);
    bool inTabuList(int i, int j);

    void swap(int *permutation, int left, int right);
    void insert(int *permutation, int left, int right);
    int * randomPermutation(int size);
};


#endif //PEA_PROJECT_2_TABUSEARCH_HPP
