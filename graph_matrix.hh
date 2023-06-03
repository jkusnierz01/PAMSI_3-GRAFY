#ifndef GRAPHMATRIX_HH
#define GRAPHMATRIX_HH
#include <iostream>
#include "linkedlst.hh"
using namespace std;

class GraphMatrix
{
public:
    int **AdjacencyMatrix;
    int NodesNumber;
    int *NodesValuesPointer;
    GraphMatrix(int value)
    {
        NodesNumber = value;
        AdjacencyMatrix = new int *[NodesNumber];
        NodesValuesPointer = new int[NodesNumber];
        for (int x = 0; x < NodesNumber; x++)
        {
            NodesValuesPointer[x] = 0;
            AdjacencyMatrix[x] = new int[NodesNumber];
            for (int j = 0; j < NodesNumber; j++)
            {
                AdjacencyMatrix[x][j] = 0;
            }
        }
    }
    ~GraphMatrix()
    {
        // Usuwanie macierzy sąsiedztwa
        for (int i = 0; i < NodesNumber; i++)
        {
            delete[] AdjacencyMatrix[i];
        }
        delete[] AdjacencyMatrix;
        delete[] NodesValuesPointer;
    }
    void addEdge(int Node1, int Node2)
    {
        int index1;
        int index2;
        // dodajemy wartosci wierzcholkow - numery do tablicy pomocniczej
        // stanowi ona lacznik miedzy wartosciami a indeksami tablicy - w macierz
        // znajdujemy ich indeksy ale w odpowiednich elementach macierzy wstawic 1
        for (int x = 0; x < NodesNumber; x++) 
        {
            if(NodesValuesPointer[x] == Node1)
            {
                index1 = x;
                break;
            }
            if (NodesValuesPointer[x] == 0)
            {
                NodesValuesPointer[x] = Node1;
                index1 = x;
                break;
            }
        }
        for (int x = 0; x < NodesNumber; x++)
        {
            if(NodesValuesPointer[x] == Node2)
            {
                index2 = x;
                break;
            }
            if (NodesValuesPointer[x] == 0)
            {
                NodesValuesPointer[x] = Node2;
                index2 = x;
                break;
            }
        }

        AdjacencyMatrix[index1][index2] = 1;
        AdjacencyMatrix[index2][index1] = 1;
    }
    void addNode(int Node)
    {
        // Tworzenie nowej, większej macierzy sąsiedztwa w celu dodania nowego wierzcholka

        int newNodesNumber = NodesNumber + 1;
        int **newAdjacencyMatrix = new int *[newNodesNumber];
        int *newNodesValuesPointer = new int[newNodesNumber];

        // Kopiowanie istniejących danych do nowej macierzy
        for (int i = 0; i < NodesNumber; i++)
        {
            newAdjacencyMatrix[i] = new int[newNodesNumber];
            newNodesValuesPointer[i] = NodesValuesPointer[i];
            for (int j = 0; j < NodesNumber; j++)
            {
                newAdjacencyMatrix[i][j] = AdjacencyMatrix[i][j];
            }
        }

        // Inicjalizacja nowych elementów wiersza
        for (int i = 0; i < newNodesNumber; i++)
        {
            newAdjacencyMatrix[newNodesNumber][i] = 0;
            newAdjacencyMatrix[i][newNodesNumber] = 0;
        }

        // Usuwanie starej macierzy sąsiedztwa
        for (int i = 0; i < NodesNumber; i++)
        {
            delete[] AdjacencyMatrix[i];
        }
        delete[] NodesValuesPointer;
        delete[] AdjacencyMatrix;

        // Aktualizacja wskaźników
        AdjacencyMatrix = newAdjacencyMatrix;
        NodesNumber = newNodesNumber;
    }
    void removeEdge(int Node1, int Node2)
    {
        //znajujemy indeks odpowiedniego wierzcholka i w macierzy ustawiamy dla nich 0 
        int index1, index2;
        for (int x = 0; x < NodesNumber; x++)
        {
            if (NodesValuesPointer[x] == Node1)
                index1 = x;
            else if (NodesValuesPointer[x] == Node2)
                index2 = x;
        }
        AdjacencyMatrix[index1][index2] = 0;
        AdjacencyMatrix[index2][index1] = 0;
    }
    void removeNode(int Node)
    {
        // Tworzenie nowej, mniejszej macierzy sąsiedztwa
        int index1;
        int newNodesNumber = NodesNumber - 1;
        int **newAdjacencyMatrix = new int *[newNodesNumber];
        int *newNodesValuesPointer = new int[newNodesNumber];
        for (int x = 0; x < NodesNumber; x++)
        {
            if (NodesValuesPointer[x] == Node)
                index1 = x;
        }

        // Kopiowanie istniejących danych do nowej macierzy (bez usuwanego wierzchołka)
        int newRow = 0;
        for (int i = 0; i < NodesNumber; i++)
        {
            // Pomijanie usuwanego wiersza
            if (i == index1)
            {
                continue;
            }

            newAdjacencyMatrix[newRow] = new int[newNodesNumber];
            newNodesValuesPointer = new int[newNodesNumber];

            int newCol = 0;
            for (int j = 0; j < NodesNumber; j++)
            {
                // Pomijanie usuwanej kolumny
                if (j == index1)
                {
                    continue;
                }

                newAdjacencyMatrix[newRow][newCol] = AdjacencyMatrix[i][j];
                newNodesValuesPointer[newRow] = NodesValuesPointer[newNodesNumber];
                newCol++;
            }

            newRow++;
        }

        // Usuwanie starej macierzy sąsiedztwa
        for (int i = 0; i < NodesNumber; i++)
        {
            delete[] AdjacencyMatrix[i];
        }
        delete[] NodesValuesPointer;
        delete[] AdjacencyMatrix;

        // Aktualizacja wskaźników
        AdjacencyMatrix = newAdjacencyMatrix;
        NodesNumber = newNodesNumber;
    }
    void showNeighbours()
    {
        for (int x = 0; x < NodesNumber; x++)
        {
            cout << "Wierzcholek: " << NodesValuesPointer[x];
            cout << " - sasiedzi -> ";
            for (int y = 0; y < NodesNumber; y++)
            {
                if (AdjacencyMatrix[x][y] == 1)
                {
                    cout << NodesValuesPointer[y] << ", ";
                }
            }
            cout << endl;
        }
    }
};

#endif