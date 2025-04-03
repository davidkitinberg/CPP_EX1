// davidkitinberg@gmail.com


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph/Graph.h"
#include "DataStructures/Queue.h"
#include "DataStructures/PriorityQueue.h"
#include "DataStructures/UnionFind.h"
#include "Algorithms/header/BFS.h"
#include "Algorithms/header/DFS.h"
#include "Algorithms/header/Dijkstra.h"
#include "Algorithms/header/Kruskal.h"
#include "Algorithms/header/Prim.h"

using namespace graph;
using namespace ds;
using namespace algo;

TEST_CASE("Test Graph") {
    Graph g(5);
  
    // Assign adjecent vertices 1,2,3,4 to vertex 0
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    // Assign adjecent vertices 2,3,4 to vertex 1
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    // Assign adjecent vertices 3,4 to vertex 2
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    // Assign adjecent verticle 4 to vertex 3
    g.addEdge(3, 4);
    // Assign adjecent verticle 4 to vertex 3
    CHECK(g.edgeExists(0, 1));
    CHECK(g.edgeExists(3, 4));
    CHECK(g.edgeExists(1, 0));  // Check that we are getting the edge also in the adjecency list of vertex 1

    g.print_graph("Original graph before removing edge (3,4)");

    // Check throws correction
    CHECK_THROWS(g.addEdge(2,3), "Edge already exists");
    CHECK_THROWS(g.removeEdge(6,5),"Edge does not exist");

    // Check remove edge correctness
    g.removeEdge(3,4);
    CHECK_FALSE(g.edgeExists(3,4));
    CHECK_FALSE(g.edgeExists(4,3));

    printf("\n");
    g.print_graph("Original graph after removing edge (3,4)");

  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("BFS test") {
    Graph g(6);  // Create a graph with 6 nodes: 0 to 5

    // Edges (undirected)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Check throws correction
    SUBCASE("BFS Exceptions") {
        Graph g(3);
        g.addEdge(0, 1);
    
        // Invalid source: -1
        CHECK_THROWS(BFS::buildBFSTree(g, -1),"Source vertex out of range");
    
        // Invalid source: 3 (out of bounds)
        CHECK_THROWS(BFS::buildBFSTree(g, 3),"Source vertex out of range");
    }

    // Build BFS tree from source 0
    Graph tree = BFS::buildBFSTree(g, 0);


    // Check that the algorithm kept the expected edges
    CHECK(tree.edgeExists(0, 1));
    CHECK(tree.edgeExists(0, 2));
    CHECK(tree.edgeExists(1, 3));
    CHECK(tree.edgeExists(1, 4));
    CHECK(tree.edgeExists(2, 5));

    printf("\n");
    tree.print_graph("BFS");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("DFS test") {
    Graph g(6);  // Create a graph with 6 nodes: 0 to 5

    // Edges (undirected)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    SUBCASE("DFS exceptions") {
        Graph g(3);
        g.addEdge(0, 1);
    
        // Invalid source: -1
        CHECK_THROWS(DFS::buildDFSTree(g, -1),"Source vertex out of range");
    
        // Invalid source: 3 (out of bounds)
        CHECK_THROWS(DFS::buildDFSTree(g, 3),"Source vertex out of range");
    }

    // Build DFS tree from source 0
    Graph tree = DFS::buildDFSTree(g, 0);

    // Check that the algorithm kept the expected edges
    CHECK(tree.edgeExists(0, 1));
    CHECK(tree.edgeExists(0, 2));
    CHECK(tree.edgeExists(1, 3));
    CHECK(tree.edgeExists(1, 4));
    CHECK(tree.edgeExists(2, 5));

    printf("\n");
    tree.print_graph("DFS");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Kruskal test") {
    Graph g(5);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 5);

    Graph mst = Kruskal::buildMST(g);

    CHECK(mst.edgeExists(0, 1));
    CHECK(mst.edgeExists(1, 2));
    CHECK(mst.edgeExists(2, 3));
    CHECK(mst.edgeExists(3, 4));

    // The MST must contain exactly 4 edges for 5 vertices
    int edgeCount = 0;
    for (int i = 0; i < mst.getNumVertices(); ++i) {
        const Graph::EdgeNode* curr = mst.getAdjacencyList()[i];
        while (curr) {
            ++edgeCount;
            curr = curr->next;
        }
    }

    CHECK(edgeCount / 2 == 4); // Each edge counted twice (undirected graph)

    printf("\n");
    mst.print_graph("Kruskal");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Dijkstra test") {

    SUBCASE("Negative edge weight") {
        Graph g(4);

        g.addEdge(0,1,-2);
        g.addEdge(0, 2, 4);
        g.addEdge(1, 3, 7);

        CHECK_THROWS(Dijkstra::buildDijkstraTree(g,0),"Dijkstra does not work on negetive edge weights");

    }

    SUBCASE("Dijkstra exceptions") {
        Graph g(4);

        g.addEdge(0,1,1);
        g.addEdge(0, 2, 4);
        g.addEdge(1, 3, 7);

        CHECK_THROWS(Dijkstra::buildDijkstraTree(g,-1),"Source vertex out of range");

    }

    SUBCASE("Validate tree structure") {

        Graph g(5);

        // Make a graph for test
        g.addEdge(0, 1, 2);
        g.addEdge(0, 2, 4);
        g.addEdge(1, 3, 7);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 4, 3);

        Graph tree = Dijkstra::buildDijkstraTree(g, 0);
        
        printf("\n");
        tree.print_graph("Dijkstra");

        CHECK(tree.edgeExists(0, 1));  // distance: 2
        bool isWeight2 = false;
        const graph::Graph::EdgeNode* adjList0 = tree.getAdjacencyList()[0];
        while(adjList0) {
            if(adjList0->weight == 2 && adjList0->neighbor == 1)
            {
                isWeight2 = true;
                break;
            } 
            adjList0 = adjList0->next;
        }
        CHECK(isWeight2);

        CHECK(tree.edgeExists(0, 2));  // distance: 4
        bool isWeight4 = false;
        const graph::Graph::EdgeNode* adjList1 = tree.getAdjacencyList()[0];
        while(adjList1) {
            if(adjList1->weight == 4 && adjList1->neighbor == 2)
            {
                isWeight4 = true;
                break;
            } 
            adjList1 = adjList1->next;
        }
        CHECK(isWeight4);


        CHECK(tree.edgeExists(2, 3));  // distance: 5
        bool isWeight5 = false;
        const graph::Graph::EdgeNode* adjList2 = tree.getAdjacencyList()[2];
        while(adjList2) {
            if(adjList2->weight == 1 && adjList2->neighbor == 3)
            {
                isWeight5 = true;
                break;
            } 
            adjList2 = adjList2->next;
        }
        if (!isWeight5) {
            const graph::Graph::EdgeNode* adjList3 = tree.getAdjacencyList()[3];
            while(adjList3) {
                if(adjList3->weight == 5 && adjList3->neighbor == 2)
                {
                    isWeight5 = true;
                    break;
                } 
                adjList3 = adjList3->next;
            }
        }
        CHECK(isWeight5);


        CHECK(tree.edgeExists(3, 4));  // distance: 8
        bool isWeight8 = false;
        const graph::Graph::EdgeNode* adjList4 = tree.getAdjacencyList()[3];
        while(adjList4) {
            if(adjList4->weight == 3 && adjList4->neighbor == 4)
            {
                isWeight8 = true;
                break;
            } 
            adjList4 = adjList4->next;
        }
        if (!isWeight8) {
            const graph::Graph::EdgeNode* adjList5 = tree.getAdjacencyList()[4];
            while(adjList5) {
                if(adjList5->weight == 8 && adjList5->neighbor == 3)
                {
                    isWeight8 = true;
                    break;
                } 
                adjList5 = adjList5->next;
            }
        }
        CHECK(isWeight8);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Prim test") {
    Graph g(4);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 3);

    Graph mst = Prim::buildMST(g, 0);

    printf("\n");
    mst.print_graph("Prim");

    CHECK(mst.edgeExists(0, 1));
    CHECK(mst.edgeExists(1, 2));
    CHECK(mst.edgeExists(2, 3));

    int edgeCount = 0;
    for (int i = 0; i < mst.getNumVertices(); ++i) {
        const Graph::EdgeNode* curr = mst.getAdjacencyList()[i];
        while (curr) {
            ++edgeCount;
            curr = curr->next;
        }
    }

    CHECK(edgeCount / 2 == 3); // Each edge counted twice

    SUBCASE("Prim exceptions") {
        Graph g1(4);

        g1.addEdge(0, 1, 1);
        g1.addEdge(0, 2, 4);
        g1.addEdge(1, 2, 2);
        g1.addEdge(1, 3, 5);
        g1.addEdge(2, 3, 3);

        CHECK_THROWS(Prim::buildMST(g1,-1),"Invalid start vertex");

        CHECK_THROWS(Prim::buildMST(g1,5),"Invalid start vertex");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Priority Queue") {
    PriorityQueue pq(5);

    CHECK(pq.isEmpty());

    pq.insert(0, 10);
    pq.insert(1, 5);
    pq.insert(2, 7);

    CHECK_FALSE(pq.isEmpty());
    CHECK(pq.contains(1));
    CHECK(pq.contains(2));
    CHECK(pq.getDistance(1) == 5);
    CHECK(pq.getDistance(2) == 7);

    // Test decreaseKey
    pq.decreaseKey(2, 2);
    CHECK(pq.getDistance(2) == 2);

    // Test extractMin (should now return 2)
    int minVertex = pq.extractMin();
    CHECK(minVertex == 2);
    CHECK_FALSE(pq.contains(2));

    // Extract next minimum (should be 1)
    minVertex = pq.extractMin();
    CHECK(minVertex == 1);

    // Extract final (should be 0)
    minVertex = pq.extractMin();
    CHECK(minVertex == 0);

    // Should now be empty
    CHECK(pq.isEmpty());

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Queue") {
    Queue q(3);
  
    CHECK(q.isEmpty());
    CHECK_FALSE(q.isFull());
  
    // Enqueue elements
    CHECK(q.enqueue(10) == 0);
    CHECK(q.enqueue(20) == 0);
    // Check new size
    CHECK(q.size() == 2);
  
    CHECK_FALSE(q.isEmpty());
  
    // Check peek function functinality
    CHECK(q.peek() == 10);
    // Dequeue elements
    CHECK(q.dequeue() == 10);
    // Check peek function functinality #2
    CHECK(q.peek() == 20);
  
    // Dequeue elements and check if empty
    CHECK(q.dequeue() == 20);
    CHECK(q.isEmpty());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Union-Find") {
    UnionFind uf(6);

    // Initially, every node should be its own parent
    for (int i = 0; i < 6; ++i) {
        CHECK(uf.find(i) == i);
    }

    // Connect 0 and 1
    uf.unite(0, 1);
    CHECK(uf.connected(0, 1));
    CHECK(uf.find(0) == uf.find(1));

    // Connect 2 and 3
    uf.unite(2, 3);
    CHECK(uf.connected(2, 3));
    CHECK(uf.find(2) == uf.find(3));

    // Connect 1 and 2 -> this merges the two connected components (0-1) and (2-3)
    uf.unite(1, 2);
    CHECK(uf.connected(0, 3));
    CHECK(uf.find(0) == uf.find(3));

    // 4 and 5 should not be connected yet
    CHECK_FALSE(uf.connected(0, 4));
    CHECK_FALSE(uf.connected(3, 5));
    CHECK_FALSE(uf.connected(4, 5));

    // Connect 4 and 5
    uf.unite(4, 5);
    CHECK(uf.connected(4, 5));

    SUBCASE("Union-Find exceptions") {

    CHECK_THROWS(uf.find(-1), "Index out of range");
    CHECK_THROWS(uf.find(6), "Index out of range");

    }
}
