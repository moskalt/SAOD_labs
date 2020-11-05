#include "tree.h"
#include <iostream>

int main() {
    cout << "Input tree size: ";
    int size = 10;
    cout << endl;
    Tree tree(size);
    tree.createAW_matrix();
    tree.printAW_matrix();
    tree.createAPAR_matrix();
    tree.printAP_matrix();
    tree.printAR_matrix();
}