#include <iostream>
#include "tree.h"
#include <ctime>

using namespace std;

int main() {
    //srand(time(nullptr));
    int size;
    cout << "Input: " ;
    cin >> size;
    Tree tree(size);
    Vertex* root = nullptr;
    tree.buildTreeA1(&root);
    cout << "A1" << endl;
    cout << "Top to Bottom : " ;
    tree.printTopToBottom(root);
    cout << endl << "Left to Right : ";
    tree.printLeftToRight(root);
    cout << endl;
    cout << "A2" << endl;
    Tree tree2(size);
    Vertex* root2 = nullptr;
    tree2.sortArrays();
    tree2.createIndexArray();
    tree2.buildTreeA2(&root2, 0, size-1);
    cout << "Top to Bottom : " ;
    tree2.printTopToBottom(root2);
    cout << endl << "Left to Right : ";
    tree2.printLeftToRight(root2);
    cout << endl << endl;
    return 0;
}
