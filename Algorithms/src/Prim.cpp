// davidkitinberg@gmail.com


#include "../header/Prim.h"
#include "../../DataStructures/PriorityQueue.h"
#include <climits>
#include <stdexcept>

using namespace graph;
using namespace ds;

namespace algo {

Graph Prim::buildMST(const Graph& g, int startVertex) {
    int n = g.getNumVertices();

    if (startVertex < 0 || startVertex >= n) {
        throw std::invalid_argument("Invalid start vertex.");
    }

    bool* inMST = new bool[n];
    int* parent = new int[n];
    int* key = new int[n];

    for (int i = 0; i < n; ++i) {
        inMST[i] = false;
        parent[i] = -1;
        key[i] = INT_MAX;
    }

    key[startVertex] = 0;
    PriorityQueue pq(n);
    pq.insert(startVertex, key[startVertex]);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        inMST[u] = true;

        const Graph::EdgeNode* neighbor = g.getAdjacencyList()[u];
        while (neighbor) {
            int v = neighbor->neighbor;
            int weight = neighbor->weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                if (pq.contains(v)) {
                    pq.decreaseKey(v, key[v]);
                } else {
                    pq.insert(v, key[v]);
                }
            }

            neighbor = neighbor->next;
        }
    }

    // Build MST
    Graph mst(n);
    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
            mst.addEdge(i, parent[i], key[i]);
        }
    }

    delete[] inMST;
    delete[] parent;
    delete[] key;

    return mst;
}

}
