#include <iostream>
#include "Graph/Graph.hpp"
#include "TabuSearch/TabuSearch.hpp"

using namespace std;

void displayMainMenu();

int main() {
    bool quit = false;
    int time = 0;
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
                    std::cout << "Podaj czas [s]> ";
                    cin >> time;
                } while (!time);
                break;
            case '3':
                diversification = !diversification;
                break;
            case '4':
                std::cout << "Please choose a neighborhood:\n"
                             "0 - swap\n"
                             "1 - insert\n";
                cin >> neighborhood;
                break;
            case '5': {
                TabuSearch tabuSearch;
                tabuSearch.solve(graph, time, diversification, neighborhood);
                break;
            }
            case '9':
                int x;
                cout << "Enter amount of nodes: ";
                cin >> x;
                graph.generateGraph(x);
                break;
            case 'a':
                if (graph.number_of_vertices <= 1) {
                    cout << ("No adjacency matrix was created.\n");
                    break;
                }
                graph.display();
                break;
            default:
                cout << "Wrong option chosen.\n";
        }

    } while (!quit);
    return 0;
}

void displayMainMenu(){
    cout << "================== MAIN MENU ==================" << endl;
    cout << "\t   1. Load from file" << endl;
    cout << "\t   2. Enter the stop criterion" << endl;
    cout << "\t   3. Diversification on / off" << endl;
    cout << "\t   4. Choice of neighborhood" << endl;
    cout << "\t   5. Tabu search" << endl;
    cout << "\t   9. Generate adjacency matrix" << endl;
    cout << "\t   a. Display adjacency matrix" << endl;
    cout << "\t   b. Tests" << endl;
    cout << "\t   0. Exit" << endl << endl;
    cout << "Chosen option: ";
}
