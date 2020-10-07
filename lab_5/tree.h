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
    int balance = 0;
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

    bool increase = true;

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
    int getVectorElement() {
        return m_array[rand() % this->m_size];
    }

    int getVectorElement(int index) {
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

    void leftLeftRotation(Vertex **root) {
        Vertex *q = (*root)->ptrLeft;
        q->balance = 0;
        (*root)->balance = 0;
        (*root)->ptrLeft = q->ptrRight;
        q->ptrRight = *root;
        *root = q;
        increase = false;
    }

    void leftRightRotation(Vertex** root){
        Vertex* q = (*root)->ptrLeft;
        Vertex* r = q->ptrRight;
        if(r->balance < 0)
            (*root)->balance = 1;
        else
            (*root)->balance;
        if(r->balance > 0)
            q->balance = -1;
        else
            q->balance = 0;
        r->balance = 0;
        (*root)->ptrLeft = r->ptrRight;
        q->ptrRight = r->ptrRight;
        r->ptrLeft = q;
        r->ptrRight = (*root);
        (*root) = r;
        increase = true;
    }

    void rightRightRotation(Vertex** root){
        Vertex* q = (*root)->ptrRight;
        q->balance = 0;
        (*root)->balance = 0;
        (*root)->ptrRight = q->ptrLeft;
        q->ptrLeft = (*root);
        (*root) = q;
        increase = false;
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
        r->ptrRight - q;
        (*root) = r;
        increase = false;
    }
    void leftRightRotation(Vertex **root) {
    }
    void AVLTree(Vertex **head, int key) {
        if (*head == nullptr) {
            (*head) = new Vertex;
            (*head)->data = key;
            increase = true;
        } else if ((*head)->data > key) {
            AVLTree(&((*head)->ptrLeft), key);
            if (increase) {
                if ((*head)->balance > 0) {
                    (*head)->balance = 0;
                    increase = false;
                } else if ((*head)->balance == 0) {
                    (*head)->balance = -1;
                    increase = true;
                } else if ((*head)->ptrLeft->balance < 0) {
                    leftLeftRotation(head);
                } else {
                    leftRightRotation(head);
                }
            }
        } else if ((*head)->data < key) {
            AVLTree(&((*head)->ptrRight), key);
            if (increase) {
                if ((*head)->balance < 0) {
                    (*head)->balance = 0;
                    increase = false;
                } else if ((*head)->balance == 0) {
                    (*head)->balance = 1;
                    increase = true;
                } else if ((*head)->ptrRight->balance > 0) {
                    rightRightRotation(head);
                } else {
                    rightLeftRotation(head);
                }
            }
        }
    }
};