#pragma once

#ifndef PEA_PROJECT_2_TABUSEARCH_HPP
#define PEA_PROJECT_2_TABUSEARCH_HPP

#include "../Graph/Graph.hpp"
#include <vector>

struct TabuElement {
    int first_city;
    int second_city;
    int life_time;
};

class TS {
public:
    std::string tabuSearch(const Graph& graph, int timeForSearch, bool diversification, int neighborhood);
private:
    vector<vector<int>> matrix;
    vector<int> current_permutation;
    vector<int> next_permutation;
    int number_of_vertexes = 0;
    bool diversification;
    double stopCriterion ; // time in seconds
    int currentNeighbourhood ;
    std::vector<TabuElement> tabuList;

    int countPath(const vector<int> &path);
    bool isInTabu(int i, int j);

    void insert(int left, int right);
    static vector<int> randomPermutation(int size);
};


#endif //PEA_PROJECT_2_TABUSEARCH_HPP
