// davidkitinberg@gmail.com


#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../../Graph/Graph.h"
#include "../../DataStructures/PriorityQueue.h"

namespace algo {

class Dijkstra {
    public:
        static graph::Graph buildDijkstraTree(const graph::Graph& g, int source);
};



}


#endif