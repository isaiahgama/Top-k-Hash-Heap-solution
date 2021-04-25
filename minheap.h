// Isaiah Gama, 4/24/2021

#include <iostream>
#include <vector>
using namespace std;
#include "Node.h"

class minHeap{

    public:
        minHeap(int capacity);

        Node* insert(Node *n);
        Node* deleteMin(Node *n);

    private:
        Node *arr;
        int population;
        int capacity;
        void percolateUp(Node *n);
        void percolateDown(int i);
};

minHeap::minHeap(int heapCapacity){
    population = 0;
    arr = new Node[heapCapacity];
    this->capacity = heapCapacity;
}


void insert(Node *n){
    
}