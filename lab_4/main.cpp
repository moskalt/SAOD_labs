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

    static void addRecursive(int key, Vertex **head) {
        if (*head == nullptr) {
            *head = CreateVertex();
            (*head)->data = key;
        } else if ((*head)->data > key) {
            addRecursive(key, &(*head)->ptrLeft);
        } else if ((*head)->data < key) {
            addRecursive(key, &(*head)->ptrRight);
        } else {
            cout << "Element is already in the array" << endl;
        }
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

    void buildRecursive(Vertex **pVertex) {
        for (auto &item : this->m_array) {
            addRecursive(item, pVertex);
        }
    }
};

int main() {
    int treeSize;
    srand(time(nullptr));
    cout << "Enter tree size: ";
    cin >> treeSize;
    cout << endl
         << "First case" << endl;
    Tree tree1(treeSize);
    Vertex *head1 = nullptr;
    tree1.buildDoubleIndirection(&head1);
    cout << "LeftToRight:" << endl;
    tree1.printLeftToRight(head1);
    cout << endl;
    cout << "Tree size : " << tree1.treeSize(head1);
    cout << endl
         << "Tree control sum: " << tree1.treeControlSum(head1);
    cout << endl
         << "Max length:" << tree1.maxTreeHeight(head1);
    cout << endl
         << "Average length: " << tree1.averageTreeHeight(head1) / float(tree1.treeSize(head1)) << endl;
    cout << endl
         << "Second case" << endl;
    Tree tree2(treeSize);
    Vertex *head2 = nullptr;
    tree2.buildRecursive(&head2);
    // print tree
    cout << "LeftToRight:" << endl;
    tree2.printLeftToRight(head2);
    cout << endl;
    cout << "Tree size : " << tree2.treeSize(head2);
    cout << endl
         << "Tree control sum: " << tree2.treeControlSum(head2);
    cout << endl
         << "Max length:" << tree2.maxTreeHeight(head2);
    cout << endl
         << "Average length: " << tree2.averageTreeHeight(head2) / float(tree2.treeSize(head2)) << endl;
    return 0;
}