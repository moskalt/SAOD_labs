#pragma once
#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    int data = 0;
    int balance = 0;
    Vertex *ptrRight = nullptr;
    Vertex *ptrLeft = nullptr;
};
class Tree {

private:
    // members
    vector<int> m_array;
    int m_size = 0;
    bool m_increase = true;
    bool m_decrease = true;
    // methods
    void fillVector(int tree_size) {
        while (m_array.size() < tree_size) {
            this->m_array.push_back(rand() % 10000 - 5000);
            auto res = unique(m_array.begin(), m_array.end());
            m_array.erase(res, m_array.end());
        }
    }
    void printVector() {
        cout << "Initial array" << endl;
        for (auto &i : m_array) {
            cout << i << " ";
        }
        cout << endl;
    }

public:
    explicit Tree(int size) {
        this->m_size = size;
        fillVector(m_size);
        printVector();
    }
    vector<int> getVector() {
        return m_array;
    }
    // print tree
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
    // build
    void fillAVL(Vertex **root) {
        for (auto &item : this->m_array) {
        }
    }

};// end of class