// davidkitinberg@gmail.com

#include "../header/BFS.h"
#include "../../DataStructures/Queue.h"
#include <stdexcept>

using namespace graph;
using namespace ds;

namespace algo {

    int* BFS::buildBFSTree(const Graph& g, int source) {
        // Get number of vertices
        int numVertices = g.getNumVertices();  // ← we'll need to expose this method in your Graph class!

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
            while (neighbor != nullptr) {
                int v = neighbor->neighbor;

                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = current;
                    q.enqueue(v);
                }

                neighbor = neighbor->next;
            }
        }

        delete[] visited;
        return parent;  // The caller must delete[] it
    }

}
