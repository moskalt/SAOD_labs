#include <iostream>

#include <iostream>
#include <new>
#include <ctime>

using namespace std;

class List {
private:
    struct Node {
        int data;
        Node *ptr_next;

        Node() {
            ptr_next = nullptr;
            data = 0;
        }
    };

public:
    Node *ptr_first_node;
    int sum;
    int qty_of_series;

    List() {
        ptr_first_node = nullptr;
        sum = 0;
        qty_of_series = 1;
    }

    void Add(int data) {
        Node *ptr_adding_node = new Node;
        ptr_adding_node->data = data;
        if (ptr_first_node != nullptr) {
            GetLastNode_ptr()->ptr_next = ptr_adding_node;
        } else {
            ptr_first_node = ptr_adding_node;
        }
    }

    Node *GetLastNode_ptr() const {
        Node *ptr_current_node = ptr_first_node;
        if (ptr_current_node == nullptr) {
            return nullptr;
        }
        while (ptr_current_node->ptr_next != nullptr) {
            ptr_current_node = ptr_current_node->ptr_next;
        }
        return ptr_current_node;
    }

    void PrintList() {
        Node *ptr_current_node = ptr_first_node;
        if (ptr_current_node == nullptr) {
            cout << "List is empty" << endl;
            return;
        } else {
            do {
                cout << ptr_current_node->data << "  ";
                ptr_current_node = ptr_current_node->ptr_next;
            } while (ptr_current_node != nullptr);
        }
    }

    void FillInc(int size) {
        int temp = 1;
        while (size > 0) {
            temp += rand() % 10 + 2;
            this->Add(temp);
            size--;
        }
    }

    void FillDec(int size) {
        int temp = 500;
        while (size > 0) {
            temp -= rand() % 10 + 2;
            this->Add(temp);
            size--;
        }
    }

    void FillRand(int size) {
        int temp;
        while (size > 0) {
            temp = rand() % 100 - 40;
            this->Add(temp);
            size--;
        }
    }

    void Sum() {
        this->sum = 0;
        Node *ptr_current_node = ptr_first_node;
        if (ptr_current_node == nullptr) {
            cout << "List is empty" << endl;
            return;
        } else {
            do {
                sum += ptr_current_node->data;
                ptr_current_node = ptr_current_node->ptr_next;
            } while (ptr_current_node != nullptr);
        }
    }

    void Series() {
        this->qty_of_series = 1;
        Node *ptr_current_node = ptr_first_node;
        if (ptr_current_node == nullptr) {
            cout << "List is empty" << endl;
            return;
        } else {
            do {
                if (ptr_current_node->data > ptr_current_node->ptr_next->data) {
                    qty_of_series++;
                }
                ptr_current_node = ptr_current_node->ptr_next;
            } while (ptr_current_node->ptr_next != nullptr);
        }
    }

    Node *min_element(Node *first_ptr) {
        if (first_ptr == nullptr) {
            return nullptr;
        }
        if (first_ptr->ptr_next == nullptr) {
            return first_ptr;
        }
        Node *ptr_current_node = first_ptr;
        int min = ptr_current_node->data;
        Node *min_ptr = ptr_current_node;
        do {
            if (ptr_current_node->data < min) {
                min = ptr_current_node->data;
                min_ptr = ptr_current_node;
            }

            ptr_current_node = ptr_current_node->ptr_next;
        } while (ptr_current_node != nullptr);
        return min_ptr;
    }

    void swap_data(Node *&ptr_current_node, Node *&ptr_min_node) {
        int temp = ptr_current_node->data;
        ptr_current_node->data = ptr_min_node->data;
        ptr_min_node->data = temp;
    }

    void SelectSort() {
        Node *ptr_current_node = this->ptr_first_node;
        Node *ptr_min;
        do {
            ptr_min = min_element(ptr_current_node);
            if (ptr_min == nullptr) {
                break;
            }
            swap_data(ptr_current_node, ptr_min);
            ptr_current_node = ptr_current_node->ptr_next;
        } while (ptr_current_node->ptr_next != nullptr);
    }

};


int main() {
    srand(time(NULL));
    List list;
    list.FillRand(10);
    list.PrintList();
    list.Sum();
    list.Series();
    cout << endl << "sum: " <<list.sum << endl;
    cout << "series: " << list.qty_of_series << endl;
    list.SelectSort();
    cout << endl;
    list.PrintList();
    list.Sum();
    list.Series();
    cout << endl << "sum: " <<list.sum << endl;
    cout << "series: " << list.qty_of_series << endl;
    return 0;
}
