//
// Created by Andrzej on 08.12.2021.
//

#include <random>
#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(Graph graph, int time, double rate) {
    matrix = graph.matrix;
    size = graph.number_of_vertices;
    timeBound = time;
    coolingRate = rate;
    temperatureBuffer = calculateTemperature();
}

SimulatedAnnealing::~SimulatedAnnealing() = default;

void SimulatedAnnealing::solve() {

}

vector<int> SimulatedAnnealing::random_permutation(int size) {
    vector<int> temp;
    temp.reserve(size);

    for (int i = 0; i < size; i++) {
        temp.push_back(i);
    }

    shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));

    return temp;
}

double SimulatedAnnealing::calculateTemperature() {
    return 0;
}

int SimulatedAnnealing::calculatePath(vector<int> path) {
    return 0;
}

double SimulatedAnnealing::getProbability(int diff, double temperature) {
    return 0;
}
