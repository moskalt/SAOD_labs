#include "tree.h"
#include <algorithm>
#include <iostream>

int main() {
    using namespace std;
    int treeSize = 1000;
    srand(time(nullptr));
    // head
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    // build
    tree1.fillAVL(&head1);
    // result
    cout << "Left to right:" << endl;
    tree1.printLeftToRight(head1);
    cout << endl;
    cout << "Top to bottom:" << endl;
    set<int> originVector = tree1.getVector();
    tree1.printTopToBottom(head1);
    for (int i = 0; i < 1000; ++i) {
        tree1.deleteAVL(*originVector.begin(), head1);
        originVector.erase(originVector.begin());
        if (i % 25 == 0) {
            cout << endl;
            cout << "Left to right:" << endl;
            tree1.printLeftToRight(head1);
        }

    }
    cout << endl;
    cout << "Left to right:" << endl;
    tree1.printLeftToRight(head1);
    return 0;
}
