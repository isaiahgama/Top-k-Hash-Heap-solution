//Isaiah Gama, 4/25/2021
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

struct Node{
    string info = "";
    int frequency = 0;
    int index = 0;
    int time = 0;
    int tag = 0; // 0 = empty, 1 = not empty, 2 = deleted
};

#endif