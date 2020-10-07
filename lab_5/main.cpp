#include "tree.h"
#include <iostream>

int main() {
    using namespace std;
    int treeSize = 15;
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    tree1.fillAVL(&head1);
    cout << "Left to right: ";
    tree1.printLeftToRight(head1);
    cout << endl << "Top to bottom: ";
    tree1.printTopToBottom(head1);
    return 0;
}
