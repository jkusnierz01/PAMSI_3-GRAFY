#ifndef GRAPH_HH
#define GRAPH_HH
#include <iostream>
#include "linkedlst.hh"
#include "edgelist.hh"
using namespace std;

class GraphElem
{
public:
    int NodeValue;
    LinkedList *LinkedListPointer;
    GraphElem *next;
    GraphElem(int value)
    {
        NodeValue = value;
        LinkedListPointer = new LinkedList;
        next = nullptr;
    }
};

class GraphElemEgde
{
public:
    int Value;
    GraphElem *Node1;
    GraphElem *Node2;
    GraphElemEgde *next;
    GraphElemEgde(GraphElem *n1, GraphElem *n2, int value)
    {
        Value = value;
        Node1 = n1;
        Node2 = n2;
        next = nullptr;
    }
};

class Graph
{
public:
    GraphElem *Head;
    GraphElemEgde *EgdeHead;
    Graph()
    {
        EgdeHead = nullptr;
        Head = nullptr;
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
    GraphElemEgde *&searchGraphEgde(GraphElem *adress)
    {
        GraphElemEgde *tmp = EgdeHead;
        // przeszukujemy liste w poszukiwaniu konkretnego wierzcholka do momentu kiedy nie ma juz nastepnego elementu
        while (tmp != nullptr) // sprawdzamy czy adres to nie nullptr - brak elementu - bo bylby segmentation fault inaczej
        {
            if (tmp->Node1 != adress && tmp->Node2 != adress) // sprawdzamy czy poszukiwana wartosc
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
    void addNode(int Value)
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
    void addEdge(int Node1, int Node2, int Value)
    {
        GraphElem *tmp1 = searchGraph(Node1); // sprawdzamy czy dane wierzcholki juz na liscie
        GraphElem *tmp2 = searchGraph(Node2);
        if (tmp1 == nullptr) // jezeli nullptr znaczy ze ich nie ma
        {
            addNode(Node1);
            tmp1 = searchGraph(Node1);
            tmp1->LinkedListPointer->addElem(Node2);
        }
        else // jezeli jest to sprawdz czy znajduje sie juz na liscie sasiedztwa
        {
            if (tmp1->LinkedListPointer->searchList(Node2) == nullptr)
            {
                tmp1->LinkedListPointer->addElem(Node2);
            }
        }
        if (tmp2 == nullptr)
        {
            addNode(Node2);
            tmp2 = searchGraph(Node2);
            tmp2->LinkedListPointer->addElem(Node1);
        }
        else
        {
            {
                if (tmp2->LinkedListPointer->searchList(Node1) == nullptr)
                {
                    tmp2->LinkedListPointer->addElem(Node1);
                }
            }
        }
        GraphElemEgde *tmp = new GraphElemEgde(tmp1, tmp2, Value);
        if (EgdeHead == nullptr)
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
    }
    void removeNode(int value)
    {
        GraphElemEgde *tmp2 = EgdeHead;
        GraphElemEgde *SearchedEdge;
        GraphElemEgde *NextEdgePointer;
        GraphElemEgde *PreviousEdgePointer = EgdeHead;
        GraphElem *tmp = Head;
        GraphElem *SearchedElemPointer;
        GraphElem *NextElemPointer;
        GraphElem *PreviousElemPointer = Head;    // adres poprzedniego elementu deklarujemy na poczatek listy
        SearchedElemPointer = searchGraph(value); // przypisujemy adres poszukiwanego elemetnu
        if (SearchedElemPointer != nullptr)
        {
            // POZBYWANIE SIE ELEMENTU Z LISTY WIERZCHOLKOW
            SearchedEdge = searchGraphEgde(SearchedElemPointer); // wyszukujemy dany wierzcholek w liscie krawedzi - zeby go usunac
            if (SearchedEdge != nullptr)
            {
                NextEdgePointer = SearchedEdge->next;
                if (EgdeHead != SearchedEdge) // sprawdzamy czy 1 element to juz poszukiwany - jak tak to do Head musimy przypisac nastepny - nullptr
                {

                    while (PreviousEdgePointer->next != SearchedEdge) // szukamy adresu poprzedniego elementu wzgledem poszukiwanego
                    {
                        PreviousEdgePointer = PreviousEdgePointer->next;
                    }
                    PreviousEdgePointer->next = NextEdgePointer; // do adresu poprzedniego elementu - przypisujemy adres nastepnego czyli tak zeby pominac usuwany element
                    delete SearchedEdge;                         // usuwamy element
                }
                else
                {
                    EgdeHead = NextEdgePointer;
                    delete SearchedEdge;
                }
            }

            // POZBYWANIE SIE ELEMENTU Z LISTY KRAWEDZI
            NextElemPointer = SearchedElemPointer->next; // bierzemy adres kolejnego elementu
            if (Head != SearchedElemPointer)             // sprawdzamy czy 1 element to juz poszukiwany - jak tak to do Head musimy przypisac nastepny - nullptr
            {
                while (PreviousElemPointer->next != SearchedElemPointer) // szukamy adresu poprzedniego elementu wzgledem poszukiwanego
                {
                    PreviousElemPointer = PreviousElemPointer->next;
                }
                PreviousElemPointer->next = NextElemPointer; // do adresu poprzedniego elementu - przypisujemy adres nastepnego czyli tak zeby pominac usuwany element
                delete SearchedElemPointer;                  // usuwamy element
            }
            else
            {
                Head = NextElemPointer;
                delete SearchedElemPointer;
            }
            // teraz nalezy usunac dany wierzcholek z listy sasiedztwa poszczegolnych wierzcholkow
            while (tmp != nullptr)
            {
                tmp->LinkedListPointer->removeElem(value);
                tmp = tmp->next;
            }
        }
    }

    void removeEdge(int Node1, int Node2, int Value)
    {
        GraphElemEgde *SearchedEdge = EgdeHead;
        GraphElemEgde *NextEdgePointer;
        GraphElemEgde *PreviousEdgePointer = EgdeHead;
        GraphElem *tmp = Head;
        while (tmp != nullptr)
        {
            tmp->LinkedListPointer->removeElem(Node1);
            tmp->LinkedListPointer->removeElem(Node2);
            tmp = tmp->next;
        }
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

    void ShowNeighbours()
    {
        GraphElem *GraphPointer = Head;
        LinkedListElem *ListPointer;
        while (GraphPointer != nullptr)
        {
            ListPointer = GraphPointer->LinkedListPointer->Head;
            cout << "Wierzchołek nr. " << GraphPointer->NodeValue << " - sasiedzi: ";
            while (ListPointer != nullptr)
            {
                cout << ListPointer->Value << ", ";
                ListPointer = ListPointer->next;
            }
            GraphPointer = GraphPointer->next;
            cout << endl;
        }
    }
};

#endif