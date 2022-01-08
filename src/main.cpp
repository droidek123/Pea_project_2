#include <iostream>
#include "Graph/Graph.hpp"
#include "SimulatedAnnealing/SimulatedAnnealing.hpp"
#include "TabuSearch/TabuSearch.hpp"

using namespace std;

void displayMainMenu();

int main() {
    bool quit = false;
    int time = 0;
    double temperatureFactor = 0;
    char option;
    bool diversification = false;
    int neighborhood = 0;
    string name;
    Graph graph;
    do {
        displayMainMenu();
        cin >> option;

        cout << endl;
        switch (option) {
            case '0':
                quit = true;
                break;
            case '1':
                cout << "Plese enter name of the file: ";
                cin >> name;
                graph.loadData(name);
                break;
            case '2':
                do
                {
                    cout << "Podaj czas [s]> ";
                    cin >> time;
                } while (!time);
                break;
            case '3': {
                cout << "Podaj wspolczynnik temperatury";
                cin >> temperatureFactor;
                break;
            }
            case '4':
                if (diversification == 0)cout << "wlaczono dywersyfikacje" << endl;
                else cout << "wylaczono dywesyfikacje" << endl;
                diversification = !diversification;
                break;
            case '5':
                std::cout << "Please choose a neighborhood:\n"
                             "0 - swap\n"
                             "1 - insert\n";
                cin >> neighborhood;
                break;
            case '6': {
                TS tabuSearch;
                std::cout << tabuSearch.tabuSearch(graph,time, diversification, neighborhood);
                break;
            }
            case '7': {
                SimulatedAnnealing simulatedAnnealing;
                simulatedAnnealing.solve(graph, time, temperatureFactor);
                break;
            }
            default:
                cout << "Wrong option chosen.\n";
        }

    } while (!quit);
    return 0;
}

void displayMainMenu(){
    cout << "================== MENU ==================" << endl;
    cout << "\t   1. Load from file" << endl;
    cout << "\t   2. Enter the time" << endl;
    cout << "\t   3. Enter the stop criterion" << endl;
    cout << "\t   4. Diversification on / off" << endl;
    cout << "\t   5. Choice of neighborhood" << endl;
    cout << "\t   6. Tabu search" << endl;
    cout << "\t   7. Simulated Annealing" << endl;
    cout << "\t   0. Exit" << endl << endl;
    cout << "Chosen option:  ";
}
