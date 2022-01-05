#include <random>
#include <ctime>
#include <iostream>
#include "SimulatedAnnealing.hpp"

using namespace std;

SimulatedAnnealing::SimulatedAnnealing() = default;

SimulatedAnnealing::~SimulatedAnnealing() = default;

void SimulatedAnnealing::solve(const Graph &graph, int time, double rate) {
    matrix = graph.matrix;
    size = graph.number_of_vertices;
    timeBound = time;
    coolingRate = rate;
    temperatureBuffer = calculateTemperature();
    vector<int> best;
    vector<int> permutation = random_permutation(size);
    vector<int> next(permutation);
    std::clock_t start;
    int firstToSwap;
    int secondToSwap;
    double temperature = temperatureBuffer;
    int result = 1 << 30;
    double foundTime = 0;
    start = std::clock();

    while (true) {
        while (temperature >= 0.1) {
            int steps = 3 * size;

            next = permutation;

            int nextCost;


            for (int i = steps; i > 0; i--) {
                do {
                    firstToSwap = rand() % size;
                    secondToSwap = rand() % size;
                } while (firstToSwap == secondToSwap);

                std::swap(next[firstToSwap], next[secondToSwap]);

                nextCost = calculatePath(next);

                int difference = result - nextCost;

                if (difference > 0) {
                    result = nextCost;
                    best = next;
                    foundTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
                }
                double p  = getProbability(difference, temperature);
                double zxu = ((double) rand() / RAND_MAX) + 1;
                if (difference > 0 ||
                    (difference < 0 && p > zxu)) {
                    permutation = next;
                    break;
                } else {
                    std::swap(next[firstToSwap], next[secondToSwap]);
                }

                time = (std::clock() - start) / (double) CLOCKS_PER_SEC;

                if (time >= timeBound) {
                    cout << "Droga: ";
                    for (int d = 0; d < size; d++) {
                        cout << best[d] << " ";
                    }

                    cout << "\nKoszt: " << result << endl;
                    cout << "Znaleziono po: " << foundTime << " s " << endl;
                    cout << "Temperatura koncowa: " << temperature << endl;
                    cout << "Procent błedu: " << (((double)(result - 2755)) / 2755.0) << endl;
                    cout << endl;
                    return;
                }
            }
            temperature *= coolingRate;
        }

        temperature = temperatureBuffer;
        permutation = random_permutation(size);

    }

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
    vector<int> origin;

    int firstToSwap;
    int secondToSwap;
    int delta;
    int buffer = 0;

    for (int i = 0; i < 10000; i++) {
        do {
            firstToSwap = rand() % size;
            secondToSwap = rand() % size;
        } while (firstToSwap == secondToSwap);

        origin = random_permutation(size);
        vector<int> neighbour(origin);

        std::swap(neighbour[firstToSwap], neighbour[secondToSwap]);

        delta = fabs(calculatePath(origin) - calculatePath(neighbour));
        buffer += delta;
    }

    buffer /= 10000;

    return (-1 * buffer) / log(0.99);
}

int SimulatedAnnealing::calculatePath(vector<int> path) {
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path[size - 1]][path[0]];

    return cost;
}

double SimulatedAnnealing::getProbability(int diff, double temperature) {
    return exp(diff / temperature);
}
