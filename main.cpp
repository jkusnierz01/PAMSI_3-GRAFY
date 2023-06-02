#include <iostream>
#include "graph.hh"
#include "linkedlst.hh"
using namespace std;

// class LinkedListElem
// {
// public:
//     int Value;
//     LinkedListElem *next;
// };

// class LinkedList
// {
// public:
//     LinkedListElem *Head;
//     LinkedList()
//     {
//         Head = nullptr;
//     }
//     void addElem(int value)
//     {
//         LinkedListElem *New = new LinkedListElem;
//         New->Value = value;
//         New->next = nullptr;

//         if (Head == nullptr)
//         {
//             Head = New;
//         }
//         else
//         {
//             LinkedListElem *current = Head;
//             // Przechodzenie do ostatniego węzła na liście
//             while (current->next != nullptr)
//             {
//                 current = current->next;
//             }
//             current->next = New;
//         }
//     }
//     void removeElem(int Value)
//     {
//         LinkedListElem *tmpPointer;
//         tmpPointer = Head;
//         while (tmpPointer != nullptr)
//         {
//         }
//     }
// };
// // graf oparty na liscie sasiedztwa
// class EdgeListGraph
// {
// public:
//     int LiczbaWierzchlokow;
//     LinkedList **Pointer; // wskaznik na tablice wskaznikow na elementy listy jednokierunkowej
//     EdgeListGraph(int value)
//     {
//         LiczbaWierzchlokow = value;
//         Pointer = new LinkedList *[LiczbaWierzchlokow];
//         for (int i = 0; i < LiczbaWierzchlokow; i++)
//         {
//             Pointer[i] = new LinkedList;
//         }
//     }

//     void addEdge(int node1, int node2) // dodawanie krawedzi miedzy dwoma wierzchołkami
//     {
//         // wykorzystujemy metody dodawania elementow do listy jednokierunkowej
//         Pointer[node1]->addElem(node2);
//         Pointer[node2]->addElem(node1);
//     }
//     // dodawanie nowego wierzcholka
//     // musimy stworzyc tablice o rozmiar wieksza - os x a nastepnie do niej przepisac wartosci z dotychczasowej
//     void addNode()
//     {
//         LinkedListElem *tmp2;
//         LiczbaWierzchlokow++;
//         LinkedList **tmpPointer;                           // tworzymy druga liste sasiedztwa lecz o 1 wieksza
//         tmpPointer = new LinkedList *[LiczbaWierzchlokow]; // tablica dwuwymiarowa
//         for (int i = 0; i < LiczbaWierzchlokow; i++)
//         {
//             tmpPointer[i] = new LinkedList;
//         }
//         for (int i = 0; i < LiczbaWierzchlokow - 1; i++)
//         {
//             tmp2 = Pointer[i]->Head; // przypisujemy adres ktory znajduje sie w head danej listy - lista jest dla kazdego wierzcholka
//             while (tmp2 != nullptr)
//             {
//                 tmpPointer[i]->addElem(tmp2->Value);
//                 tmp2 = tmp2->next;
//             }
//         }
//         delete[] Pointer;
//         Pointer = tmpPointer;
//     }

//     void showNeighbours() // wyswietlanie listy sasiedztwa
//     {
//         LinkedListElem *tmp;
//         for (int x = 0; x < LiczbaWierzchlokow; x++)
//         {
//             cout << "Wierzcholek " << x << ", sasiedzi-> ";
//             tmp = Pointer[x]->Head;
//             while (tmp != nullptr)
//             {
//                 cout << tmp->Value << ", ";
//                 tmp = tmp->next;
//             }
//             cout << endl;
//         }
//     }
// };
int main()
{
    Graph Graph;
    Graph.addNode(0);
    Graph.addNode(2);
    Graph.addNode(3);
    Graph.addEdge(0,2);
    Graph.addEdge(2,3);
    Graph.ShowNeighbours();
    Graph.removeNode(3);
    Graph.ShowNeighbours();
}
