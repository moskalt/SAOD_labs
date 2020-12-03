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
    pVertex->ptrRight = nullptr;
    pVertex->ptrLeft = nullptr;
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
    int getVectorElement() {
        return m_array[rand() % this->m_size];
    }

    int getVectorElement(int index){
        return m_array[index];
    }

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

    static void DeleteElement(int key, Vertex **root) {
        Vertex **ptrRoot = root;
        Vertex *r, *s, *q;
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
            q = *ptrRoot;
            if (q->ptrLeft == nullptr) {
                *ptrRoot = q->ptrRight;
            } else if (q->ptrRight == nullptr) {
                *ptrRoot = q->ptrLeft;
            } else {
                r = q->ptrLeft;
                s = q;
                if (r->ptrRight == nullptr) {
                    r->ptrRight = q->ptrRight;
                    *ptrRoot = r;
                } else {
                    //searching right element in left subtree
                    while (r->ptrRight != nullptr) {
                        s = r;
                        r = r->ptrRight;
                    }
                    s->ptrRight = r->ptrLeft;
                    //replacing right element to deleted element
                    r->ptrLeft = q->ptrLeft;
                    r->ptrRight = q->ptrRight;
                    *ptrRoot = r;
                }
            }
            delete q;
        }
    }
};

int main() {
    int treeSize = 15;
    srand(time(nullptr));
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    tree1.buildDoubleIndirection(&head1);
    cout << "LeftToRight:" << endl;
    tree1.printLeftToRight(head1);
    int delElement = tree1.getVectorElement(0);
    cout << endl
         << "Try to delete element: " << delElement << endl;
    Tree::DeleteElement(delElement, &head1);
    cout << "LeftToRight:" << endl;
    tree1.printLeftToRight(head1);
    return 0;
}