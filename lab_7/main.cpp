#include <iostream>
#include "tree.hpp"

int main() {
    Tree tree(15);
    Vertex* root = nullptr;
    tree.buildTree(&root);
    cout << endl;
    tree.printLeftToRight(root);
    cout << endl;
    tree.printTopToBottom(root);
    cout << endl;
    cout << "Count of levels(DBD): ";
    cout << tree.countLevels();
    return 0;
}
