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

    int treeSize(Vertex *pVertex) {
        if (pVertex == nullptr)
            return 0;
        else
            return 1 + treeSize(pVertex->ptrLeft) +
                   treeSize(pVertex->ptrRight);
    }

    int treeControlSum(Vertex *root) {
        if (root == nullptr)
            return 0;
        else
            return root->data + treeControlSum(root->ptrLeft) +
                   treeControlSum(root->ptrRight);
    }

    int maxTreeHeight(Vertex *root) {
        if (root == nullptr) {
            return 0;
        } else {
            return 1 + max(maxTreeHeight(root->ptrLeft), maxTreeHeight(root->ptrRight));
        }
    }

    float averageTreeHeight(Vertex *root, int level = 1) {
        if (root == nullptr) {
            return 0;
        } else {
            return (float) level + averageTreeHeight(root->ptrLeft, level + 1) +
                   averageTreeHeight(root->ptrRight, level + 1);
        }
    }

    int searchInTree(Vertex *root, int key) {
        if (key == root->data) {
            cout << root->data;
            return 1;
        }
        if (root->ptrRight == nullptr && root->ptrLeft == nullptr) {
            return 0;
        }
        if (key > root->data) {
            cout << root->data << " ";
            searchInTree(root->ptrRight, key);
        } else if (key < root->data) {
            cout << root->data << " ";
            searchInTree(root->ptrLeft, key);
        }
        return 0;
    }

    void buildDoubleIndirection(Vertex **pVertex) {
        for (auto &item : this->m_array) {
            addDoubleIndirection(item, pVertex);
        }
    }

};

int main() {
    int treeSize;
    srand(time(nullptr));
    cout << "Enter tree size: ";
    cin >> treeSize;
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    tree1.buildDoubleIndirection(&head1);
    cout << "LeftToRight:" << endl;
    tree1.printLeftToRight(head1);
    return 0;
}