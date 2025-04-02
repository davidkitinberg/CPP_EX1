// davidkitinberg@gmail.com


#include "../header/DFS.h"
#include "../../Graph/Graph.h"
#include <stdexcept>

using namespace graph;

namespace algo {

    // Helper recursive function
    static void dfs_visit(const Graph& g, int current, bool visited[], int parent[]) {
        visited[current] = true;

        const Graph::EdgeNode* neighbor_list = g.getAdjacencyList()[current]; // Get neighbors list of current
        while (neighbor_list != nullptr) // Visit all current's neighbors
        {
            int v = neighbor_list->neighbor; // Vertex's index
            if (!visited[v]) // If not visited already
            {
                parent[v] = current; // Set parent
                dfs_visit(g, v, visited, parent); // Recursive call
            }
            neighbor_list = neighbor_list->next; // Do next neighbor
        }
    }

    Graph DFS::buildDFSTree(const Graph& g, int source) {
        // Get number of vertices
        int numVertices = g.getNumVertices();

        // Validate the source vertex
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

        // Construct the DFS tree as a new Graph
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
