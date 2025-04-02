// davidkitinberg@gmail.com


#include "../header/Prim.h"
#include "../../DataStructures/PriorityQueue.h"
#include <climits>
#include <stdexcept>

using namespace graph;
using namespace ds;

namespace algo {

Graph Prim::buildMST(const Graph& g, int startVertex) {
    int n = g.getNumVertices(); // Get |v|

    // Check bounds of startVertex
    if (startVertex < 0 || startVertex >= n) {
        throw std::invalid_argument("Invalid start vertex.");
    }

    // Initialize helper arrays
    bool* inMST = new bool[n]; // Tracks which vertices are already in the MST
    int* parent = new int[n]; // Stores the parent of each vertex in the MST
    int* key = new int[n]; // Stores the minimum weight to reach each vertex

    // Initialize arrays values for the start of the algorithm
    for (int i = 0; i < n; ++i) 
    {
        inMST[i] = false;
        parent[i] = -1;
        key[i] = INT_MAX;
    }

    key[startVertex] = 0; // Initialize the source/start vertex weight to 0 to be picked first by pq
    PriorityQueue pq(n);
    pq.insert(startVertex, key[startVertex]);

    // Run until MST contains all vertices
    while (!pq.isEmpty()) 
    {
        int min_key_vertex = pq.extractMin(); // Pick vertex u with the smallest key value
        inMST[min_key_vertex] = true; // Include u in MST

        const Graph::EdgeNode* neighbor_list = g.getAdjacencyList()[min_key_vertex]; // Get all neighbors for min_key_vertex
        while (neighbor_list) // Go through all its neighbors
        {
            // Extract values from curr neighbor of min_key_vertex
            int v = neighbor_list->neighbor; 
            int weight = neighbor_list->weight;

            
            // If v is not in MST and the edge between v and min_key_vertex is 'cheaper' than current key[v]
            if (!inMST[v] && weight < key[v]) 
            {
                key[v] = weight; // Update the key to this new smaller weight
                parent[v] = min_key_vertex; // Update parent to v

                // If already in the pq, update v's key
                if (pq.contains(v)) 
                {
                    pq.decreaseKey(v, key[v]);
                } 
                else // If v not in the pq, insert it
                {
                    pq.insert(v, key[v]);
                }
            }

            neighbor_list = neighbor_list->next;
        }
    }

    // Build MST
    Graph mst(n);
    for (int i = 0; i < n; ++i) 
    {
        if (parent[i] != -1) 
        {
            mst.addEdge(i, parent[i], key[i]); // Add edge between vertex and its parent
        }
    }

    // Free memory
    delete[] inMST;
    delete[] parent;
    delete[] key;

    return mst;
}

}
