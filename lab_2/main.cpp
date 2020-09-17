#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

class Tree {
private:
    struct Vertex {
        int data;
        Vertex *ptr_r_Vertex;
        Vertex *ptr_l_Vertex;

        int tree_size = 0;
        int tree_sum = 0;

        Vertex() {
            ptr_l_Vertex = nullptr;
            ptr_r_Vertex = nullptr;
            data = 0;
        }
    };

    vector<int> array;
    int height = 0;
    int mid_height = 0;

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

    void FillVector(int tree_size) {
        for (int i = 0; i < tree_size; i++) {
            this->array.push_back(rand() % 100 - 50);
        }
        sort(this->array.begin(), this->array.end());
    }

    Vertex *TreeBuild(int size_left, int size_right) {
        if (size_left > size_right)
            return nullptr;
        else {
            int middle = (size_left + size_right) / 2;
            Vertex *root = CreateVertex();
            root->data = this->array[middle];
            root->ptr_l_Vertex = TreeBuild(size_left, middle - 1);
            root->ptr_r_Vertex = TreeBuild(middle + 1, size_right);
            return root;
        }
    }

    void GetRoot() { this->ptr_root = TreeBuild(0, this->array.size() - 1); }

    Vertex *ReturnRoot() { return this->ptr_root; }

    int MaxTreeHeight(Vertex *pVertex) {
        if (pVertex == nullptr) {
            return 0;
        } else {
            return this->height = 1 + max(MaxTreeHeight(pVertex->ptr_l_Vertex),
                                          MaxTreeHeight(pVertex->ptr_r_Vertex));
        }
    }

    int MidTreeHeight(Vertex *pVertex, int level = 1) {
        if (pVertex == nullptr) {
            return 0;
        } else {
            return this->mid_height =
                           level + MidTreeHeight(pVertex->ptr_l_Vertex, level + 1) +
                           MidTreeHeight(pVertex->ptr_r_Vertex, level + 1);
        }
    }

    int TreeSize(Vertex *pVertex) {
        if (pVertex == nullptr)
            return 0;
        else
            return 1 + TreeSize(pVertex->ptr_l_Vertex) +
                   TreeSize(pVertex->ptr_r_Vertex);
    }

    int TreeSum(Vertex *pVertex) {
        if (pVertex == nullptr)
            return 0;
        else
            return pVertex->data + TreeSum(pVertex->ptr_l_Vertex) +
                   TreeSum(pVertex->ptr_r_Vertex);
    }
};

int main() {
    srand(time(NULL));
    cout << "Input tree size" << endl;
    int tree_size;
    cin >> tree_size;
    Tree tree;
    tree.FillVector(tree_size);
    tree.GetRoot();
    cout << endl;
    tree.PrintLeftToRight(tree.ReturnRoot());
    tree.TreeSum(tree.ReturnRoot());
    cout << "Tree size: " << tree.TreeSize(tree.ReturnRoot()) << endl;
    cout << "Tree sum: " << tree.TreeSum(tree.ReturnRoot()) << endl;
    tree.MaxTreeHeight(tree.ReturnRoot());
    return 0;
}
