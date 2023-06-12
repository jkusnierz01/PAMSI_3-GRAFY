#ifndef ALGORYTM_HH
#define ALGORYTM_HH
#include "graph.hh"
#include "graph_matrix.hh"
#include <iostream>
using namespace std;
const int MAX_VERTICES = 500000;

//*****************************************//
//
//
//
// LISTA SASIEDZTWA /////////////////////////
//
//
//
//*******************************************
//zbior rozlaczny 
class DisjointSet
{
private:
    int *parent;
    int *rank;
    int size;

public:
    DisjointSet(int n)
    {
        size = n;
        parent = new int[n];
        rank = new int[n];

        // Inicjalizacja zbiorów rozłącznych
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // Każdy element jest początkowo rodzicem samego siebie
            rank[i] = 0;   // Początkowo każdy zbiór ma rangę 0
        }
    }

    int find(int v)
    {
        if (v != parent[v])
        {
            parent[v] = find(parent[v]); // Skompresowanie ścieżki
        }
        return parent[v];
    }

    void merge(int v1, int v2)
    {
        int root1 = find(v1);
        int root2 = find(v2);

        if (root1 != root2)
        {
            if (rank[root1] < rank[root2])
            {
                parent[root1] = root2;
            }
            else if (rank[root1] > rank[root2])
            {
                parent[root2] = root1;
            }
            else
            {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }
};

void quicksort(GraphElemEgde tab[], int tab_size, int first)
{
    float pivot = tab[(first + tab_size - 1) / 2].Value;
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
            tmp.next = tab[left].next;
            tmp.Node1 = tab[left].Node1;
            tmp.Node2 = tab[left].Node2;
            tmp.Value = tab[left].Value;

            tab[left].next = tab[right].next;
            tab[left].Node1 = tab[right].Node1;
            tab[left].Node2 = tab[right].Node2;
            tab[left].Value = tab[right].Value;

            tab[right].next = tmp.next;
            tab[right].Node1 = tmp.Node1;
            tab[right].Node2 = tmp.Node2;
            tab[right].Value = tmp.Value;
            left++;
            right--;
        }
    }
    if (first < right)
        quicksort(tab, right + 1, first);
    if (left < tab_size - 1)
        quicksort(tab, tab_size, left);
}

void Kruskal(Graph *graph, int numEdges, int numVertices)
{
    // tworzenie tablicy na podstawie listy jednokierunkowej
    int iter = 0;
    bool if_already_on_mst_node1 = false;
    bool if_already_on_mst_node2 = false;
    GraphElemEgde tab[numEdges];
    GraphElemEgde *tmp = graph->EgdeHead;
    GraphElem *NodesPointer = graph->Head;
    while (tmp != nullptr)
    {
        tab[iter].next = tmp->next;
        tab[iter].Node1 = tmp->Node1;
        tab[iter].Node2 = tmp->Node2;
        tab[iter].Value = tmp->Value;
        tmp = tmp->next;
        iter++;
    }
    // tablica krawedzi minimal spanning tree - naszego drzewa wyjsciowego
    GraphElemEgde mstEdges[numVertices - 1];
    int mstEdgeCount = 0;
    // tablica drzew rozlacznych - na poczatku kazdy wierzcholek jest osobnym drzewem rozlacznym
    GraphElem vertices[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        vertices[i].NodeValue = NodesPointer->NodeValue;
        vertices[i].next = NodesPointer->next;
    }
    quicksort(tab, numEdges, 0);
    DisjointSet disjointSet(numVertices);

    int edgeIndex = 0;
    while (mstEdgeCount < numVertices - 1 && edgeIndex < numEdges)
    {
        GraphElemEgde nextEdge = tab[edgeIndex++];

        int root1 = disjointSet.find(nextEdge.Node1->NodeValue);
        int root2 = disjointSet.find(nextEdge.Node2->NodeValue);

        if (root1 != root2)
        {
            // Dodanie krawędzi do minimal spanning tree
            mstEdges[mstEdgeCount++] = nextEdge;

            // Połączenie zbiorów rozłącznych
            disjointSet.merge(root1, root2);
        }
    }
    for (int i = 0; i < mstEdgeCount; ++i)
    {
        std::cout << mstEdges[i].Node1->NodeValue << " -- " << mstEdges[i].Node2->NodeValue << std::endl;
    }
}

// ALOGORYTM PRIMA

