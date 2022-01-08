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
    temperature = calculateTemperature();
    vector<int> best;

    // wulosowanie permutacji początkowej
    vector<int> permutation = random_permutation(size);
    vector<int> next(permutation);

    std::clock_t start;
    int firstToSwap;
    int secondToSwap;
    int result = INT_MAX;
    double foundTime = 0;
    start = std::clock();
    int nextCost;
    int steps;

        while (true)
        {
            steps =  100*size;
            for (int i = steps; i > 0; i--)
            {
                next = permutation;
                do
                {
                    firstToSwap = rand() % size;
                    secondToSwap = rand() % size;
                } while (firstToSwap == secondToSwap);

                std::swap(next[firstToSwap],next[secondToSwap]);

                nextCost = calculatePath(next);

                int difference = result - nextCost;

                if (difference > 0)
                {
                    result = nextCost;
                    best = next;
                    foundTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                }

                if (difference > 0 || (difference < 0 && getProbability(difference,temperature) > ((double)rand() / RAND_MAX)))
                {
                    permutation = next;
                }

                time = (std::clock() - start) / (double)CLOCKS_PER_SEC;

                if (time >= timeBound || temperature <= 0.1)
                {
                    cout << "Droga: ";
                    for (int d = 0; d < size; d++)
                    {
                        cout << best[d] << " ";
                    }

                    cout << "\nKoszt: " << result << endl;
                    cout << "Znaleziono po: " << foundTime << " s " << endl;
                    cout << "Temperatura koncowa: "<< temperature << endl;
                    cout << endl;
                    return;
                }
            }
            temperature *= coolingRate;
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
    int best = INT_MAX;

    for (int i = 0; i < 10000; i++){
        do {
            firstToSwap = rand() % size;
            secondToSwap = rand() % size;
        } while (firstToSwap == secondToSwap);

        origin = random_permutation(size);
        if (best > calculatePath(origin)){
            best = calculatePath(origin);
        }

    }
    return best;
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
