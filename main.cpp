//Isaiah Gama, 4/25/2021
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
#include "heaphash.h"



int main(int argc, char* argv[]){

    heapHash m = heapHash(atoi(argv[3]));
    string s;
    ifstream fileName(argv[1]);
    int i = 0;

    while(getline(fileName,s,',')){
        Node* tmp = new Node();
        tmp->info = s;
        bool exists = m.search(tmp); // so we dont repeat code
        //if exists
        if(exists){
            int r = m.searchIndex(tmp);
            //cout<<"Already exists!"<<endl;
            m.insertExists(r);
            continue;
        }
        //If not full and doesn't exist
        if(!(m.isFull()) && !(exists)){
            //cout<<"Not full and doesnt exist!"<<endl;
            m.insertNotFullNorExists(tmp);
            continue;
        }
        //if full and doesnt exist
        if(m.isFull() && !(exists)){
            //cout<<"Full and doesn't exist!"<<endl;
            m.insertFullNotExists(tmp);
            continue;
        }//else{
        //     while(true)
        //     cout<<"glitch!"<<endl;
        // }        
    }

    //write to output file
    ofstream myFile;
    myFile.open(argv[2]);
    string s1 = "";
    for(int i = 0; i < atoi(argv[3]); i++){
        s1 = m.toPrint();
        myFile << s1;
    }
    myFile.close();

    return 0;
}