#include <iostream>
#include "graph.hh"
#include "graph_matrix.hh"
using namespace std;

int main()
{
    // GraphMatrix graphmatrix(5);
    // graphmatrix.addEdge(5,7);
    // graphmatrix.addEdge(1,2);
    // graphmatrix.addEdge(2,7);
    // graphmatrix.showNeighbours();
    // cout << endl;
    Graph Graph;
    Graph.addNode(0);
    Graph.addNode(2);
    Graph.addNode(3);
    Graph.addEdge(0,2,5);
    Graph.addEdge(2,3,5);
    Graph.addEdge(8,4,10);
    Graph.ShowNeighbours();
    cout << endl;
    Graph.removeNode(3);
    Graph.removeEdge(0,2,5);
    Graph.ShowNeighbours();
}
