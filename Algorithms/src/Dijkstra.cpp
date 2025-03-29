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

    int* distance = new int[numVertices];
    int* parent = new int[numVertices];
    PriorityQueue pq(numVertices);

    // Initialization
    for (int i = 0; i < numVertices; ++i) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // Source vertec initialization and insertion to pq
    distance[source] = 0;
    pq.insert(source, 0);

    while (!pq.isEmpty()) {
        int currentVertex = pq.extractMin();

        // Get the linked list (all the neighbors) for current vertex
        const Graph::EdgeNode* neighbor = g.getAdjacencyList()[currentVertex];
        while (neighbor) { // loop through all neighbors
            int neighborVertex = neighbor->neighbor; // neighbor node index (ID)
            int edgeWeight = neighbor->weight; // Weight of the edge from current to neighbor

            if (pq.contains(neighborVertex) == false) { // If the pq don't have this vertex we insert it with its dist
                pq.insert(neighborVertex, distance[neighborVertex]);
            }

            // this is the relax procedure in the algorithm
            if (distance[currentVertex] + edgeWeight < distance[neighborVertex]) // if d[u] (dist from source to u vertex) + w (weight/dist of the curr neighbor's edge we look into now) < d[v] (neighbor dist from source)
            { 
                distance[neighborVertex] = distance[currentVertex] + edgeWeight; // Update the dist --> relax
                parent[neighborVertex] = currentVertex; // Update parent
                pq.decreaseKey(neighborVertex, distance[neighborVertex]); // Update the dist in pq
            }

            neighbor = neighbor->next; // Go to next neighbor of u
        }
    }

    // Build the shortest-path tree
    Graph tree(numVertices);
    for (int vertex = 0; vertex < numVertices; ++vertex) {
        if (parent[vertex] != -1) {
            int parentVertex = parent[vertex];
            int edgeWeight = distance[vertex] - distance[parentVertex];  // Calculate actual weight from parent to child
            tree.addEdge(parentVertex, vertex, edgeWeight);  // You can call it only once because tree is undirected
        }
    }

    delete[] distance;
    delete[] parent;

    return tree;
}

}
