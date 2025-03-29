// davidkitinberg@gmail.com


#include "../header/Kruskal.h"
#include "../../DataStructures/UnionFind.h"
#include <climits>

using namespace graph;
using namespace ds;

namespace algo {

    struct EdgeData {
        int src;
        int dest;
        int weight;
    };

    // Quicksort to sort edges by weight
    void quicksort(EdgeData arr[], int low, int high) {
        if (low < high) {
            // Partitioning index
            int pivot = arr[high].weight;
            int i = low - 1;

            for (int j = low; j < high; ++j) {
                if (arr[j].weight < pivot) {
                    ++i;
                    EdgeData temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }

            // Swap pivot to correct place
            EdgeData temp = arr[i + 1];
            arr[i + 1] = arr[high];
            arr[high] = temp;

            int pi = i + 1;
            quicksort(arr, low, pi - 1);
            quicksort(arr, pi + 1, high);
        }
    }


    Graph Kruskal::buildMST(const Graph& g) {
        int n = g.getNumVertices();
        Graph mst(n);

        // Count all edges
        int edgeCount = 0;
        graph::Graph::EdgeNode** adj = g.getAdjacencyList();
        for (int i = 0; i < n; ++i) {
            const graph::Graph::EdgeNode* curr = adj[i];
            while (curr) {
                if (i < curr->neighbor) edgeCount++;  // Count one direction to avoid double-counting
                curr = curr->next;
            }
        }

        // Copy edges to a EdgeData array
        EdgeData* edges = new EdgeData[edgeCount];
        int idx = 0;
        for (int i = 0; i < n; ++i) {
            const graph::Graph::EdgeNode* curr = adj[i];
            while (curr) {
                if (i < curr->neighbor) {
                    edges[idx].src = i;
                    edges[idx].dest = curr->neighbor;
                    edges[idx].weight = curr->weight;
                    idx++;
                }
                curr = curr->next;
            }
        }

        // Sort edges by weight
        quicksort(edges, 0, edgeCount - 1);

        // Kruskal's algorithm using Union-Find
        UnionFind uf(n);
        for (int i = 0; i < edgeCount; ++i) {
            int u = edges[i].src;
            int v = edges[i].dest;
            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                mst.addEdge(u, v, edges[i].weight);
            }
        }

        delete[] edges;
        return mst;
    }

}
