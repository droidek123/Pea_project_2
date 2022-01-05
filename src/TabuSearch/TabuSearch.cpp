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

std::string TS::tabuSearch(const Graph& graph, int timeForSearch, bool diversification, int neighborhood) {
    matrix = graph.matrix;
    number_of_vertexes = graph.number_of_vertices;
    stopCriterion = timeForSearch;
    tabuList.clear();
    clock_t t;
    double time = 0;
    t = std::clock();
    int *current_permutation = new int[number_of_vertexes]; // stores currently analyzed permutation

    //first permutation - random permutation
    //int length = beginning(current_permutation); // stores the best known length

    for(int i = 0; i < number_of_vertexes;i++)
        current_permutation[i] = i;

//    current_permutation = randomPermutation(number_of_vertexes);
    int length = countPath(current_permutation);

    int *result_permutation = new int[number_of_vertexes]; // stores the best known permutation
    for (int i = 0; i < number_of_vertexes; i++){
        result_permutation[i] = current_permutation[i];
    }

    int numberOfIterationsWithoutChange = number_of_vertexes * 3; // maximum number of iterations without a change - diversification
    while (time  < stopCriterion){
        // new solution - the best from the neighbourhood
//        TabuElement tabuElement = newSolution(current_permutation); // returns swapped i, j

        TabuElement tabuElement{};
        int min = INT32_MAX;
        for (int i = 0; i < number_of_vertexes; i++) {
            current_permutation[i] = result_permutation[i];
        }

        for (int i = 1; i < number_of_vertexes - 1; i++) {
            for (int j = 1; j < number_of_vertexes - 1; j++) {
                if (i != j && !inTabuList(i, j)) {
                    switch(currentNeighbourhood) {  // choose neighbourhood
                        case 0: swap(current_permutation, i, j); break;
                        case 1: insert(current_permutation, i, j); break;
                    }
                    int tmp = countPath(current_permutation);

                    if (tmp <= min) {
                        tabuElement.i = j; tabuElement.j = i;
                        min = tmp;
                        for (int k = 0; k < number_of_vertexes; k++) {
                            result_permutation[k] = current_permutation[k]; // here is the best permutation in the neighbourhood
                        }
                    }
                    switch(currentNeighbourhood){
                        case 0: swap(current_permutation, i, j); break;
                        case 1: insert(current_permutation, j, i); break;
                    }

                }
            }
        }

        int tmp = countPath(current_permutation); // the length of the found route

        if (tmp < length){ // if the solution is better, change for the new one
            numberOfIterationsWithoutChange = number_of_vertexes * 3;
            length = tmp;
            for (int i = 0; i < number_of_vertexes; i++){
                result_permutation[i] = current_permutation[i];
            }
        }

        //tabu list actualisation: reducing the lifetime (cadence) and removing unnecessary items
        for(auto it = tabuList.begin(); it != tabuList.end(); ++it) {
            it->lifetime--;

            if (it->lifetime == 0){
                tabuList.erase(it);
                --it;
            }
        }

        // add new elements to the tabu list
        if (tabuList.size() < number_of_vertexes * 2 ) { // maximum size of the tabu list
            tabuElement.lifetime = number_of_vertexes * 2;
            tabuList.push_back(tabuElement);
        }


        // diversification: if better after the restart then swap
//        if(diversification && (numberOfIterationsWithoutChange <= 0)){
//            restart(current_permutation);
//            tmp = countPath(current_permutation);
//
//            numberOfIterationsWithoutChange = number_of_vertexes * 3;
//            if (tmp <= length){
//                length = tmp;
//                for (int i = 0; i < number_of_vertexes; i++){
//                    result_permutation[i] = current_permutation[i];
//                }
//            }
//        }
        numberOfIterationsWithoutChange--;
        time = (std::clock() - t) / (double) CLOCKS_PER_SEC;
    }

    std::stringstream ss;
    ss << length << std::endl;

    delete[] current_permutation;
    delete[] result_permutation;
    tabuList.clear();
    return ss.str();
}


// Finds the best solution in the neighbourhood
TabuElement TS::newSolution(int *result_permutation) {
    TabuElement tabuElement{};
    int min = INT32_MAX;
    int *current_permutation = new int[number_of_vertexes]; // current permutation
    for (int i = 0; i < number_of_vertexes; i++) {
        current_permutation[i] = result_permutation[i];
    }

    for (int i = 1; i < number_of_vertexes - 1; i++) {
        for (int j = 1; j < number_of_vertexes - 1; j++) {
            if (i != j && !inTabuList(i, j)) {
                switch(currentNeighbourhood) {  // choose neighbourhood
                    case 0: swap(current_permutation, i, j); break;
                    case 1: insert(current_permutation, i, j); break;
                }
                int tmp = countPath(current_permutation);

                if (tmp <= min) {
                    tabuElement.i = j; tabuElement.j = i;
                    min = tmp;
                    for (int k = 0; k < number_of_vertexes; k++) {
                        result_permutation[k] = current_permutation[k]; // here is the best permutation in the neighbourhood
                    }
                }
                // todo sprzwdzic czy to jest jeszcze potrzebne
//                switch(currentNeighbourhood){
//                    case 0: swap(current_permutation, i, j); break;
//                    case 1: insert(current_permutation, j, i); break;
//                }

            }
        }
    }
    return tabuElement;
}

bool TS::inTabuList(int i, int j) {
    for (auto &it : tabuList) {
        if ((it.i == i && it.j == j)||(it.i == j && it.j == i)) // cases in which we do not swap
            return true;
    }
    return false;
}

int TS::countPath(int *permutation) {
    int length = 0;
    int end;

    for (int i = 0; i < number_of_vertexes -1; i++){
        length += matrix[permutation[i]][permutation[i+1]];
        end = i;
    }
    length += matrix[permutation[number_of_vertexes-1]][0];

    return length;
}



void TS::swap(int *permutation, int left, int right) {
    if (right == left) return;
    int tmp = permutation[left];
    permutation[left] = permutation[right];
    permutation[right] = tmp;
}

void TS::insert(int *permutation, int left, int right) {
    if (right == left) return;
    if (right < left){
        int tmp = permutation[left];
        for (int i = left; i > right; i--){
            permutation[i] = permutation[i-1];
        }
        permutation[right] = tmp;
    }
    else {
        int tmp = permutation[left];
        for (int i = left; i < right; i++){
            permutation[i] = permutation[i+1];
        }
        permutation[right] = tmp;
    }

}
