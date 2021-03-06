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

        Vertex() {
            ptr_l_Vertex = nullptr;
            ptr_r_Vertex = nullptr;
            data = 0;
        }
    };

    vector<int> array;

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
            this->array.push_back(rand() % 200 - 100);
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
            return 1 + max(MaxTreeHeight(pVertex->ptr_l_Vertex), MaxTreeHeight(pVertex->ptr_r_Vertex));
        }
    }

    float MidTreeHeight(Vertex *pVertex, int level) {
        if (pVertex == nullptr) {
            return 0;
        } else {
            return level + MidTreeHeight(pVertex->ptr_l_Vertex, level + 1) +
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

    int SearchTree(Vertex *root, int key) {
        if (key == root->data) {
            cout << root->data;
            return 1;
        }
        if (root->ptr_r_Vertex == nullptr && root->ptr_l_Vertex == nullptr) {
            return 0;
        }
        if (key > root->data) {
            cout << root->data << " ";
            SearchTree(root->ptr_r_Vertex, key);
        } else if (key < root->data) {
            cout << root->data << " ";
            SearchTree(root->ptr_l_Vertex, key);
        }

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
    cout << endl;
    tree.PrintTopBottom(tree.ReturnRoot());
    cout << endl;
    tree.TreeSum(tree.ReturnRoot());
    cout << endl;
    int size = tree.TreeSize(tree.ReturnRoot());
    int sum = tree.TreeSum(tree.ReturnRoot());
    int height = tree.MaxTreeHeight(tree.ReturnRoot());
    float midHeight = tree.MidTreeHeight(tree.ReturnRoot(), 1);
    cout << "Tree size: " << size << endl;
    cout << "Tree sum: " << sum << endl;
    cout << "Tree height: " << height << endl;
    cout << "Tree mid-height: " << midHeight / size << endl;
    cout << "Input key" << endl;
    int key;
    cin >> key;
    bool check = tree.SearchTree(tree.ReturnRoot(), key);
    if (check == 1) {
        cout << endl << "True";
    }else
        cout << endl << "False";
    return 0;
}
