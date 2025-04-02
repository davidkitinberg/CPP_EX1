// davidkitinberg@gmail.com


#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cstdlib>


namespace ds {

class Queue {
  int *array;
  int capacity;
  int front;
  int rear;
  public:
    Queue(int size);
    ~Queue();

    int dequeue();
    int enqueue(int value);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};

}

#endif
