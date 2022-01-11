//
// Created by Andrzej on 22.11.2021.
//

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <sstream>
#include "TabuSearch.hpp"

using namespace std;

std::string TS::tabuSearch(const Graph& graph, int timeForSearch, bool div, int neighborhood) {
    this->diversification = div;
    this->currentNeighbourhood = neighborhood;
    matrix = graph.matrix;
    number_of_vertexes = graph.number_of_vertices;
    stopCriterion = timeForSearch;
    tabuList.clear();
    clock_t t;
    double time = 0;
    t = std::clock();

    current_permutation = randomPermutation(number_of_vertexes);
    vector<int> result_permutation = current_permutation;
    int length = countPath(current_permutation);

    int numberOfIterationsWithoutChange = number_of_vertexes * 6; // maximum number of iterations without a change - diversification
    while (time  < stopCriterion){

        TabuElement tabuElement{};
        int min = INT32_MAX;
        next_permutation = current_permutation;
        vector<int>nextperm(current_permutation);


        for (int i = 1; i < number_of_vertexes; i++) {
            for (int j = 1; j < number_of_vertexes; j++) {
                if (i != j && !isInTabu(i,j)) {
                    next_permutation = nextperm;
                    switch (currentNeighbourhood) {  // choose neighbourhood
                        case 0:
                            swap(next_permutation[i], next_permutation[j]);
                            break;
                        case 1:
                            insert(i, j);
                            break;
                    }
                    int tmp = countPath(next_permutation);

                    if (tmp <= min) {
                        tabuElement.first_city = j;
                        tabuElement.second_city = i;
                        min = tmp;
                        for (int k = 0; k < number_of_vertexes; k++) {
                            current_permutation[k] = next_permutation[k]; // here is the best permutation in the neighbourhood
                        }
                    }
                }
            }
        }

        //int tmp = countPath(current_permutation); // the length of the found route

        if (min < length){ // if the solution is better, change for the new one
            numberOfIterationsWithoutChange = number_of_vertexes * 6;
            length = min;
            result_permutation = current_permutation;
        }

        //tabu list actualisation: reducing the lifetime (cadence) and removing unnecessary items
        for(auto it = tabuList.begin(); it != tabuList.end(); ++it) {
            it->life_time--;

            if (it->life_time == 0){
                tabuList.erase(it);
                --it;
            }
        }

        // add new elements to the tabu list
        if (tabuList.size() < number_of_vertexes * 2 ) { // maximum size of the tabu list
            tabuElement.life_time = number_of_vertexes * 2;
            tabuList.push_back(tabuElement);
        }


        // diversification: if better after the restart then swap
        if(this->diversification && (numberOfIterationsWithoutChange <= 0)){
            current_permutation = randomPermutation(number_of_vertexes);
            min = countPath(current_permutation);

            numberOfIterationsWithoutChange = number_of_vertexes * 6;
            if (min <= length){
                length = min;
                result_permutation = current_permutation;
            }
        }
        numberOfIterationsWithoutChange--;
        time = (std::clock() - t) / (double) CLOCKS_PER_SEC;
    }

    std::stringstream ss;
    ss << length << std::endl;

    current_permutation.clear();
    result_permutation.clear();
    tabuList.clear();
    return ss.str();
}


bool TS::isInTabu(int i, int j) {
    for (auto & k : tabuList){
        if ((k.first_city == i && k.second_city == j)||(k.second_city == i && k.first_city == j)){
            return true;
        }
    }
    return false;
}

int TS::countPath(const vector<int> &path) {
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path[number_of_vertexes - 1]][path[0]];

    return cost;
}

void TS::insert(int left, int right) {
    if (right == left) return;
    if (right < left){
        int tmp = next_permutation[left];
        for (int i = left; i > right; i--){
            next_permutation[i] = next_permutation[i-1];
        }
        next_permutation[right] = tmp;
    }
    else {
        int tmp = next_permutation[left];
        for (int i = left; i < right; i++){
            next_permutation[i] = next_permutation[i+1];
        }
        next_permutation[right] = tmp;
    }

}

vector<int> TS::randomPermutation(int size)
{
    vector<int> temp;
    temp.reserve(size);
    for (int i = 0; i < size; i++) {
        temp.push_back(i);
    }
    shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));
    return temp;
}
