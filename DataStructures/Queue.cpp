// davidkitinberg@gmail.com


#include <iostream>
#include "Queue.h"

using namespace std;

namespace ds {

// Constructor
Queue::Queue(int size) {
  
    // Ititalization is done only after we check whether or not the size given is valid (to prevent mem leak)
    if (size <= 0) {
      throw std::runtime_error("Invalid priority queue size!");
    }

    capacity = size + 1;
    array = new int[capacity];
    front = 0;
    rear = 0;
}

// Destructor
Queue::~Queue() {
  delete[] array;
}

int ds::Queue::enqueue(int v) {
  // Check if queue is full
  if(rear == capacity) {
    std::cerr << "Queue is full and cannot enqueue anymore :(" << endl;
    return -1;
  }
  // assign value to queue
  array[rear] = v;
  // If rear reaches the end it will wrap back itself
  rear = (rear + 1) % capacity;
  return 0;
}

int ds::Queue::dequeue() {
    // Check if queue is empty
    if (front == rear) {
        std::cerr << "Queue is empty. Cannot dequeue." << std::endl;
        return -1;
    }
    int value = array[front];
    // If front reaches the end it will wrap back itself
    front = (front + 1) % capacity;
    return value;
}

int ds::Queue::peek() {
    // Check if queue is empty
    if (front == rear) {
        std::cerr << "Queue is empty. Nothing to peek." << std::endl;
        return -1;
    }
    return array[front];
}

bool Queue::isEmpty() {
return front == rear;
}

bool Queue::isFull() {
return (rear + 1) % capacity == front;
}


int Queue::size() {
return (rear - front + capacity) % capacity;
}

}