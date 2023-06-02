#ifndef GRAPH_HH
#define GRAPH_HH
#include <iostream>
#include "linkedlst.hh"
using namespace std;

class GraphElem
{
    public:
    int NodeValue;
    LinkedList* LinkedListPointer;
    GraphElem* GraphElemPointer;
    GraphElem()
    {
        LinkedListPointer = nullptr;
        GraphElemPointer = nullptr;
    }
};


class Graph
{
    public:
    GraphElem* Head;
    Graph()
    {
        Head = nullptr;
    }

};


#endif