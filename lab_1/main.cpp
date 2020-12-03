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

    void FillTree() {
        const int size = 6;
        int array[6];
        for (int i = 0; i < 6; i++) {
            array[i] = i + 1;
        }
        Vertex *temp_ptr = this->ptr_root;
        temp_ptr->data = array[0];
        temp_ptr->ptr_r_Vertex = CreateVertex();
        temp_ptr = temp_ptr->ptr_r_Vertex;
        temp_ptr->data = array[2];
        temp_ptr->ptr_l_Vertex = CreateVertex();
        temp_ptr->ptr_l_Vertex->data = array[1];
        temp_ptr->ptr_r_Vertex = CreateVertex();
        temp_ptr = temp_ptr->ptr_r_Vertex;
        temp_ptr->data = array[5];
        temp_ptr->ptr_l_Vertex = CreateVertex();
        temp_ptr = temp_ptr->ptr_l_Vertex;
        temp_ptr->data = array[4];
        temp_ptr->ptr_l_Vertex = CreateVertex();
        temp_ptr = temp_ptr->ptr_l_Vertex;
        temp_ptr->data = array[3];
    }


};

int main() {
    Tree tree;
    tree.GetRoot();
    tree.FillTree();
    cout << "LeftRight print :" << endl;
    tree.PrintLeftToRight(tree.ptr_root);
    cout << endl << "TopBottom print :" << endl;
    tree.PrintTopBottom(tree.ptr_root);
    cout << endl << "BottomTop print :" << endl;
    tree.PrintBottomTop(tree.ptr_root);
    //creating tree from task
    return 0;
}
