//
// Created by Andrzej on 08.12.2021.
//

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
    return vector<int>();
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
