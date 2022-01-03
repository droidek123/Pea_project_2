//
// Created by Andrzej on 22.11.2021.
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include "TabuSearch.hpp"

using namespace std;

TabuSearch::TabuSearch() = default;

TabuSearch::~TabuSearch() = default;

vector<int> TabuSearch::randomPermutation(int size) {
    vector<int> temp;
    temp.reserve(size);

    for (int i = 0; i < size; i++) {
        temp.push_back(i);
    }

    shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));

    return temp;
}

int TabuSearch::calculatePath(const vector<int> &path) {
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path[number_of_vertexes - 1]][path[0]];

    return cost;
}

void TabuSearch::insert(int first, int second) {
    if (second == first) return;
    if (second < first){
        int tmp = permutation[first];
        for (int i = first; i > second; i--){
            permutation[i] = permutation[i-1];
        }
        permutation[second] = tmp;
    }
    else {
        int tmp = permutation[first];
        for (int i = first; i < second; i++){
            permutation[i] = permutation[i+1];
        }
        permutation[second] = tmp;
    }

}

void TabuSearch::solve(const Graph &graph, int timeForSearch, bool diversification, int neighborhood) {
    this->searchTime = timeForSearch;
    this->matrix = graph.matrix;
    this->number_of_vertexes = graph.number_of_vertices;
    vector<int> best;
    permutation = randomPermutation(number_of_vertexes);
    vector<int> next(permutation);
    int result = 1 << 30;
    int firstToSwap;
    int secondToSwap;
    int nextCost;
    clock_t start;
    double time;


    start = std::clock();

    while (true) {

        this->tabuMatrix.resize(this->number_of_vertexes);

        for (auto &it: this->tabuMatrix) {
            it.resize(this->number_of_vertexes, 0);
        }

        for (int step = 0; step < 15 * this->number_of_vertexes; ++step) {
            firstToSwap = 0;
            secondToSwap = 0;
            nextCost = 1 << 30;

            for (int first = 0; first < this->number_of_vertexes; ++first) {
                for (int second = first + 1; second < this->number_of_vertexes; ++second) {
                    if(neighborhood == 0) std::swap(permutation[first], permutation[second]);
                    else if(neighborhood == 1) insert(first, second);
                    int currentCost = calculatePath(permutation);

                    if (currentCost < result) {
                        result = currentCost;
                        best = permutation;
                    }

                    if (currentCost < nextCost) {
                        if (this->tabuMatrix[second][first] < step) {
                            nextCost = currentCost;
                            next = permutation;

                            firstToSwap = second;
                            secondToSwap = first;
                        }
                    }

                    if(neighborhood == 0)  std::swap(permutation[first], permutation[second]);
                    else if(neighborhood == 1) insert(first, second);

                    time = (std::clock() - start) / (double) CLOCKS_PER_SEC;

                    if (time >= searchTime) {
                        cout << "Droga: ";
                        for (int d = 0; d < this->number_of_vertexes; d++) {
                            cout << best[d] << " ";
                        }

                        cout << "\nKoszt: " << result << endl;
                        return;
                    }

                }
            }
            permutation = next;
            this->tabuMatrix[firstToSwap][secondToSwap] += this->number_of_vertexes;
        }
        if(diversification) {
            permutation.clear();
            permutation = randomPermutation(this->number_of_vertexes);
        }

        for (auto &it: this->tabuMatrix) {
            it.clear();
        }
        this->tabuMatrix.clear();
    }
}
