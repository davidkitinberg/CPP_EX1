// davidkitinberg@gmail.com

//#include "Test_Queue.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // Makes doctest run this test without main
#include "../Graph/Graph.h"
#include "../doctest.h"

using namespace graph;

TEST_CASE("Test Graph operations") {
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
//  g.addEdge(4, 5);
  CHECK(g.edgeExists(0, 1));
  CHECK(g.edgeExists(3, 4));
  CHECK_FALSE(g.edgeExists(1, 0));  // still undirected, but you may want to test both directions
}

