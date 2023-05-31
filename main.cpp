#include <iostream>
using namespace std;

class LinkedListElem
{
    public:
    int Value;
    LinkedListElem* next;
};

class LinkedList
{
    public:
    LinkedListElem* Head;
    LinkedList()
    {
        Head = nullptr;
    }
    void addElem(int value)
    {
        LinkedListElem* New = new LinkedListElem;
        New->Value = value;
        New->next = nullptr;

        if(Head == nullptr)
        {
            Head = New;
        }
        else 
        {
            LinkedListElem* current = Head;
            // Przechodzenie do ostatniego węzła na liście
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = New;
        
        }
    }
};

class EdgeListGraph
{
    public:
    int LiczbaWierzchlokow;
    LinkedList** Pointer;
    EdgeListGraph(int value)
    {
        LiczbaWierzchlokow = value;
        Pointer = new LinkedList*[LiczbaWierzchlokow];
        for(int i=0;i<LiczbaWierzchlokow;i++)
        {
            Pointer[i] = new LinkedList;
        }
    }

    void addEdge(int node1,int node2)
    {
        // Dla pierwszego wierzcholka
        Pointer[node1]->addElem(node2);
        Pointer[node2]->addElem(node1);
    }


    void showNeighbours()
    {
        int tab[100];
        int z = 0;
        LinkedListElem * tmp;
        for(int x=0;x<LiczbaWierzchlokow;x++)
        {
            cout << "Wezel " << x << " - sasiedzi: ";
            tmp = Pointer[x]->Head;
            while(tmp != nullptr)
            {
                cout << tmp->Value << " ";
                tmp = tmp->next;
            }
            cout << endl;
        }
    }


};
int main()
{
    int l_wierzcholkow = 5;
    EdgeListGraph Graph(l_wierzcholkow);
    Graph.addEdge(0,1);
    Graph.addEdge(2,1);
    Graph.addEdge(4,2);
    Graph.addEdge(3,1);
    Graph.addEdge(2,3);
    Graph.showNeighbours();
}
