// davidkitinberg@gmail.com


#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <cstdlib>
#include "../../DataStructures/Queue.h"
#include "../../Graph/Graph.h"

namespace algo {

    class BFS {
    public:
        // Returns a BFS tree as a parent array.
        // parent[v] = u means u is the parent of v in the BFS tree.
        // parent[source] = -1
        // Caller must delete[] the returned array after use.
        static int* buildBFSTree(const graph::Graph& g, int source);
    };
}

#endif //BFS_H
