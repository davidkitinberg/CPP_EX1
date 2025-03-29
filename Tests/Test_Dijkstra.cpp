// davidkitinberg@gmail.com


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../Graph/Graph.h"
#include "../Algorithms/header/Dijkstra.h"

using namespace graph;
using namespace algo;

TEST_CASE("Dijkstra test") {
    Graph g(5);

    // Make a graph for test
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 3);

    Graph tree = Dijkstra::buildDijkstraTree(g, 0);

    // Validate tree structure
    CHECK(tree.edgeExists(0, 1));  // distance: 2
    bool isWeight2 = false;
    const graph::Graph::EdgeNode* adjList = tree.getAdjacencyList()[0];
    while(adjList) {
        if(adjList->weight == 2 && adjList->neighbor == 1)
        {
            isWeight2 = true;
            break;
        } 
        adjList = adjList->next;
    }
    CHECK(isWeight2);


    CHECK(tree.edgeExists(0, 2));  // distance: 4
    bool isWeight4 = false;
    const graph::Graph::EdgeNode* adjList = tree.getAdjacencyList()[0];
    while(adjList) {
        if(adjList->weight == 4 && adjList->neighbor == 2)
        {
            isWeight4 = true;
            break;
        } 
        adjList = adjList->next;
    }
    CHECK(isWeight4);


    CHECK(tree.edgeExists(2, 3));  // distance: 5
    bool isWeight5 = false;
    const graph::Graph::EdgeNode* adjList = tree.getAdjacencyList()[2];
    while(adjList) {
        if(adjList->weight == 5 && adjList->neighbor == 3)
        {
            isWeight5 = true;
            break;
        } 
        adjList = adjList->next;
    }
    CHECK(isWeight5);


    CHECK(tree.edgeExists(3, 4));  // distance: 8
    bool isWeight8 = false;
    const graph::Graph::EdgeNode* adjList = tree.getAdjacencyList()[3];
    while(adjList) {
        if(adjList->weight == 8 && adjList->neighbor == 4)
        {
            isWeight8 = true;
            break;
        } 
        adjList = adjList->next;
    }
    CHECK(isWeight8);

}
