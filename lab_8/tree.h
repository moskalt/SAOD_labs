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
    vector<vector<int>> AWmatrix;
    vector<vector<int>> APmatrix;
    vector<vector<int>> ARmatrix;
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

    void printWeightvector() {
        cout << "Weight Vector" << endl;
        for (auto &i:weights_array) {
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

    int getVectorElement(int index) {
        return m_array[index];
    }

    explicit Tree(int size) {
        this->m_size = size;
        fillVector(m_size);
        createWeigthsArray();
        printVector();
        printWeightvector();
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

    void createWeigthsArray() {
        for (size_t i = 0; i < m_size; i++) {
            weights_array.push_back(rand() % 100 + 30);
        }
    }

    void createAWmatrix() {
        AWmatrix.resize(m_size + 1);
        for (size_t i = 0; i < AWmatrix.size(); i++) {
            AWmatrix[i].resize(m_size + 1);
        }
        for (size_t i = 0; i < AWmatrix.size(); i++) {
            for (size_t j = 0; j < AWmatrix.size(); j++) {
                AWmatrix[i][j] = 0;
            }
        }
        for (size_t i = 0; i < AWmatrix.size(); i++) {
            for (size_t j = i +1; j < AWmatrix.size(); j++) {
                AWmatrix[i][j] = AWmatrix[i][j -1 ] + weights_array[j - 1];
            }
        }
    }

    void printAWmatrix() {
        cout << endl;
        for (size_t i = 0; i < AWmatrix.size(); i++) {
            cout << endl;
            for (size_t j = 0; j < AWmatrix.size(); j++) {
                cout.width(4);
                cout << AWmatrix[i][j] << " ";
            }
        }
    }
    void printARmatrix(){
        cout << endl;
        for (size_t i = 0; i < AWmatrix.size(); i++) {
            cout << endl;
            for (size_t j = 0; j < AWmatrix.size(); j++) {
                cout.width(4);
                cout << ARmatrix[i][j] << " ";
            }
        }
    }

    void printAPmatrix(){
        cout << endl;
        for (size_t i = 0; i < AWmatrix.size(); i++) {
            cout << endl;
            for (size_t j = 0; j < AWmatrix.size(); j++) {
                cout.width(4);
                cout << APmatrix[i][j] << " ";
            }
        }
    }

    void createAPARmatrix(){
        for(size_t i = 0; i < AWmatrix.size() -1 ; i++){
            APmatrix[i][i+1] = AWmatrix[i][i+1];
            ARmatrix[i][i+1] = i+1;
        }
        for(size_t h = 2; h < ARmatrix.size(); h++){
            for(size_t i = 0; i < ARmatrix.size() - h; i++){
                size_t j = i + h;
                size_t m = ARmatrix[i][j-1];
                int min = APmatrix[i][m-1] + APmatrix[m][j];
                for(size_t k = m+1; k < ARmatrix[i+1][j]; k++){
                    int x = APmatrix[i][k-1] + APmatrix[k][j];
                    if(x < min){
                        m = k;
                        min = x;
                    }
                }
                APmatrix[i][j] = min + AWmatrix[i][j];
                ARmatrix[i][j] = m;
            }
        }
    }

};