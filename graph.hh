#ifndef GRAPH_HH
#define GRAPH_HH
#include <iostream>
#include "linkedlst.hh"
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

class Graph
{
public:
    GraphElem *Head;
    Graph()
    {
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
    void addEdge(int Node1, int Node2)
    {
        GraphElem *tmp1 = searchGraph(Node1);
        GraphElem *tmp2 = searchGraph(Node2);
        if (tmp1 == nullptr)
        {
            addNode(Node1);
            tmp1 = searchGraph(Node1);
            tmp1->LinkedListPointer->addElem(Node2);
        }
        else
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
    }
    void removeNode(int value)
    {
        GraphElem *tmp = Head;
        GraphElem *SearchedElemPointer;
        GraphElem *NextElemPointer;
        GraphElem *PreviousElemPointer = Head;    // adres poprzedniego elementu deklarujemy na poczatek listy
        SearchedElemPointer = searchGraph(value); // przypisujemy adres poszukiwanego elemetnu
        if (SearchedElemPointer != nullptr)
        {
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