#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

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

    Vertex *TreeBuild(int size_left, int size_right, vector<int> array) {
        if (size_left > size_right)
            return nullptr;
        else {
            int middle = (size_left + size_right) / 2;
            Vertex* root = CreateVertex();
            root->data = array[middle];
            root->ptr_l_Vertex = TreeBuild(size_left, middle - 1,array);
            root->ptr_r_Vertex = TreeBuild(middle + 1, size_right, array);
            return root;
        }
    }
};

int main() {
    srand(time(NULL));
    cout << "Input tree size" << endl;
    int tree_size;
    cin >> tree_size;
    vector<int> array;
    for (int i = 0; i < tree_size; i++) {
        array.push_back(rand() % 100 - 50);
    }
    sort(array.begin(), array.end());
    for (auto &item: array) {
        cout.width(3);
        cout << item << " ";
    }
    Tree tree;
    tree.TreeBuild(0, array.size()-1, array);
    tree.PrintLeftToRight()
    return 0;
}
