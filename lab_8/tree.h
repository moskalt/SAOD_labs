#pragma once

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
    vector<vector<int>> AW_matrix;
    vector<vector<int>> AP_matrix;
    vector<vector<int>> AR_matrix;
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
    void buildDoubleIndirection(Vertex **pVertex) {
        for (auto &item : this->m_array) {
            addDoubleIndirection(item, pVertex);
        }
    }
    void createWeightsArray() {
        for (size_t i = 0; i < m_size; i++) {
            weights_array.push_back(rand() % 100 + 30);
        }
    }
    void createAW_matrix() {
        AW_matrix.resize(m_size + 1);
        for (auto &i : AW_matrix) {
            i.resize(m_size + 1);
        }
        for (auto &i : AW_matrix) {
            for (size_t j = 0; j < AW_matrix.size(); j++) {
                i[j] = 0;
            }
        }
        for (size_t i = 0; i < AW_matrix.size(); i++) {
            for (size_t j = i + 1; j < AW_matrix.size(); j++) {
                AW_matrix[i][j] = AW_matrix[i][j - 1] + weights_array[j - 1];// i ?
            }
        }
    }
    void printAW_matrix() {
        cout << endl;
        for (auto &i : AW_matrix) {
            cout << endl;
            for (size_t j = 0; j < AW_matrix.size(); j++) {
                cout.width(4);
                cout << i[j] << " ";
            }
        }
    }
    void printAR_matrix() {
        cout << endl;
        for (size_t i = 0; i < AW_matrix.size(); i++) {
            cout << endl;
            for (size_t j = 0; j < AW_matrix.size(); j++) {
                cout.width(4);
                cout << AR_matrix[i][j] << " ";
            }
        }
    }
    void printAP_matrix() {
        cout << endl;
        for (size_t i = 0; i < AW_matrix.size(); i++) {
            cout << endl;
            for (size_t j = 0; j < AW_matrix.size(); j++) {
                cout.width(4);
                cout << AP_matrix[i][j] << " ";
            }
        }
    }
    void createAPAR_matrix() {
        AP_matrix.resize(m_size + 1); // ??
        AR_matrix.resize(m_size + 1); // ??
        for (size_t i = 0; i < this->m_size; i++) {
            AP_matrix[i][i + 1] = AW_matrix[i][i + 1]; // падает тут
            AR_matrix[i][i + 1] = i + 1;
        }
        for (size_t h = 2; h <= this->m_size; h++) {
            for (size_t i = 0; i < this->m_size - h; i++) {
                size_t j = i + h;
                size_t m = AR_matrix[i][j - 1];
                int min = AP_matrix[i][m - 1] + AP_matrix[m][j];
                for (size_t k = m + 1; k <= AR_matrix[i + 1][j]; k++) {
                    int x = AP_matrix[i][k - 1] + AP_matrix[k][j];
                    if (x < min) {
                        m = k;
                        min = x;
                    }
                }
                AP_matrix[i][j] = min + AW_matrix[i][j];
                AR_matrix[i][j] = m;
            }
        }
    }
};