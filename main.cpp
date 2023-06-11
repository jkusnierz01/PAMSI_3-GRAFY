#include <iostream>
#include "graph.hh"
#include "graph_matrix.hh"
#include "algorytm.hh"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    int GraphNodesNumber[] = {10, 50, 100, 500, 1000};
    float GraphDensity[] = {0.25, 0.5, 0.75};
    int EgdeNumber;
    double time = 0.0;
    Graph *graphPointer;
    for (int z = 0; z < 5; z++)
    {
        for (int g = 0; g < 3; g++)
        {
            auto start_time = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 100; i++)
            {
                graphPointer = new Graph;
                EgdeNumber = (GraphDensity[g] * (GraphNodesNumber[z] * GraphNodesNumber[z] - GraphNodesNumber[z])) / 2;
                cout << EgdeNumber << endl;
                for (int x = 0; x < EgdeNumber; x++)
                {
                    graphPointer->addEdge(x, x + 1, x+1);
                }
                Kruskal(graphPointer,EgdeNumber);
                delete[] graphPointer;
                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
                time =+duration.count();
            }
            cout << "Gestosc nr: " << g +1 <<" Ilosc wierzcholkow: "<< GraphNodesNumber[z] << " , CZAS: "<< time/100 << endl;
        }
    }
}
