#include "tree.h"
#include <iostream>

int main() {
    using namespace std;
    int treeSize = 15;
    srand(time(nullptr));
    // head
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    // build
    tree1.fillAVL(&head1);
    // result
    cout << "Left to right:" << endl;
    tree1.printLeftToRight(head1);
    cout << endl
         << "Top to bottom:" << endl;
    tree1.printTopToBottom(head1);
    return 0;
}
