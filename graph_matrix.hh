#ifndef GRAPHMATRIX_HH
#define GRAPHMATRIX_HH
#include <iostream>
#include "graph.hh"
using namespace std;
// pomysl - macierz obiektow, dwa atrybuty: int, wskaznik na element listy wierzcholkow - wierzcholek
// normalnie NULL ale jak wskazniki to znaczy ze sa sasiadami, int to wartosc wierzcholkow
// pytanie jak robic dodawanie metoda addEgde(a,b) - spra

class GraphMatrix
{
public:
    GraphElem *Head;
    GraphElemEgde *EgdeHead;
    int **adjacencyMatrix;
    int NodesNumber;
    GraphMatrix(int value)
    {
        Head = nullptr;
        EgdeHead = nullptr;
        NodesNumber = value;
        adjacencyMatrix = new int *[NodesNumber];
        for (int x = 0; x < NodesNumber; x++)
        {
            adjacencyMatrix[x] = new int[NodesNumber];
            for (int j = 0; j < NodesNumber; j++)
            {
                adjacencyMatrix[x][j] = 0;
            }
        }
    }
    GraphMatrix()
    {
        Head = nullptr;
        EgdeHead = nullptr;
        adjacencyMatrix = new int *[NodesNumber];
        for (int x = 0; x < NodesNumber; x++)
        {
            adjacencyMatrix[x] = new int[NodesNumber];
            for (int j = 0; j < NodesNumber; j++)
            {
                adjacencyMatrix[x][j] = 0;
            }
        }
    }
    // metoda do dodania nowego wierzcholka do listy wierzchołkow
    void addNodeList(int Value)
    {
        GraphElem *New = new GraphElem(Value);
        if (Head == nullptr)
        {
            Head = New;
        }
        else
        {
            GraphElem *current = Head;
            // Przechodzenie do ostatniego węzła na liście
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = New;
        }
    }
    // metoda dodajaca nowy wierzcholek do macierzy sasiedztwa
    void addNodeMatrix(int Node)
    {
        // Tworzenie nowej, większej macierzy sąsiedztwa w celu dodania nowego wierzcholka
        int newNodesNumber = NodesNumber + 1;
        int **newAdjacencyMatrix = new int *[newNodesNumber];

        // Kopiowanie istniejących danych do nowej macierzy
        for (int i = 0; i < newNodesNumber; i++)
        {
            newAdjacencyMatrix[i] = new int[newNodesNumber];
            for (int j = 0; j < newNodesNumber; j++)
            {
                if (i != 5 && j != 5)
                {
                    newAdjacencyMatrix[i][j] = adjacencyMatrix[i][j];
                }
            }
        }
        // Inicjalizacja nowych elementów wiersza
        for (int i = 0; i < newNodesNumber; i++)
        {
            newAdjacencyMatrix[newNodesNumber - 1][i] = 0;
            newAdjacencyMatrix[i][newNodesNumber - 1] = 0;
        }
        // Usuwanie starej macierzy sąsiedztwa
        for (int i = 0; i < NodesNumber; i++)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;

        // Aktualizacja wskaźników
        adjacencyMatrix = newAdjacencyMatrix;
        NodesNumber = newNodesNumber;
    }
    // dodanie nowego wierzcholka
    void addNode(int Node)
    {
        // addNodeList(Node);   // dodajemy nowy element do listy wierzcholkow
        addNodeMatrix(Node); // dodanie nowego wierzcholka do macierzy sasiedztwa
    }

