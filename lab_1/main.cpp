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

    Vertex *ptr_root = nullptr;
public:
    Tree() {
        Vertex *new_ptr = new Vertex;
        this->ptr_root = new_ptr;
    }

    Vertex *CreateVertex() {
        Vertex *pVertex = new Vertex;
        return pVertex;
    }

    void CreateTree(int size) {
        int vertex_left_count = 0;
        int vertex_right_count = 0;
        if ((size - 1) % 2 == 0) {
            vertex_right_count = vertex_left_count = (size - 1) / 2;
            //creating new Vertexes
        } else {
            vertex_left_count = (size - 1) / 2 + 1;
            vertex_right_count = (size - 1) / 2;
            //creating new Vertexes
        }

    }

    Vertex *GetRoot() {
        return this->ptr_root;
    }


};

int main() {

    return 0;
}
