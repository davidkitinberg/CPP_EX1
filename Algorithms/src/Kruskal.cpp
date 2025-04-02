// davidkitinberg@gmail.com


#include "../header/Kruskal.h"
#include "../../DataStructures/UnionFind.h"
#include <climits>

using namespace graph;
using namespace ds;

namespace algo {

    // Helper structure to store an edge with source, destination, and weight
    struct EdgeData {
        int src;
        int dest;
        int weight;
    };

    // Classic quicksort to sort edges by weight (ascending order)
    void quicksort(EdgeData arr[], int low, int high) {
        if (low < high) 
        {
            // Choose pivot (last element's weight)
            int pivot = arr[high].weight;
            int i = low - 1;

            // Partition the arr
            for (int j = low; j < high; ++j) 
            {
                if (arr[j].weight < pivot) 
                {
                    ++i;
                    // Swap arr[i] and arr[j]
                    EdgeData temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }

            // Place pivot in its correct position
            EdgeData temp = arr[i + 1];
            arr[i + 1] = arr[high];
            arr[high] = temp;

            // Index where the pivot is now correctly placed
            int pi = i + 1;

            quicksort(arr, low, pi - 1); // Sort elements before the pivot
            quicksort(arr, pi + 1, high); // Sort elements after the pivot
        }
    }


    Graph Kruskal::buildMST(const Graph& g) {

        int n = g.getNumVertices(); // Get |v|
        Graph mst(n);  // Final MST graph to return

        // Count all edges in the graph
        // We only count one direction for undirected edges (i < neighbor)
        int edgeCount = 0;
        graph::Graph::EdgeNode** adj = g.getAdjacencyList(); // Arr of linked list (of neighbors)
        for (int i = 0; i < n; ++i) 
        {
            const graph::Graph::EdgeNode* neighbors_list = adj[i];
            while (neighbors_list) // Go through all neighbors of index i
            {
                if (i < neighbors_list->neighbor)
                {
                    edgeCount++;  // Avoid double counting
                } 
                neighbors_list = neighbors_list->next;
            }
        }

        // Copy all edges into an array of EdgeData struct
        EdgeData* edges = new EdgeData[edgeCount]; // Memory allocation with the size of the edges in the graph (no dupes)
        int idx = 0;
        for (int i = 0; i < n; ++i) // Go through all neighbors of index i -> all the graph eventually
        {
            const graph::Graph::EdgeNode* neighbors_list2 = adj[i]; 
            while (neighbors_list2) {
                if (i < neighbors_list2->neighbor) {  // Only store one direction
                    edges[idx].src = i;
                    edges[idx].dest = neighbors_list2->neighbor;
                    edges[idx].weight = neighbors_list2->weight;
                    idx++;
                }
                neighbors_list2 = neighbors_list2->next;
            }
        }

        // Sort edges by weight
        quicksort(edges, 0, edgeCount - 1);

        // Use Union-Find data structure to pick edges without forming cycles
        UnionFind uf(n);  // Each node is its own connected component initially

        for (int i = 0; i < edgeCount; ++i) 
        {
            int u = edges[i].src;
            int v = edges[i].dest;

            // If u and v are in different connected component, adding this edge won't form a cycle
            if (uf.find(u) != uf.find(v)) 
            {
                uf.unite(u, v);  // Union their sets
                mst.addEdge(u, v, edges[i].weight);  // Add edge to the MST
            }
        }

        // Free memory
        delete[] edges;

        
        return mst;
    }

}