    int searchGraphIndex(int value)
    {
        GraphElem *tmp = Head;
        int index = 0;
        // przeszukujemy liste w poszukiwaniu konkretnego wierzcholka do momentu kiedy nie ma juz nastepnego elementu
        while (tmp != nullptr) // sprawdzamy czy adres to nie nullptr - brak elementu - bo bylby segmentation fault inaczej
        {
            if (tmp->NodeValue != value) // sprawdzamy czy poszukiwana wartosc
            {
                tmp = tmp->next;
                index++;
            }
            else // jezeli tak to zwracamy adres znalezionego elementu
            {
                return index; // zwracamy adres elementu ktory ma poszukiwana wartosc
            }
        }
        index = -1;
        return index;
    }
    GraphElem *&searchGraph(int value)
    {
        GraphElem *tmp = Head;
        // przeszukujemy liste w poszukiwaniu konkretnego wierzcholka do momentu kiedy nie ma juz nastepnego elementu
        while (tmp != nullptr) // sprawdzamy czy adres to nie nullptr - brak elementu - bo bylby segmentation fault inaczej
        {
            if (tmp->NodeValue != value) // sprawdzamy czy poszukiwana wartosc
            {
                tmp = tmp->next;
            }
            else // jezeli tak to zwracamy adres znalezionego elementu
            {
                return tmp; // zwracamy adres elementu ktory ma poszukiwana wartosc
            }
        }
        tmp = nullptr;
        return tmp;
    }
    void removeEdge(int Node1, int Node2, int Value)
    {
        int index1 = searchGraphIndex(Node1);
        int index2 = searchGraphIndex(Node2);
        if (adjacencyMatrix[index1][index2] != 0 && adjacencyMatrix[index2][index1] != 0)
        {
            adjacencyMatrix[index1][index2] = 0;
            adjacencyMatrix[index2][index1] = 0;
        }

        // USUWANIE KRAWEDZI Z LISTY KRAWEDZI
        GraphElemEgde *SearchedEdge = EgdeHead;
        GraphElemEgde *NextEdgePointer;
        GraphElemEgde *PreviousEdgePointer = EgdeHead;
        while (SearchedEdge->Value != Value)
        {
            SearchedEdge = SearchedEdge->next;
        }
        NextEdgePointer = SearchedEdge->next;
        if (PreviousEdgePointer == nullptr)
        {
            EgdeHead = NextEdgePointer;
            delete SearchedEdge;
        }
        else
        {
            if (PreviousEdgePointer == EgdeHead)
            {
                EgdeHead = NextEdgePointer;
            }
            else
            {
                while (PreviousEdgePointer->next != SearchedEdge)
                {
                    PreviousEdgePointer = PreviousEdgePointer->next;
                }
                PreviousEdgePointer = NextEdgePointer;
            }
            delete SearchedEdge;
        }
    }
    void addEdge(int Node1, int Node2, int Value)
    {
        // sprawdzamy czy dane wierzcholki juz na liscie wierzcholkow
        GraphElem *tmp1 = searchGraph(Node1);
        GraphElem *tmp2 = searchGraph(Node2);

        // jezeli nullptr znaczy ze ich nie ma
        if (tmp1 == nullptr)
        {
            addNodeList(Node1); // w takim razie dodajemy
            tmp1 = searchGraph(Node1); // potrzebujemy adresu, zeby wskaznik z krawedzi przypisac
        }
        // to samo dla drugiego wierzcholka
        if (tmp2 == nullptr)
        {
            addNodeList(Node2);
            tmp2 = searchGraph(Node2);
        }

        // teraz chcemy dodac krawedz do listy krawedzi
        GraphElemEgde *tmp = new GraphElemEgde(tmp1, tmp2, Value);
        if (EgdeHead == nullptr) // sprawdzamy czy lista pusta - jak tak to dodajemy jako 1 element, jak nie to idziemy na koniec listy i dodajemy
        {
            EgdeHead = tmp;
        }
        else
        {
            GraphElemEgde *current = EgdeHead;
            // Przechodzenie do ostatniego węzła na liście
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = tmp;
        }

        // chcemy dodać do macierzy sasiedztwa polaczenie miedzy odpowiednimi wiercholkami
        int index1 = searchGraphIndex(Node1);
        int index2 = searchGraphIndex(Node2);
        if (index1 != (-1) && index2 != (-1))
        {
            if (index1 < NodesNumber && index2 << NodesNumber)
            {
                if (adjacencyMatrix[index1][index2] == 0 && adjacencyMatrix[index2][index1] == 0)
                {
                    adjacencyMatrix[index1][index2] = 1;
                    adjacencyMatrix[index2][index1] = 1;
                }
            }
        }
        else
        {
            cout << "Brak podanych wierzcholkow" << endl;
        }
    }
    int findNode(int index)
    {
        GraphElem* tmp = Head;
        int i = 0;
        while(i<index)
        {
            if(tmp!=nullptr)
            {
                tmp = tmp->next;
            }
            else
            {
                cout << "brak elementow na liscie" << endl;
            }
            i++;
        }
        return tmp->NodeValue;
    }
    void showNeighbours()
    {
        GraphElem *tmp = Head;
        int index1,index2;
        int vvalue;
        for (int i = 0; i < NodesNumber; i++)
        {
            if (tmp != nullptr)
            {
                vvalue = tmp->NodeValue;
                tmp = tmp->next;
                cout << "Wierzchołek nr. " << vvalue << " - sasiedzi: ";
            }
            for (int j = 0; j < NodesNumber;j++)
            {
                if (adjacencyMatrix[i][j] == 1)
                {
                    cout << findNode(j) << ", ";
                }
            }
            cout << endl;
        }
    }
};

#endif