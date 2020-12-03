#include "tree.hpp"
#include <iostream>

int main() {
    Tree tree(15);
    Vertex *root = nullptr;
    tree.buildTree(&root);
    cout << endl;
    tree.printLeftToRight(root);
    cout << endl;
    tree.printTopToBottom(root);
    cout << endl;
    cout << "Max count of levels(DBD): ";
    cout << tree.countLevels();
    cout << endl;
    cout << "Max count of levels(): ";
    cout << tree.maxTreeHeight(root);
    return 0;
}
