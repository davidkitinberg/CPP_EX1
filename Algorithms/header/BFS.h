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
        static graph::Graph buildBFSTree(const graph::Graph& g, int source);
    };
}

#endif
