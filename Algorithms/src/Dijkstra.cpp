// davidkitinberg@gmail.com


#include "../header/Dijkstra.h"
#include <stdexcept>
#include <climits>

using namespace graph;
using namespace ds;

namespace algo {

Graph Dijkstra::buildDijkstraTree(const Graph& g, int source) {
    int numVertices = g.getNumVertices(); // Get |v|

    // Check bounds
    if (source < 0 || source >= numVertices) {
        throw std::invalid_argument("Source vertex out of range.");
    }

    // Memory allocation for the dijkstra algorithm
    int* distance = new int[numVertices];
    int* parent = new int[numVertices];
    PriorityQueue pq(numVertices);

    // Initialization
    for (int i = 0; i < numVertices; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // Source vertex initialization and insertion to pq
    distance[source] = 0;
    pq.insert(source, 0);

    while (!pq.isEmpty()) 
    {
        int currentVertex = pq.extractMin();

        // Get the linked list (all the neighbors) for current vertex
        const Graph::EdgeNode* neighbor_list = g.getAdjacencyList()[currentVertex];
        while (neighbor_list) { // loop through all neighbors
            int neighborVertex = neighbor_list->neighbor; // neighbor node index (ID)
            int edgeWeight = neighbor_list->weight; // Weight of the edge from current to neighbor

            if (edgeWeight < 0) // Exception on negetive edges
            {
                throw std::invalid_argument("Dijkstra does not work on negetive edge weights.");
            }

            // this is the relax procedure in the algorithm
            if (distance[currentVertex] + edgeWeight < distance[neighborVertex]) // if d[u] (dist from source to u vertex) + w (weight/dist of the curr neighbor's edge we look into now) < d[v] (neighbor dist from source)
            { 
                distance[neighborVertex] = distance[currentVertex] + edgeWeight; // Update the dist --> relax
                parent[neighborVertex] = currentVertex; // Update parent

                if (pq.contains(neighborVertex)) 
                {
                    pq.decreaseKey(neighborVertex, distance[neighborVertex]); // Update the dist in pq
                } 
                else 
                {
                    pq.insert(neighborVertex, distance[neighborVertex]); // Insert with correct value
                }
            }

            neighbor_list = neighbor_list->next; // Go to next neighbor of u
        }
    }

    // Build the shortest-path tree from Dijkstra
    Graph tree(numVertices);
    for (int vertex = 0; vertex < numVertices; ++vertex) 
    {
        if (parent[vertex] != -1) // Check if vertex has a valid parent
        {
            int parentVertex = parent[vertex];

            // Find the real weight from parentVertex to vertex in the original graph
            const Graph::EdgeNode* neighbor_list2 = g.getAdjacencyList()[parentVertex];
            int realWeight = -1;
            while (neighbor_list2) // Go through all neighbors
            {
                if (neighbor_list2->neighbor == vertex) 
                {
                    realWeight = neighbor_list2->weight;
                    break;
                }
                neighbor_list2 = neighbor_list2->next;
            }

            if (realWeight == -1) {
                throw std::runtime_error("Edge not found in original graph");
            }

            tree.addEdge(parentVertex, vertex, realWeight);
        }
    }

    // Free memory
    delete[] distance;
    delete[] parent;

    return tree;
}

}
