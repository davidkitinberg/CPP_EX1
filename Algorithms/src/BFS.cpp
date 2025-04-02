// davidkitinberg@gmail.com


#include "../header/BFS.h"
#include "../../DataStructures/Queue.h"
#include <stdexcept>

using namespace graph;
using namespace ds;

namespace algo {

    Graph BFS::buildBFSTree(const Graph& g, int source) {
        // Get number of vertices
        int numVertices = g.getNumVertices();

        // Validate the source vertex
        if (source < 0 || source >= numVertices) {
            throw std::invalid_argument("Source vertex out of range.");
        }

        // Allocate visited and parent arrays
        bool* visited = new bool[numVertices];
        int* parent = new int[numVertices];

        // Initialize parent and visited parameters for BFS
        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
            parent[i] = -1;  // -1 means "no parent" (used for the root)
        }

        // Initialize queue
        Queue q(numVertices);

        // Start from the source
        visited[source] = true;
        q.enqueue(source);

        while (!q.isEmpty()) {
            int current = q.dequeue();

            // Traverse neighbors using the Graph's adjacency list
            const Graph::EdgeNode* neighbor = g.getAdjacencyList()[current];
            while (neighbor != nullptr) // Visit all neighbors of the current Node
            {
                int v = neighbor->neighbor;

                if (!visited[v]) 
                {
                    visited[v] = true;
                    parent[v] = current;
                    q.enqueue(v);
                }

                neighbor = neighbor->next;
            }
        }

        // Construct the BFS tree as a new Graph
        Graph tree(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            if (parent[i] != -1) {
                tree.addEdge(parent[i], i, 1); // Default weight of 1
            }
        }

        // Free memory
        delete[] visited;
        delete[] parent;

        return tree;
    }

}