void Prim(Graph* graph) {
    int numVertices = 0;
    GraphElem* current = graph->Head;
    
    while (current != nullptr) {
        numVertices++;
        current = current->next;
    }
    
    bool visited[MAX_VERTICES] = { false }; // Tablica odwiedzonych wierzchołków
    int minWeight[MAX_VERTICES]; // Tablica przechowująca minimalne wagi krawędzi do danego wierzchołka
    int parent[MAX_VERTICES]; // Tablica przechowująca rodziców wierzchołków w minimalnym drzewie rozpinającym

    // Inicjalizacja tablic
    for (int i = 0; i < numVertices; i++) {
        minWeight[i] = numeric_limits<int>::max(); // Przypisujemy maksymalną wartość
        parent[i] = -1; // Przypisujemy wartość -1 (brak rodzica)
    }

    // Rozpoczynamy od pierwszego wierzchołka
    int startVertex = 0;
    visited[startVertex] = true;
    minWeight[startVertex] = 0;
    
    // Przetwarzamy wszystkie krawędzie
    GraphElemEgde* currentEdge = graph->EgdeHead;
    while (currentEdge != nullptr) {
        int node1 = currentEdge->Node1->NodeValue;
        int node2 = currentEdge->Node2->NodeValue;
        int weight = currentEdge->Value;

        if (visited[node1] && !visited[node2] && weight < minWeight[node2]) {
            // Jeśli krawędź prowadzi do jeszcze nieodwiedzonego wierzchołka
            // i ma mniejszą wagę niż dotychczasowa minimalna waga dla tego wierzchołka,
            // aktualizujemy minimalną wagę i rodzica
            minWeight[node2] = weight;
            parent[node2] = node1;
        }
        else if (!visited[node1] && visited[node2] && weight < minWeight[node1]) {
            minWeight[node1] = weight;
            parent[node1] = node2;
        }

        currentEdge = currentEdge->next;
    }

    // Konstrukcja minimalnego drzewa rozpinającego
    for (int i = 1; i < numVertices; i++) {
        int minWeightVertex = -1;
        int minWeightValue = numeric_limits<int>::max();

        // Wybieramy wierzchołek o najmniejszej wadze
        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && minWeight[j] < minWeightValue) {
                minWeightValue = minWeight[j];
                minWeightVertex = j;
            }
        }

        // Dodajemy krawędź do minimalnego drzewa rozpinającego
        // cout << "Krawedz: " << parent[minWeightVertex] << " -- " << minWeightVertex << endl;

        // Oznaczamy wierzchołek jako odwiedzony
        visited[minWeightVertex] = true;

        // Aktualizujemy minimalne wagi dla sąsiadujących wierzchołków
        currentEdge = graph->EgdeHead;
        while (currentEdge != nullptr) {
            int node1 = currentEdge->Node1->NodeValue;
            int node2 = currentEdge->Node2->NodeValue;
            int weight = currentEdge->Value;

            if ((visited[node1] && !visited[node2] && weight < minWeight[node2]) ||
                (!visited[node1] && visited[node2] && weight < minWeight[node1])) {
                // Jeśli krawędź prowadzi do jeszcze nieodwiedzonego wierzchołka
                // i ma mniejszą wagę niż dotychczasowa minimalna waga dla tego wierzchołka,
                // aktualizujemy minimalną wagę i rodzica
                minWeight[node2] = weight;
                parent[node2] = node1;
                minWeight[node1] = weight;
                parent[node1] = node2;
            }

            currentEdge = currentEdge->next;
        }
    }
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

void Kruskal(GraphMatrix *graph, int numEdges, int numVertices)
{
    // tworzenie tablicy na podstawie listy jednokierunkowej
    int iter = 0;
    GraphElemEgde* tab = new GraphElemEgde[numEdges];
    GraphElemEgde *tmp = graph->EgdeHead;
    while (tmp != nullptr)
    {
        tab[iter].next = tmp->next;
        tab[iter].Node1 = tmp->Node1;
        tab[iter].Node2 = tmp->Node2;
        tab[iter].Value = tmp->Value;
        tmp = tmp->next;
        iter++;
    }
    // tablica krawedzi minimal spanning tree - naszego drzewa wyjsciowego
    GraphElemEgde mstEdges[numVertices - 1];
    int mstEdgeCount = 0;
    // tablica drzew rozlacznych - na poczatku kazdy wierzcholek jest osobnym drzewem rozlacznym
    quicksort(tab, numEdges, 0);
    DisjointSet disjointSet(numVertices);

    int edgeIndex = 0;

    while (mstEdgeCount < numVertices - 1 && edgeIndex < numEdges)
    {
        GraphElemEgde nextEdge = tab[edgeIndex++];

        int root1 = disjointSet.find(nextEdge.Node1->NodeValue);
        int root2 = disjointSet.find(nextEdge.Node2->NodeValue);

        if (root1 != root2)
        {
            // Dodanie krawędzi do minimal spanning tree
            mstEdges[mstEdgeCount++] = nextEdge;

            // Połączenie zbiorów rozłącznych
            disjointSet.merge(root1, root2);
        }
    }
    // for (int i = 0; i < mstEdgeCount; ++i)
    // {
    //     std::cout << mstEdges[i].Node1->NodeValue << " -- " << mstEdges[i].Node2->NodeValue << std::endl;
    // }
}


