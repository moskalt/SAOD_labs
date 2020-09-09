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

    void CreateTree(int size, Vertex *root) {
        Vertex *root_ptr = root;
        int vertex_left_count = 0;
        int vertex_right_count = 0;
        if ((size - 1) % 2 == 0 && size != 0) {
            vertex_right_count = vertex_left_count = (size - 1) / 2;
            if (size == 1) {
                root_ptr->ptr_l_Vertex = CreateVertex();
                return;
            }
            //creating new Vertexes
            if (vertex_left_count != 0) {
                root_ptr->ptr_l_Vertex = CreateVertex();
                vertex_left_count--;
            }
            if (vertex_right_count != 0) {
                root_ptr->ptr_r_Vertex = CreateVertex();
                vertex_right_count--;
            }
            CreateTree(vertex_left_count, root_ptr->ptr_l_Vertex);
            CreateTree(vertex_right_count, root_ptr->ptr_r_Vertex);


        } else if ((size - 1) % 2 == 1 && size != 0) {
            if (size == 1) {
                root_ptr->ptr_l_Vertex = CreateVertex();
                return;
            }
            vertex_left_count = (size - 1) / 2 + 1;
            vertex_right_count = (size - 1) / 2;
            //creating new Vertexes
            if (vertex_left_count != 0) {
                root_ptr->ptr_l_Vertex = CreateVertex();
                vertex_left_count--;
            }
            if (vertex_right_count != 0) {
                root_ptr->ptr_r_Vertex = CreateVertex();
                vertex_right_count--;
            }
            CreateTree(vertex_left_count, root_ptr->ptr_l_Vertex);
            CreateTree(vertex_right_count, root_ptr->ptr_r_Vertex);
        }
    }

    void PrintLeftToRight(Vertex* pVertex){
        if(pVertex != nullptr){
            cout.width(4);
            PrintLeftToRight(pVertex->ptr_l_Vertex);
            cout << pVertex->ptr_l_Vertex->data << endl;
            PrintLeftToRight(pVertex->ptr_r_Vertex);
        }
    }

    Vertex *GetRoot() {
        return this->ptr_root;
    }


};

int main() {
    Tree tree;
    tree.CreateTree(5,tree.GetRoot());
    return 0;
}
