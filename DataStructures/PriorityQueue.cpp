// davidkitinberg@gmail.com


#include "PriorityQueue.h"
#include <iostream>
#include <climits>

namespace ds {

    // Constructor: initializes the priority queue with the given capacity.
    PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {

        // Ititalization is done only after we check whether or not the size given is valid (to prevent mem leak)
        if (cap <= 0) {
            throw std::runtime_error("Invalid priority queue size!");
        }
        
        // Allocate arrays for the vertex list, their distances, and a flag to check if they're still in the queue.
        vertices = new int[capacity];
        distances = new int[capacity];
        inQueue = new bool[capacity];

        // Initialize all distances to "infinity" and mark all vertices as not in the queue.
        for (int i = 0; i < capacity; ++i) {
            distances[i] = INT_MAX;
            inQueue[i] = false;
        }
    }

    // Destructor: cleans up all the dynamically allocated memory.
    PriorityQueue::~PriorityQueue() {
        delete[] vertices;
        delete[] distances;
        delete[] inQueue;
    }

    // Adds a new vertex to the priority queue with a given distance.
    void PriorityQueue::insert(int vertex, int distance) {
        if (size >= capacity) return; // Ignore if the queue is already full.

        vertices[size] = vertex;          // Add vertex to the queue.
        distances[vertex] = distance;     // Set its distance.
        inQueue[vertex] = true;           // Mark it as in the queue.
        ++size;                           // Increase the size counter.
    }

    // Returns the vertex with the smallest distance that is still in the queue.
    int PriorityQueue::extractMin() {
        int minDist = INT_MAX;
        int minIndex = -1;

        // Scan through all current vertices to find the one with the smallest distance.
        for (int i = 0; i < size; ++i) {
            int v = vertices[i];
            if (inQueue[v] && distances[v] < minDist) {
                minDist = distances[v];
                minIndex = i;
            }
        }

        // If no vertex was found (all were removed), return -1.
        if (minIndex == -1) return -1;

        // Remove the vertex from the queue and return it.
        int minVertex = vertices[minIndex];
        inQueue[minVertex] = false;
        return minVertex;
    }

    // Updates the distance of a vertex if the new distance is smaller.
    void PriorityQueue::decreaseKey(int vertex, int newDistance) {
        if (inQueue[vertex] && newDistance < distances[vertex]) {
            distances[vertex] = newDistance;
        }
    }

    // Checks whether the queue is completely empty.
    bool PriorityQueue::isEmpty() {
        for (int i = 0; i < capacity; ++i) {
            if (inQueue[i]) return false;
        }
        return true;
    }

    // Checks if a particular vertex is still in the queue.
    bool PriorityQueue::contains(int vertex) {
        return inQueue[vertex];
    }

    // Returns the currently stored distance of a given vertex.
    int PriorityQueue::getDistance(int vertex) {
        return distances[vertex];
    }

}
