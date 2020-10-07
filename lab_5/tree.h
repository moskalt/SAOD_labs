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
    // methods
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

public:
    explicit Tree(int size) {
        this->m_size = size;
        fillVector(m_size);
        printVector();
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
    // rotation
    void leftLeftRotation(Vertex **root) {
        Vertex *q = (*root)->ptrLeft;
        q->balance = 0;
        (*root)->balance = 0;
        (*root)->ptrLeft = q->ptrRight;
        q->ptrRight = *root;
        *root = q;
        this->m_increase = false;
    }
    void leftRightRotation(Vertex** root){
        Vertex* q = (*root)->ptrLeft;
        Vertex* r = q->ptrRight;
        if(r->balance < 0)
            (*root)->balance = 1;
        else
            (*root)->balance = 0;
        if(r->balance > 0)
            q->balance = -1;
        else
            q->balance = 0;
        r->balance = 0;
        (*root)->ptrLeft = r->ptrRight;
        q->ptrRight = r->ptrLeft;
        r->ptrLeft = q;
        r->ptrRight = (*root);
        (*root) = r;
        this->m_increase = true;
    }
    void rightRightRotation(Vertex** root){
        Vertex* q = (*root)->ptrRight;
        q->balance = 0;
        (*root)->balance = 0;
        (*root)->ptrRight = q->ptrLeft;
        q->ptrLeft = (*root);
        (*root) = q;
        this->m_increase = false;
    }
    void rightLeftRotation(Vertex** root){
        Vertex* q = (*root)->ptrRight;
        Vertex* r = q->ptrLeft;
        if(r->balance > 0)
            (*root)->balance = -1;
        else
            (*root)->balance = 0;
        if(r->balance < 0)
            q->balance = 1;
        else
            q->balance = 0;
        r->balance = 0;
        (*root)->ptrRight = r->ptrLeft;
        q->ptrLeft = r->ptrRight;
        r->ptrLeft = (*root);
        r->ptrRight = q;
        (*root) = r;
        this->m_increase = false;
    }
    // build
    void buildAVL(Vertex **root, int key) {
        if (*root == nullptr) {
            (*root) = new Vertex;
            (*root)->data = key;
            this->m_increase = true;
        } else if ((*root)->data > key) {
            buildAVL(&((*root)->ptrLeft), key);
            if (this->m_increase) {
                if ((*root)->balance > 0) {
                    (*root)->balance = 0;
                    this->m_increase = false;
                } else if ((*root)->balance == 0) {
                    (*root)->balance = -1;
                    this->m_increase = true;
                } else if ((*root)->ptrLeft->balance < 0) {
                    leftLeftRotation(root);
                } else {
                    leftRightRotation(root);
                }
            }
        } else if ((*root)->data < key) {
            buildAVL(&((*root)->ptrRight), key);
            if (this->m_increase) {
                if ((*root)->balance < 0) {
                    (*root)->balance = 0;
                    this->m_increase = false;
                } else if ((*root)->balance == 0) {
                    (*root)->balance = 1;
                    this->m_increase = true;
                } else if ((*root)->ptrRight->balance > 0) {
                    rightRightRotation(root);
                } else {
                    rightLeftRotation(root);
                }
            }
        }
    }
    void fillAVL(Vertex** root){
        for(auto &item:this->m_array){
            buildAVL(root, item);
        }
    }
};