#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

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
    Vertex *ptr_root = nullptr;
public:
    Tree() {
        Vertex *new_ptr = new Vertex;
        this->ptr_root = new_ptr;
    }

    Vertex *CreateVertex() {
        Vertex *pVertex = new Vertex;
        pVertex->ptr_l_Vertex = nullptr;
        pVertex->ptr_r_Vertex = nullptr;
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

    void FillVector(int tree_size, uniform_int_distribution<unsigned long long> dis, mt19937_64 mers) {
        for (int i = 0; i < tree_size; i++) {
            this->array.push_back(dis(mers) % 200 - 50);
        }
        //        sort(this->array.begin(), this->array.end());
    }

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

    void DoubleIndirection(int key, Vertex *root) {
        Vertex **head_ptr = &root;
        while (*head_ptr) {
            if (key < (*head_ptr)->data) {
                head_ptr = &((*head_ptr)->ptr_l_Vertex);
            } else if (key > (*head_ptr)->data) {
                head_ptr = &((*head_ptr)->ptr_r_Vertex);
            } else {
                break;
            }
        }
        if (*head_ptr == nullptr) {
            *head_ptr = CreateVertex();
            (*head_ptr)->data = key;
        }
    }

    void CreateRandomSearchTreeDI() {
        for (auto &item: this->array) {
            DoubleIndirection(item, this->ptr_root);
        }
    }

    void AddRecursive(int key, Vertex **temp ) {
        if(*temp == nullptr){
            *temp = CreateVertex();
            (*temp)->data = key;
        }
        else if((*temp)->data > key){
            AddRecursive(key,&(*temp)->ptr_l_Vertex);
        }
        else if((*temp)->data < key){
            AddRecursive(key, &(*temp)->ptr_r_Vertex);
        }
        else if((*temp)->data == key){
            return;
        }
    }
    void CreateRandomSearchTreeRecursive() {
        for (auto &item: this->array) {
            AddRecursive(item, &this->ptr_root);
        }
    }
};

int main() {
    random_device rd;
    mt19937_64 mersenne;
    uint64_t new_seed = time(NULL);
    mersenne.seed(new_seed);
    uniform_int_distribution<unsigned long long> dis;
    Tree tree;
    int tree_size;
    cout << "input tree_size: ";
    cin >> tree_size;
    tree.FillVector(tree_size, dis, mersenne);
    tree.CreateRandomSearchTreeDI();
    cout << "LeftToRight: " << endl;
    tree.PrintLeftToRight(tree.ReturnRoot());
    cout << endl << "TopToBottom: " << endl;
    tree.PrintTopBottom(tree.ReturnRoot());
    cout << endl;
    Tree wood;
    mersenne.seed(new_seed%12);
    wood.FillVector(tree_size, dis ,mersenne);
    wood.CreateRandomSearchTreeRecursive();
    cout << "LeftToRight: " << endl;
    tree.PrintLeftToRight(wood.ReturnRoot());
    cout << endl << "TopToBottom: " << endl;
    tree.PrintTopBottom(wood.ReturnRoot());
    cout << endl;
    return 0;
}