#include "tree.h"
#include <iostream>

int main(){
    cout << "Input tree size: ";
    int size;
    cin >> size;
    cout << endl;
    Tree tree(size);
    tree.createAWmatrix();
    tree.printAWmatrix();
}