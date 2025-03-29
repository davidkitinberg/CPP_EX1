// davidkitinberg@gmail.com

#include <iostream>
#include "Graph/Graph.h"
#include "Algorithms/header/BFS.h"
#include "Algorithms/header/DFS.h"
#include "Algorithms/header/Dijkstra.h"
#include "Algorithms/header/Kruskal.h"
#include "Algorithms/header/Prim.h"

using namespace std;
using namespace graph;
using namespace algo;

void printTree(const int* parent, int numVertices, const string& algorithmName) {
    cout << "\n" << algorithmName << " Tree (parent array):\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << " <- " << parent[i] << endl;
    }
}

int main() {
    Graph g(6);

    // Build a sample graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 4, 3);
    g.addEdge(4, 3, 4);
    g.addEdge(3, 5, 11);

    cout << "Original Graph:\n";
    g.print_graph();

    int source = 0;

    // Run BFS
    int* bfsTree = BFS::buildBFSTree(g, source);
    printTree(bfsTree, g.getNumVertices(), "BFS");
    delete[] bfsTree;

    // Run DFS
    int* dfsTree = DFS::buildDFSTree(g, source);
    printTree(dfsTree, g.getNumVertices(), "DFS");
    delete[] dfsTree;

    // Run Dijkstra
    Graph dijkstraTree = Dijkstra::buildDijkstraTree(g, source);
    cout << "\nDijkstra Shortest-Path Tree:\n";
    dijkstraTree.print_graph();

    // Run Kruskal
    Graph kruskalTree = Kruskal::buildMST(g);
    cout << "\nKruskal MST:\n";
    kruskalTree.print_graph();

    // Run Prim
    Graph primTree = Prim::buildMST(g);
    cout << "\nPrim MST:\n";
    primTree.print_graph();

    return 0;
}