void Prim(GraphMatrix* graph) {
    int numVertices = 0;
    GraphElem* current = graph->Head;
    
    while (current != nullptr) {
        numVertices++;
        current = current->next;
    }
    
    bool visited[MAX_VERTICES] = { false }; // Tablica odwiedzonych wierzchołków
    int minWeight[MAX_VERTICES]; // Tablica przechowująca minimalne wagi krawędzi do danego wierzchołka
    int parent[MAX_VERTICES]; // Tablica przechowująca rodziców wierzchołków w minimalnym drzewie rozpinającym

    // Inicjalizacja tablic
    for (int i = 0; i < numVertices; i++) {
        minWeight[i] = numeric_limits<int>::max(); // Przypisujemy maksymalną wartość
        parent[i] = -1; // Przypisujemy wartość -1 (brak rodzica)
    }

    // Rozpoczynamy od pierwszego wierzchołka
    int startVertex = 0;
    visited[startVertex] = true;
    minWeight[startVertex] = 0;
    
    // Przetwarzamy wszystkie krawędzie
    GraphElemEgde* currentEdge = graph->EgdeHead;
    while (currentEdge != nullptr) {
        int node1 = currentEdge->Node1->NodeValue;
        int node2 = currentEdge->Node2->NodeValue;
        int weight = currentEdge->Value;

        if (visited[node1] && !visited[node2] && weight < minWeight[node2]) {
            // Jeśli krawędź prowadzi do jeszcze nieodwiedzonego wierzchołka
            // i ma mniejszą wagę niż dotychczasowa minimalna waga dla tego wierzchołka,
            // aktualizujemy minimalną wagę i rodzica
            minWeight[node2] = weight;
            parent[node2] = node1;
        }
        else if (!visited[node1] && visited[node2] && weight < minWeight[node1]) {
            minWeight[node1] = weight;
            parent[node1] = node2;
        }

        currentEdge = currentEdge->next;
    }

    // Konstrukcja minimalnego drzewa rozpinającego
    for (int i = 1; i < numVertices; i++) {
        int minWeightVertex = -1;
        int minWeightValue = numeric_limits<int>::max();

        // Wybieramy wierzchołek o najmniejszej wadze
        for (int j = 0; j < numVertices; j++) {
            if (!visited[j] && minWeight[j] < minWeightValue) {
                minWeightValue = minWeight[j];
                minWeightVertex = j;
            }
        }

        // Dodajemy krawędź do minimalnego drzewa rozpinającego
        // cout << "Krawedz: " << parent[minWeightVertex] << " -- " << minWeightVertex << endl;

        // Oznaczamy wierzchołek jako odwiedzony
        visited[minWeightVertex] = true;

        // Aktualizujemy minimalne wagi dla sąsiadujących wierzchołków
        currentEdge = graph->EgdeHead;
        while (currentEdge != nullptr) {
            int node1 = currentEdge->Node1->NodeValue;
            int node2 = currentEdge->Node2->NodeValue;
            int weight = currentEdge->Value;

            if ((visited[node1] && !visited[node2] && weight < minWeight[node2]) ||
                (!visited[node1] && visited[node2] && weight < minWeight[node1])) {
                // Jeśli krawędź prowadzi do jeszcze nieodwiedzonego wierzchołka
                // i ma mniejszą wagę niż dotychczasowa minimalna waga dla tego wierzchołka,
                // aktualizujemy minimalną wagę i rodzica
                minWeight[node2] = weight;
                parent[node2] = node1;
                minWeight[node1] = weight;
                parent[node1] = node2;
            }

            currentEdge = currentEdge->next;
        }
    }
}

#endif