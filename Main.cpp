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

// Helper method to construct graph
Graph buildSampleGraph() {
    Graph g(6);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 4, 3);
    g.addEdge(4, 3, 4);
    g.addEdge(3, 5, 11);

    return g;
}

int main() {
    int source = 0;

    // Original Graph
    Graph originalGraph = buildSampleGraph();
    originalGraph.print_graph("Original graph");
    printf("\n");

    // Run BFS
    Graph bfsInput = buildSampleGraph();
    Graph bfsTree = BFS::buildBFSTree(bfsInput, source);
    bfsTree.print_graph("BFS");
    printf("\n");

    // Run DFS
    Graph dfsInput = buildSampleGraph();
    Graph dfsTree = DFS::buildDFSTree(dfsInput, source);
    dfsTree.print_graph("DFS");
    printf("\n");

    // Run Dijkstra
    Graph dijkstraInput = buildSampleGraph();
    Graph dijkstraTree = Dijkstra::buildDijkstraTree(dijkstraInput, source);
    dijkstraTree.print_graph("Dijkstra");
    printf("\n");

    // Run Kruskal
    Graph kruskalInput = buildSampleGraph();
    Graph kruskalTree = Kruskal::buildMST(kruskalInput);
    kruskalTree.print_graph("Kruskal");
    printf("\n");

    // Run Prim
    Graph primInput = buildSampleGraph();
    Graph primTree = Prim::buildMST(primInput);
    primTree.print_graph("Prim");
    printf("\n");

    return 0;
}
