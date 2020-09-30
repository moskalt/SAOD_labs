#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    int data = 0;
    Vertex *ptrRight = nullptr;
    Vertex *ptrLeft = nullptr;
};

Vertex *CreateVertex() {
    auto *pVertex = new Vertex;
    return pVertex;
}

class Tree {

private:
    vector<int> m_array;
    int m_size = 0;
    void fillVector(int tree_size) {
        for (int i = 0; i < tree_size; i++) {
            this->m_array.push_back(rand() % 400 - 100);
        }
    }
    void printVector() {
        cout << "Initial array" << endl;
        for (auto &i : m_array) {
            cout << i << " ";
        }
        cout << endl;
    }
    static void addDoubleIndirection(int key, Vertex **root) {
        Vertex **head_ptr = root;
        while (*head_ptr) {
            if (key < (*head_ptr)->data) {
                head_ptr = &((*head_ptr)->ptrLeft);
            } else if (key > (*head_ptr)->data) {
                head_ptr = &((*head_ptr)->ptrRight);
            } else {
                cout << "Element is already in the array" << endl;
                break;
            }
        }
        if (*head_ptr == nullptr) {
            *head_ptr = CreateVertex();
            (*head_ptr)->data = key;
        }
    }

public:
    explicit Tree(int size) {
        this->m_size = size;
        fillVector(m_size);
        printVector();
    }
    void printLeftToRight(Vertex *root) {
        if (root != nullptr) {
            printLeftToRight(root->ptrLeft);
            cout << root->data << " ";
            printLeftToRight(root->ptrRight);
        }
    }
    void printTopToBottom(Vertex *root) {
        if (root != nullptr) {
            cout << root->data << " ";
            printTopToBottom(root->ptrLeft);
            printTopToBottom(root->ptrRight);
        }
    }
    void printBottomToTop(Vertex *root) {
        if (root != nullptr) {
            printBottomToTop(root->ptrLeft);
            printBottomToTop(root->ptrRight);
            cout << root->data << " ";
        }
    }
    void buildDoubleIndirection(Vertex **pVertex) {
        for (auto &item : this->m_array) {
            addDoubleIndirection(item, pVertex);
        }
    }
    static void DeleteElement(int key, Vertex *root) {
        Vertex **ptrRoot = &root;
        Vertex *temp1, *temp2, *temp3;
        while (*ptrRoot != nullptr) {
            if ((*ptrRoot)->data < key) {
                ptrRoot = &(*ptrRoot)->ptrRight;
            } else if ((*ptrRoot)->data > key) {
                ptrRoot = &(*ptrRoot)->ptrLeft;
            } else {
                cout << "Delete element:" << (*ptrRoot)->data << endl;
                break;
            }
        }
        if (*ptrRoot != nullptr) {
            temp3 = *ptrRoot;
            if (temp3->ptrLeft == nullptr) {
                *ptrRoot = temp3->ptrRight;
            } else if (temp3->ptrRight == nullptr) {
                *ptrRoot = temp3->ptrLeft;
            } else {
                temp1 = temp3->ptrLeft;
                temp2 = temp3;
                while (temp1->ptrRight != nullptr) {
                    temp2 = temp1;
                    temp1 = temp1->ptrRight;
                }
                temp2->ptrRight = temp1->ptrLeft;
                temp1->ptrLeft = temp3->ptrRight;
                temp1->ptrRight = temp3->ptrRight;
                *ptrRoot = temp1;
            }
            delete temp3;
        }
    }
};

int main() {
    int treeSize = 15;
    // srand(time(nullptr));
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    tree1.buildDoubleIndirection(&head1);
    cout << "LeftToRight:" << endl;
    tree1.printLeftToRight(head1);
    int delElement = -42;
    cout << endl
         << "Try to delete element: " << delElement << endl;
    Tree::DeleteElement(delElement, head1);
    cout << "LeftToRight:" << endl;
    tree1.printLeftToRight(head1);
    return 0;
}