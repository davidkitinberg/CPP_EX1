// davidkitinberg@gmail.com

#include "../header/DFS.h"
#include <stdexcept>

using namespace graph;

namespace algo {

    // Helper recursive function
    static void dfs_visit(const Graph& g, int current, bool visited[], int parent[]) {
        visited[current] = true;

        const Graph::EdgeNode* neighbor = g.getAdjacencyList()[current];
        while (neighbor != nullptr) {
            int v = neighbor->neighbor;
            if (!visited[v]) {
                parent[v] = current;
                dfs_visit(g, v, visited, parent);
            }
            neighbor = neighbor->next;
        }
    }

    int* DFS::buildDFSTree(const Graph& g, int source) {
        int numVertices = g.getNumVertices();

        if (source < 0 || source >= numVertices) {
            throw std::invalid_argument("Source vertex out of range.");
        }

        // Allocate and initialize arrays
        bool* visited = new bool[numVertices];
        int* parent = new int[numVertices];

        // Initialize parent and visited parameters for DFS
        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
            parent[i] = -1;
        }

        // Start DFS
        dfs_visit(g, source, visited, parent);

        delete[] visited;
        return parent;
    }

}
