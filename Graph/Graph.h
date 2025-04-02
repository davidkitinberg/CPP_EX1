// davidkitinberg@gmail.com


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

namespace graph {

    class Graph {
    public:

        struct EdgeNode {
            int neighbor;
            int weight;
            EdgeNode* next;
        };

    private:
        int numVertices;
        EdgeNode** adjacencyList; // array of linked lists

        void validateVertex(int v) const;

    public:
        Graph(int numVertices);
        ~Graph();

        void addEdge(int src, int dest, int weight = 1);
        void removeEdge(int src, int dest);
        void print_graph(const std::string& label) const;


        // Getters for BFS and other algorithms
        int getNumVertices() const;
        EdgeNode** getAdjacencyList() const;

        bool edgeExists(int src, int dest) const;
    };

}

#endif
