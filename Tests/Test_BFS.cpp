// davidkitinberg@gmail.com


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../Graph/Graph.h"
#include "../Algorithms/header/BFS.h"

using namespace graph;
using namespace algo;

TEST_CASE("BFS builds correct tree") {
    Graph g(6);  // Create a graph with 6 nodes: 0 to 5

    // Edges (undirected)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Build BFS tree from source 0
    int* parent = BFS::buildBFSTree(g, 0);

    // The expected BFS tree (parents)
    // Node:     0  1  2  3  4  5
    // Parent:  -1  0  0  1  1  2
    CHECK(parent[0] == -1);  // root
    CHECK(parent[1] == 0);
    CHECK(parent[2] == 0);
    CHECK(parent[3] == 1);
    CHECK(parent[4] == 1);
    CHECK(parent[5] == 2);

    delete[] parent;
}

TEST_CASE("BFS throws on invalid source") {
    Graph g(3);
    g.addEdge(0, 1);

    int* tree = nullptr;

    // Invalid source: -1
    CHECK_THROWS(tree = BFS::buildBFSTree(g, -1));

    // Invalid source: 3 (out of bounds)
    CHECK_THROWS(tree = BFS::buildBFSTree(g, 3));
}
