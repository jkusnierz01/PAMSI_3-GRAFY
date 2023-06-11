#ifndef QUICKSORT_HH
#define QUICKSORT_HH
#include "struct.hh"
#include <iostream>
using namespace std;


void quicksort(ranking_elem tab[], int tab_size, int first)
{
    float pivot = tab[(first + tab_size-1) / 2].ranking;
    int left = first, right = tab_size - 1;
    ranking_elem tmp;
    while (left <= right)
    {
        while (tab[left].ranking < pivot)
        {
            left++;
        }
        while (tab[right].ranking > pivot)
        {
            right--;
        }
        if (left <= right)
        {
            tmp = tab[left];
            tab[left] = tab[right];
            tab[right] = tmp;
            left++;
            right--;
        }
    }
    if (first < right)
        quicksort(tab, right + 1, first);
    if (left < tab_size - 1)
        quicksort(tab, tab_size,left );
}
#endif

void Kruskal(Graph *graph, int numEdges, int numVertices)
{
    int iter = 0;
    GraphElemEgde tab[numEdges];
    GraphElemEgde *tmp = graph->EgdeHead;
    while (tmp != nullptr)
    {
        tab[iter].Node1 = tmp->Node1;
        tab[iter].Node2 = tmp->Node2;
        tab[iter].Value = tmp->Value;
    }
    // Tworzenie zbioru rozłącznego dla każdego wierzchołka
    GraphElem *vertices = new GraphElem[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        vertices[i].next = nullptr;
    }

    // Sortowanie krawędzi grafu w kolejności niemalejącej
    quicksort(tab, numEdges, 0);

    GraphElemEgde *mstEdges = new GraphElemEgde[numVertices - 1];
    int mstEdgeCount = 0;

    for (int i = 0; i < numEdges; ++i)
    {
        GraphElemEgde currentEdge = graphEdges[i];
        GraphElem *root1 = findRoot(vertices, currentEdge.Node1);
        GraphElem *root2 = findRoot(vertices, currentEdge.Node2);

        if (root1 != root2)
        {
            // Krawędź nie tworzy cyklu, dodaj ją do MST
            mstEdges[mstEdgeCount] = currentEdge;
            mstEdgeCount++;

            // Połącz zbiory rozłączne zawierające wierzchołki krawędzi
            unionSets(vertices, root1, root2);
        }

        if (mstEdgeCount == numVertices - 1)
            break;
    }

    // Wyświetl krawędzie MST
    for (int i = 0; i < mstEdgeCount; ++i)
    {
        std::cout << mstEdges[i].Node1->NodeValue << " -- " << mstEdges[i].Node2->NodeValue << std::endl;
    }

    // Zwolnij pamięć
    delete[] vertices;
    delete[] mstEdges;
}