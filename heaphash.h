//Isaiah Gama, 4/25/2021
#ifndef HEAPHASH_H
#define HEAPHASH_H

#include <iostream>
using namespace std;
#include "Node.h"

class heapHash{

    public:
        //heap functions
        heapHash(int cap);
        void insertNotFullNorExists(Node *n);
        void insertExists(int ind);
        void insertFullNotExists(Node *n);
        void deleteMin();
        bool compare(Node child, Node parent);
        int getPopulation(){
            return population;
        }
        string toPrint();
        bool isFull(){
            return population == capacity;
        }

        //hash functions
        void insert(Node* n);
        bool search(Node* n);
        int searchIndex(Node* n);
        void del(string s);
        void update(string s, int newIndex);


    private:
        Node* heap;
        Node* hashTable;

        //hashtable variables
        int tableSize; // hashTable size (next prime > 2*capacity)

        //minHeap variables
        int population;
        int capacity;
        int timeAdded;
        void percolateUp(int ind);
        void percolateDown(int ind);

};






#endif