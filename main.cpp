#include <iostream>
#include "graph.hh"
#include "graph_matrix.hh"
#include "algorytm.hh"
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{

    // Graph* graph =   new Graph;
    // graph->addEdge(0,1,4);
    // graph->addEdge(1,2,2);
    // graph->addEdge(0,2,6);
    // graph->addEdge(3,2,9);
    // graph->addEdge(1,3,5);
    // graph->addEdge(3,4,1);
    // graph->addEdge(4,2,7);
    // graph->addEdge(2,5,8);
    // graph->ShowNeighbours();
    // Kruskal(graph,8,6);
    // cout << endl;
    // Prim(graph);
    int random1, random2, random3, node1, node2 = 0;
    int GraphNodesNumber[] = {10, 50, 100, 500, 1000};
    float GraphDensity[] = {0.25, 0.5, 0.75};
    int EgdeNumber;
    double czas = 0.0;
    std::set<std::pair<int, int> > dostepnePary;
    Graph *graphPointer;
    // GraphMatrix* graphPointer;
    for (int z = 0; z < 5; z++)
    {
        for (int g = 0; g < 3; g++)
        {
            czas = 0;
            graphPointer = new Graph;
            // graphPointer = new GraphMatrix(GraphNodesNumber[z]);
            EgdeNumber = (GraphDensity[g] * (GraphNodesNumber[z] * GraphNodesNumber[z] - GraphNodesNumber[z])) / 2;
            // for (int g = 0; g < GraphNodesNumber[z]; g++)
            // {
            //     graphPointer->addNode(g);
            // }
            // for (int g = 0; g < GraphNodesNumber[z]; g++)
            // {
            //     for (int h = g + 1; h < GraphNodesNumber[z]; h++)
            //     {
            //         dostepnePary.insert(std::make_pair(g, h));
            //     }
            // }

            // for (int x = 0; x < EgdeNumber; x++)
            // {
            //                 auto startt_time = std::chrono::high_resolution_clock::now();
            //     // Sprawdź, czy są dostępne jeszcze jakieś pary wierzchołków
            //     if (dostepnePary.empty())
            //     {
            //         break;
            //     }

            //     // Wybierz losową parę z dostępnych par
            //     auto it = dostepnePary.begin();
            //     std::advance(it, rand() % dostepnePary.size());
            //     auto randomPair = *it;

            //     // Usuń wybraną parę z dostępnych par
            //     dostepnePary.erase(it);

            //     // Dodaj krawędź do grafu
            //     random1 = randomPair.first;
            //     random2 = randomPair.second;
            //     random3 = rand() % 10001;
            //                 auto endd_time = std::chrono::high_resolution_clock::now();
            // auto durationn = std::chrono::duration_cast<std::chrono::milliseconds>(endd_time - startt_time);
            // cout << durationn.count() << endl;
            //     graphPointer->addEdge(random1, random2, random3);
            // }

            // dostepnePary.clear();
            for (int x = 0; x < EgdeNumber; x++)
            {
                random1 = rand() % (GraphNodesNumber[z] + 1);
                random2 = rand() % (GraphNodesNumber[z] + 1);
                random3 = rand() % 101;
                while (random2 == random1)
                {
                    random2 = rand() % (GraphNodesNumber[z] + 1);
                }
                graphPointer->addEdge(random1, random2, random3);
            }
            auto start_time = std::chrono::high_resolution_clock::now();
            Kruskal(graphPointer, EgdeNumber, GraphNodesNumber[z]);
            //Prim(graphPointer);
            delete[] graphPointer;
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            czas = duration.count();
            cout << "Gestosc: " << GraphDensity[g] * 100 << "%, "
                 << " Ilosc wierzcholkow: " << GraphNodesNumber[z] << ", CZAS: " << czas << "ms" << endl;
        }
    }
}
