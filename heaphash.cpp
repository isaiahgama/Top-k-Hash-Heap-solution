//Isaiah Gama, 4/25/2021
#include <iostream>
using namespace std;
#include "heaphash.h"

int nextPrime(int n){ // calculate tableSize
    //n++ ensures we dont return the same number
    n++;
    for(int i=2; i < n; i++){
        if(n % i == 0){
            n++;
            i=2;
        }
    }
    //cout<<n<<endl;
    return n;
}


// heap functions
heapHash::heapHash(int cap){ // constructor, initialize all variables we use
    //heap
    population = 0;
    timeAdded = 0;
    heap = new Node[cap+1];
    this->capacity = cap;
    //hashtable
    tableSize = nextPrime(2*cap);
    hashTable = new Node[tableSize];

}

void heapHash::insertNotFullNorExists(Node *n){
    //insert into the heap
    population++;
    heap[population].info = n->info;
    heap[population].frequency = 1;
    heap[population].index = population;
    timeAdded++;
    heap[population].time = timeAdded;
    // insert into the hash table
    n->index = population;
    n->frequency = 1;
    n->tag = 1;
    insert(n);
    percolateUp(population);
}

void heapHash::insertExists(int ind){
    //just increment and percolate down
    heap[ind].frequency+=1;
    percolateDown(ind);
}

void heapHash::insertFullNotExists(Node *n){
    // f+1
    int newFreq = heap[1].frequency + 1;
    //delete the old min
    deleteMin();
    //insert the new node
    population++;
    heap[population].info = n->info;
    heap[population].frequency = newFreq;
    heap[population].index = population;
    timeAdded++;
    heap[population].time = timeAdded;
    //insert the new node in the hash table
    n->index = population;
    n->frequency = newFreq;
    n->tag = 1;
    insert(n);
    percolateUp(n->index);
    
}

void heapHash::deleteMin(){
    if(population > 1){
        string newMin = heap[population].info;
        string toDel = heap[1].info;

        swap(heap[1],heap[population]);
        update(newMin,1);
        del(toDel);

        population--;
        percolateDown(1);
    }
    return;
}

bool heapHash::compare(Node child, Node parent){ // return true if child < parent , false if child > parent
    //child < parent
    if(child.frequency < parent.frequency){
        return true; // need to swap
    }
    
    if(child.frequency == parent.frequency){
        if(child.time > parent.time){ // bigger times means newer (smaller)
            return true; // child newer than parent, need to swap
        }
    }
    return false; // no need to swap
}

void heapHash::percolateUp(int ind){
    int parent = ind/2;

    if (ind <= 1){ // if only one node, do nothing
        return;
    }

    bool needToSwap = compare(heap[ind],heap[parent]);

    if(needToSwap){

        int newParent = ind;
        int newChild = parent;
        string oldParent = heap[parent].info;
        string oldChild = heap[ind].info;

        update(oldParent, newParent);
        update(oldChild, newChild);
        swap(heap[ind],heap[parent]);

        percolateUp(parent);
    }

}

void heapHash::percolateDown(int ind){

    int min = ind;
    int l = ind*2;
    int r = ind*2+1;

    if(l <= population ){

        if(compare(heap[l],heap[ind])){
            min = l;
        }
    }

    if(r <= population ){
        if(compare(heap[r],heap[min])){
            min = r;
        }
    }

    if(min != ind){
        int newParent = min;
        int newChild = ind;
        string oldParent = heap[ind].info;
        string oldChild = heap[min].info;

        
        update(oldParent, newParent);
        update(oldChild, newChild);
        swap(heap[ind],heap[min]);

        percolateDown(min);
    }
}

string heapHash::toPrint(){
    //returns the formatted output we need
    string toReturn = "" + heap[1].info + ":" + to_string(heap[1].frequency) +",";
    deleteMin();
    // string toReturn = "";
    // cout<<"Printing Hash table"<<endl;
    // for(int i = 0; i < tableSize; i++){
    //     cout<<"Info: "<<hashTable[i].info<<", Tag: "<<hashTable[i].tag<<", Index: "<<hashTable[i].index<<endl;
    // }
    return toReturn;
}

// hashtable functions

void heapHash::insert(Node* n){
    int toHash = stoi(n->info);
    hash<int> hash;
    int index = hash(toHash)%tableSize;
    
    bool done = false;
    int i = 0; //  i used for quadratic probing
    while(!done){ 
        if(hashTable[(index+i*i)%tableSize].tag == 1){ // if that slot is already taken, i++ and try again
            i++;
        }else{ // if we found an empty slot, insert the node
            hashTable[(index+i*i)%tableSize].info = n->info;
            hashTable[(index+i*i)%tableSize].tag = 1;
            hashTable[(index+i*i)%tableSize].index = n->index;
            hashTable[(index+i*i)%tableSize].frequency = n->frequency;
            done = true;
        }
    }
}

bool heapHash::search(Node* n){

    int toHash = stoi(n->info);
    hash<int> hash;
    int index = hash(toHash)%tableSize;

    
    for(int i = 0; i < tableSize/2; i++){ // replaced while loop, both work

        if(hashTable[(index+i*i)%tableSize].tag == 1){ // if slot is not empty/deleted
            if(hashTable[(index+i*i)%tableSize].info == n->info){ // and its string matches the one we're looking for
                return true;
            }
        }
    }
    return false;
}

int heapHash::searchIndex(Node* n){ // same function as search but returns the index of the node in the hash table
    int toHash = stoi(n->info);
    hash<int> hash;
    int index = hash(toHash)%tableSize;

    for(int i = 0; i < tableSize/2; i++){

        if(hashTable[(index+i*i)%tableSize].tag == 1){ 
            if(hashTable[(index+i*i)%tableSize].info == n->info){
                //cout<<"searching for "<<n->info<<endl;
                //cout<<"returning: "<<hashTable[(index+i*i)%tableSize].info<<endl;
                return hashTable[(index+i*i)%tableSize].index;
            }
        }
    }
}

void heapHash::del(string s){
    int toHash = stoi(s);
    hash<int> hash;
    int index = hash(toHash)%tableSize;

    
    for(int i = 0; i <tableSize/2; i++){
        if( (hashTable[(index+i*i)%tableSize].tag == 1) ){ // if not empty
            if( (hashTable[(index+i*i)%tableSize].info == s) ){ // if the strings match
                // cout<<"supposed to delete: "<<s<<endl;
                // cout<<"deleting: "<<hashTable[(index+i*i)%tableSize].info<<endl;
                hashTable[(index+i*i)%tableSize].tag = 2;
                return;
            }
        }        
    }
}

void heapHash::update(string s, int newIndex){
    int toHash = stoi(s);
    hash<int> hash;
    int index = hash(toHash)%tableSize;

    for(int i = 0; i < tableSize/2; i++){
        if(hashTable[(index+i*i)%tableSize].tag == 1){ // if slot isn't empty
            if(hashTable[(index+i*i)%tableSize].info == s){ // and the info matches the input we're looking for
                hashTable[(index+i*i)%tableSize].index = newIndex; // update the index
                break;
            }
        }
    }
}