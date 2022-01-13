#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "SimulatedAnnealing.hpp"

using namespace std;

SimulatedAnnealing::SimulatedAnnealing() = default;

SimulatedAnnealing::~SimulatedAnnealing() = default;


/**
 * Glowna funkcja otpowiadajaca za wykonywanie się algorytmu
 * @param graph graf z którego pobieramy macierz sąsiedztwa
 * @param time maksymalny czas wykonywania sie w algorytu
 * @param cooling_rate wspolczynnik wyzarzania
 * @param neighborhood rodzaj sasiedztwa 0 - swap, 1 insert
 * @param age mnożnik epoki
 */
void SimulatedAnnealing::solve(const Graph &graph, int time, double cooling_rate, int neighborhood, int age) {
    matrix = graph.matrix;
    size = graph.number_of_vertices;
    timeBound = time;
    coolingRate = cooling_rate;
    temperature = calculateTemperature();
    vector<int> best;

    // wlosowanie permutacji początkowej
    vector<int> permutation = random_permutation(size);
    vector<int> next;

    std::clock_t start;
    int first;
    int second;
    int result = calculatePath(permutation);
    int permCost = calculatePath(permutation);
    start = std::clock();
    int nextCost;
    if (age == 0) age = 1000;
    int steps = age * size;

    while (true) {
        for (int i = steps; i > 0; i--) // wykonuje sie przez dlugosc epoki
        {
            next = permutation;
            do {
                first = rand() % size;
                second = rand() % size;
            } while (first == second);

            // tworzymy nowego saisada
            if (neighborhood == 0) swap(next[first], next[second]);
            else next = insert(next, first, second);


            nextCost = calculatePath(next);

            int difference = permCost - nextCost;

            // jesli rozwiazanie jest gorsze to wykonujemy losowanie czy chcemy przyjąc to rozwiazanie
            if (difference <= 0) {
                if (getProbability(difference, temperature) < (double) rand() / RAND_MAX)
                    continue;
            }

            permutation = next;
            permCost = nextCost;

            if (difference > 0) {
                result = nextCost;
            }

            time = (std::clock() - start) / (double) CLOCKS_PER_SEC;
            if (time >= timeBound) {
                cout << result << endl;
                return;
            }
        }

        temperature *= coolingRate; // wyzyrzarzanie
        if (temperature <= 0.1) {
            cout << result << endl;
            return;
        }
    }
}

/**
 *  Funkcja generująca losowe roziazanie
 * @param size rozmiar pliku na którym pracujemy
 * @return zwraca losowe rozwiazanie
 */
vector<int> SimulatedAnnealing::random_permutation(int size) {
    vector<int> temp;
    temp.reserve(size);
    for (int i = 0; i < size; i++) {
        temp.push_back(i);
    }
    shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));
    return temp;
}

/**
 * Funkcja licząca temperaturę początkową
 * @return zwraca temperaturę początkową
 */
double SimulatedAnnealing::calculateTemperature() {
    vector<int> origin;

    int firstToSwap;
    int secondToSwap;
    int delta;
    int buffer = 0;

    for (int i = 0; i < 1000; i++) {
        do {
            firstToSwap = rand() % size;
            secondToSwap = rand() % size;
        } while (firstToSwap == secondToSwap);

        origin = random_permutation(size);
        vector<int> neighbour(origin);

        swap(neighbour[firstToSwap], neighbour[secondToSwap]);

        delta = fabs(calculatePath(origin) - calculatePath(neighbour));
        buffer += delta;

    }
    buffer /= 10000;
    return (-1 * buffer) / log(0.99);
}

/**
 *  Oblicza koszt sciezki
 * @param path sciezka ktorej koszt chcemy obliczyc
 * @return zwraca koszt sciezki
 */
int SimulatedAnnealing::calculatePath(vector<int> path) {
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path[size - 1]][path[0]];

    return cost;
}

/**
 * Funkcjia akceptacji
 * @param diff roznica pomiedzy rozwiazaniem a jego sasiadem
 * @param temperature temperatura
 * @return
 */
double SimulatedAnnealing::getProbability(int diff, double temperature) {
    return exp(diff / temperature);
}

/**
 * implementacja sasiedztwa typu insert
 * @param permutation rozwiazenie na ktorym generujemy sasiedztwo
 * @param first
 * @param second
 * @return zwraca nowego sasiada
 */
vector<int> SimulatedAnnealing::insert(vector<int> &permutation, int first, int second) {
    if (second < first) {
        int tmp = permutation[first];
        for (int i = first; i > second; i--) {
            permutation[i] = permutation[i - 1];
        }
        permutation[second] = tmp;
        return permutation;
    } else {
        int tmp = permutation[first];
        for (int i = first; i < second; i++) {
            permutation[i] = permutation[i + 1];
        }
        permutation[second] = tmp;
        return permutation;
    }

}
