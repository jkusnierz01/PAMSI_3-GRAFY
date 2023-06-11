#ifndef ALGORYTM_HH
#define ALGORYTM_HH
#include "graph.hh"
#include "graph_matrix.hh"
#include <iostream>
using namespace std;

//*****************************************//
//
//
//
// LISTA SASIEDZTWA /////////////////////////
//
//
//
//*******************************************
void quicksort(GraphElemEgde tab[], int tab_size, int first)
{
    float pivot = tab[(first + tab_size-1) / 2].Value;
    int left = first, right = tab_size - 1;
    GraphElemEgde tmp;
    while (left <= right)
    {
        while (tab[left].Value < pivot)
        {
            left++;
        }
        while (tab[right].Value > pivot)
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


// Funkcja porównująca dwie krawędzie
bool compareEdges(const GraphElemEgde& edge1, const GraphElemEgde& edge2)
{
    return edge1.Value < edge2.Value;
}
GraphElem *findRoot(GraphElem *elem)
{
    if (elem->next == nullptr)
        return elem;
    return findRoot(elem->next);
}

// Funkcja pomocnicza do łączenia dwóch zbiorów w strukturze zbiorów rozłącznych
void unionSets(GraphElem *elem1, GraphElem *elem2)
{
    GraphElem *root1 = findRoot(elem1);
    GraphElem *root2 = findRoot(elem2);
    root2->next = root1;
}

// Algorytm Kruskala dla grafu opartego na liście sąsiedztwa
void Kruskal(Graph graph)
{
    GraphElemEgde *mstEdges = nullptr; // Lista krawędzi MST
    int numVertices = 0;               // Liczba wierzchołków w grafie

    // Tworzenie zbioru rozłącznego dla każdego wierzchołka
    GraphElem *currentVertex = graph.Head;
    while (currentVertex != nullptr)
    {
        currentVertex->next = nullptr;
        numVertices++;
        currentVertex = currentVertex->next;
    }

    // Sortowanie krawędzi grafu w kolejności niemalejącej
    GraphElemEgde *currentEdge = graph.EgdeHead;
    while (currentEdge != nullptr)
    {
        GraphElemEgde *minEdge = currentEdge;
        GraphElemEgde *nextEdge = currentEdge->next;

        while (nextEdge != nullptr)
        {
            if (nextEdge->Value < minEdge->Value)
                minEdge = nextEdge;

            nextEdge = nextEdge->next;
        }

        // Sprawdzanie czy dodanie krawędzi spowoduje cykl
        GraphElem *root1 = findRoot(minEdge->Node1);
        GraphElem *root2 = findRoot(minEdge->Node2);

        if (root1 != root2)
        {
            // Krawędź nie tworzy cyklu, dodaj ją do MST
            mstEdges->next = minEdge;
            mstEdges = minEdge;

            // Połącz zbiory rozłączne zawierające wierzchołki krawędzi
            unionSets(root1, root2);
        }

        currentEdge = currentEdge->next;
    }

    // Wyświetl krawędzie MST
    currentEdge = graph.EgdeHead;
    while (currentEdge != nullptr)
    {
        if (currentEdge != nullptr)
            std::cout << currentEdge->Node1->NodeValue << " -- " << currentEdge->Node2->NodeValue << std::endl;

        currentEdge = currentEdge->next;
    }
}


GraphElemEgde* getMinimumEdge(GraphElemEgde *edgeList)
{
    GraphElemEgde *minEdge = edgeList;
    GraphElemEgde *currentEdge = edgeList;

    while (currentEdge != nullptr)
    {
        if (currentEdge->Value < minEdge->Value)
            minEdge = currentEdge;
        currentEdge = currentEdge->next;
    }

    return minEdge;
}

void addEdgeToMST(GraphElemEgde *&mstEdges, GraphElemEgde *edge)
{
    if (mstEdges == nullptr)
    {
        mstEdges = edge;
        edge->next = nullptr;
    }
    else
    {
        edge->next = mstEdges;
        mstEdges = edge;
    }
}

void removeEdgeFromList(GraphElemEgde *&edgeList, GraphElemEgde *edge)
{
    if (edgeList == edge)
    {
        edgeList = edge->next;
    }
    else
    {
        GraphElemEgde *currentEdge = edgeList;
        while (currentEdge->next != edge)
        {
            currentEdge = currentEdge->next;
        }
        currentEdge->next = edge->next;
    }
}

void Prim(Graph graph, int l_wierzcholkow)
{
    GraphElemEgde *mstEdges = nullptr; // Lista krawędzi MST

    // Wybierz pierwszy wierzchołek jako startowy
    GraphElem *startVertex = graph.Head;

    // Utwórz tablicę odwiedzonych wierzchołków
    bool *visited = new bool[l_wierzcholkow];
    for (int i = 0; i < l_wierzcholkow; i++)
    {
        visited[i] = false;
    }

    // Utwórz listę krawędzi
    GraphElemEgde *edgeList = graph.EgdeHead;

    // Oznacz startowy wierzchołek jako odwiedzony
    visited[startVertex->NodeValue] = true;

    // Główna pętla algorytmu
    while (edgeList != nullptr)
    {
        // Znajdź najmniejszą wagę krawędzi
        GraphElemEgde *minEdge = getMinimumEdge(edgeList);

        // Usuń krawędź z listy
        removeEdgeFromList(edgeList, minEdge);

        // Pobierz wierzchołki krawędzi
        GraphElem *node1 = minEdge->Node1;
        GraphElem *node2 = minEdge->Node2;

        // Jeśli oba wierzchołki są odwiedzone, pomiń tę krawędź
        if (visited[node1->NodeValue] && visited[node2->NodeValue])
        {
            delete minEdge;
            continue;
        }

        // Dodaj krawędź do MST
        addEdgeToMST(mstEdges, minEdge);

        // Oznacz wierzchołki jako odwiedzone
        visited[node1->NodeValue] = true;
        visited[node2->NodeValue] = true;
    }

    // Wyświetl krawędzie MST
    GraphElemEgde *currentEdge = mstEdges;
    while (currentEdge != nullptr)
    {
        std::cout << currentEdge->Node1->NodeValue << " -- " << currentEdge->Node2->NodeValue << std::endl;
        currentEdge = currentEdge->next;
    }

    // Zwolnienie pamięci
    delete[] visited;
}



//*****************************************//
//
//
//
// Macierz SASIEDZTWA /////////////////////////
//
//
//
//*******************************************

void Kruskall(GraphMatrix graph)
{
    GraphElemEgde *mstEdges = nullptr; // Lista krawędzi MST
    int numVertices = 0;               // Liczba wierzchołków w grafie

    // Tworzenie zbioru rozłącznego dla każdego wierzchołka
    GraphElem *currentVertex = graph.Head;
    while (currentVertex != nullptr)
    {
        currentVertex->next = nullptr;
        numVertices++;
        currentVertex = currentVertex->next;
    }

    
    // Sortowanie krawędzi grafu w kolejności niemalejącej
    GraphElemEgde *currentEdge = graph.EgdeHead;
    while (currentEdge != nullptr)
    {
        GraphElemEgde *minEdge = currentEdge;
        GraphElemEgde *nextEdge = currentEdge->next;

        while (nextEdge != nullptr)
        {
            if (nextEdge->Value < minEdge->Value)
                minEdge = nextEdge;

            nextEdge = nextEdge->next;
        }

        // Sprawdzanie czy dodanie krawędzi spowoduje cykl
        GraphElem *root1 = findRoot(minEdge->Node1);
        GraphElem *root2 = findRoot(minEdge->Node2);

        if (root1 != root2)
        {
            // Krawędź nie tworzy cyklu, dodaj ją do MST
            mstEdges->next = minEdge;
            mstEdges = minEdge;

            // Połącz zbiory rozłączne zawierające wierzchołki krawędzi
            unionSets(root1, root2);
        }

        currentEdge = currentEdge->next;
    }
    
    // Wyświetl krawędzie MST
    currentEdge = graph.EgdeHead;
    while (currentEdge != nullptr)
    {
        
        if (currentEdge != nullptr)
            std::cout << currentEdge->Node1->NodeValue << " -- " << currentEdge->Node2->NodeValue << std::endl;

        currentEdge = currentEdge->next;
    }
    
}

void Primm(GraphMatrix graph, int l_wierzcholkow)
{
    GraphElemEgde *mstEdges = nullptr; // Lista krawędzi MST

    // Wybierz pierwszy wierzchołek jako startowy
    GraphElem *startVertex = graph.Head;

    // Utwórz tablicę odwiedzonych wierzchołków
    bool *visited = new bool[l_wierzcholkow];
    for (int i = 0; i < l_wierzcholkow; i++)
    {
        visited[i] = false;
    }

    // Utwórz listę krawędzi
    GraphElemEgde *edgeList = graph.EgdeHead;

    // Oznacz startowy wierzchołek jako odwiedzony
    visited[startVertex->NodeValue] = true;

    // Główna pętla algorytmu
    while (edgeList != nullptr)
    {
        // Znajdź najmniejszą wagę krawędzi
        GraphElemEgde *minEdge = getMinimumEdge(edgeList);

        // Usuń krawędź z listy
        removeEdgeFromList(edgeList, minEdge);

        // Pobierz wierzchołki krawędzi
        GraphElem *node1 = minEdge->Node1;
        GraphElem *node2 = minEdge->Node2;

        // Jeśli oba wierzchołki są odwiedzone, pomiń tę krawędź
        if (visited[node1->NodeValue] && visited[node2->NodeValue])
        {
            delete minEdge;
            continue;
        }

        // Dodaj krawędź do MST
        addEdgeToMST(mstEdges, minEdge);

        // Oznacz wierzchołki jako odwiedzone
        visited[node1->NodeValue] = true;
        visited[node2->NodeValue] = true;
    }

    // Wyświetl krawędzie MST
    GraphElemEgde *currentEdge = mstEdges;
    while (currentEdge != nullptr)
    {
        std::cout << currentEdge->Node1->NodeValue << " -- " << currentEdge->Node2->NodeValue << std::endl;
        currentEdge = currentEdge->next;
    }

    // Zwolnienie pamięci
    delete[] visited;
}

#endif