#ifndef LAB_9_TREE_H
#define LAB_9_TREE_H

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
    vector<int> weights_array;
    int m_size = 0;
    void fillVector(int tree_size) {
        for (int i = 0; i < tree_size; i++) {
            this->m_array.push_back(rand() % 700 - 350);
        }
        auto ptr = unique(m_array.begin(), m_array.end());
        m_array.erase(ptr, m_array.end());
        while (m_array.size() < tree_size) {
            this->m_array.push_back(rand() % 700 - 350);
            auto newPtr = unique(m_array.begin(), m_array.end());
            m_array.erase(newPtr, m_array.end());
        }
    }
    void printVector() {
        cout << "Initial array" << endl;
        for (auto &i : m_array) {
            cout << i << " ";
        }
        cout << endl;
    }
    void printWeightVector() {
        cout << "Weight Vector" << endl;
        for (auto &i : weights_array) {
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
        createWeightsArray();
        printVector();
        printWeightVector();
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
    void createWeightsArray() {
        for (size_t i = 0; i < m_size; i++) {
            weights_array.push_back(rand() % 100 + 2);
        }
    }
    void QuickSortRev(int L, int R) {
        int i = L;
        int j = R;
        int temp = weights_array[(i + j) / 2];
        while (i <= j) {
            while (weights_array[i] > temp) {
                i++;
            }
            while (weights_array[j] < temp) {
                j--;
            }
            if (i <= j) {
                swap(weights_array[i], weights_array[j]);
                swap(m_array[i], m_array[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            QuickSortRev(L, j);
        }
        if (i < R) {
            QuickSortRev(i, R);
        }
    }
    void buildTreeA1(Vertex **root) {
        //sort weights
        QuickSortRev(0, (int) m_array.size() - 1);
        printVector();
        printWeightVector();
        for (int &i : m_array) {
            addDoubleIndirection(i, root);
        }
    }
    void sortArrays() {
        QuickSortVertex(0, m_size - 1);
        printVector();
        printWeightVector();
    }
    void QuickSortVertex(int L, int R) {
        int i = L;
        int j = R;
        int temp = m_array[(i + j) / 2];
        while (i <= j) {
            while (m_array[i] < temp) {
                i++;
            }
            while (m_array[j] > temp) {
                j--;
            }
            if (i <= j) {
                swap(weights_array[i], weights_array[j]);
                swap(m_array[i], m_array[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            QuickSortVertex(L, j);
        }
        if (i < R) {
            QuickSortVertex(i, R);
        }
    }
    void buildTreeA2(Vertex **root, int L, int R) {
        int weight = 0;
        int sum = 0;
        int temp_index;
        if (L <= R) {
            for (int i = L; i <= R; i++) {
                weight += weights_array[i];
            }
            for (int i = L; i <= R; i++) {
                temp_index = i;
                if (sum < weight / 2 && (sum + weights_array[i]) > weight / 2) {
                    break;
                }
                sum += weights_array[i];
            }
            addDoubleIndirection(m_array[temp_index], root);
            buildTreeA2(root, L, temp_index - 1);
            buildTreeA2(root, temp_index + 1, R);
            return;
        }
    }
};


#endif//LAB_9_TREE_H
