#include <iostream>

using namespace std;


class Tree {
private:
    struct Vertex {
        int data;
        Vertex *ptr_r_Vertex;
        Vertex *ptr_l_Vertex;

        Vertex() {
            ptr_l_Vertex = nullptr;
            ptr_r_Vertex = nullptr;
            data = 0;
        }
    };


public:
    Vertex *ptr_root = nullptr;

    Tree() {
        Vertex *new_ptr = new Vertex;
        this->ptr_root = new_ptr;
    }

    Vertex *CreateVertex() {
        Vertex *pVertex = new Vertex;
        return pVertex;
    }

    void PrintLeftToRight(Vertex *pVertex) {
        if (pVertex != nullptr) {
            PrintLeftToRight(pVertex->ptr_l_Vertex);
            cout << pVertex->data << " ";
            PrintLeftToRight(pVertex->ptr_r_Vertex);
        }
    }

    void PrintTopBottom(Vertex *pVertex) {
        if (pVertex != nullptr) {
            cout << pVertex->data << " ";
            PrintTopBottom(pVertex->ptr_l_Vertex);
            PrintTopBottom(pVertex->ptr_r_Vertex);
        }
    }

    void PrintBottomTop(Vertex *pVertex) {
        if (pVertex != nullptr) {
            PrintBottomTop(pVertex->ptr_l_Vertex);
            PrintBottomTop(pVertex->ptr_r_Vertex);
            cout << pVertex->data << " ";
        }
    }


    void GetRoot() {
        if (this->ptr_root == nullptr) {
            Vertex *new_ptr_root = new Vertex;
            this->ptr_root = new_ptr_root;
        }
    }


};

int main() {
    return 0;
}
