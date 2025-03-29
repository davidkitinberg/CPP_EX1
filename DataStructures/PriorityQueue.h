// davidkitinberg@gmail.com


#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <iostream>
#include <climits>

namespace ds {

    class PriorityQueue {
    private:
        int* vertices;      // vertex indices
        int* distances;     // distances for each vertex
        bool* inQueue;      // whether a vertex is still in the queue
        int capacity;
        int size;

    public:
        PriorityQueue(int capacity);
        ~PriorityQueue();

        void insert(int vertex, int distance);
        int extractMin(); // returns the vertex with the smallest distance
        void decreaseKey(int vertex, int newDistance);
        bool isEmpty();
        bool contains(int vertex);
        int getDistance(int vertex);
    };

}

#endif