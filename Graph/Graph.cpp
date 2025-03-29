// davidkitinberg@gmail.com

#include "Graph.h"
#include <stdexcept>
#include <iostream>



namespace graph {

// Constructor
Graph::Graph(int numVertices) : numVertices(numVertices) {
    // Validation of correct input
    if (numVertices <= 0) {
        throw std::invalid_argument("Number of vertices must be positive");
    }

    // Construct the adjacencyList
    // Allocation of adjacencyList with a finite Array size (as requested)
    adjacencyList = new EdgeNode*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyList[i] = nullptr;
    }
}

// destructor
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i)
    {
        EdgeNode* current = adjacencyList[i];
        while (current)
        {
            EdgeNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacencyList;
}

void Graph::validateVertex(int v) const {
    if (v < 0 || v >= numVertices)
    {
        throw std::out_of_range("Invalid vertex index");
    }
}

// Helper method that checks there is an existing edge between 2 vertices.
bool Graph::edgeExists(int src, int dest) const {
    validateVertex(src);
    EdgeNode* current = adjacencyList[src];
    while (current) {
        if (current->neighbor == dest) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void Graph::addEdge(int src, int dest, int weight) {
    // Validate edge's index number correctness
    validateVertex(src);
    validateVertex(dest);
    // Check wheter or not this edge already exists
    if (edgeExists(src, dest)) {
        throw std::runtime_error("Edge already exists");
    }

    // Add a new edge in both directions (this is an undirected graph)
    EdgeNode* newNode1 = new EdgeNode{dest, weight, adjacencyList[src]};
    adjacencyList[src] = newNode1;

    EdgeNode* newNode2 = new EdgeNode{src, weight, adjacencyList[dest]};
    adjacencyList[dest] = newNode2;
}

void Graph::removeEdge(int src, int dest) {
    // Validate edge's index number correctness
    validateVertex(src);
    validateVertex(dest);

    // When removing an edge in undirected graph, we should remove the edge in the adjacencyList
    // both from src index and dest index

    // Removing edge from src
    EdgeNode** current = &adjacencyList[src];
    while (*current && (*current)->neighbor != dest) {
        current = &((*current)->next);
    }
    if (*current == nullptr) {
        throw std::runtime_error("Edge does not exist");
    }
    EdgeNode* toDelete = *current;
    *current = toDelete->next;
    delete toDelete;

    // Removing edge from dest
    current = &adjacencyList[dest];
    while (*current && (*current)->neighbor != src) {
        current = &((*current)->next);
    }
    if (*current) {
        toDelete = *current;
        *current = toDelete->next;
        delete toDelete;
    }
}

void Graph::print_graph() const {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << i << ": ";
        EdgeNode* current = adjacencyList[i];
        while (current) {
            std::cout << "(" << current->neighbor << ", w=" << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

Graph::EdgeNode** Graph::getAdjacencyList() const {
    return adjacencyList;
}

}
