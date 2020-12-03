#include <ctime>
#include <iostream>
#include <new>

using namespace std;

class forward_list {

private:
    int sum;
    int qty_of_series;

    struct Node {
        int data;
        Node *ptr_next;

        Node() {
            ptr_next = nullptr;
            data = 0;
        }
    };

    Node *head;

public:
    forward_list() {
        head = nullptr;
        sum = 0;
        qty_of_series = 0;
    }

    ~forward_list() {
        Node* temp = head;
        while (head != nullptr) {
            temp = head->ptr_next;
            delete temp;
        }
    }

    int get_sum() const {
        return this->sum;
    }

    int get_series() const {
        return this->qty_of_series;
    }

    Node *get_last_node_ptr() const {
        Node *ptr_current_node = head;
        if (ptr_current_node == nullptr) {
            return nullptr;
        }
        while (ptr_current_node->ptr_next != nullptr) {
            ptr_current_node = ptr_current_node->ptr_next;
        }
        return ptr_current_node;
    }

    void add_node(int data) {
        Node *ptr_adding_node = new Node;
        ptr_adding_node->data = data;
        if (head != nullptr) {
            get_last_node_ptr()->ptr_next = ptr_adding_node;
        } else {
            head = ptr_adding_node;
        }
    }

    void printList() {
        Node *ptr_current_node = head;
        if (ptr_current_node == nullptr) {
            cout << "forward_list is empty" << endl;
        } else {
            do {
                cout << ptr_current_node->data << "  ";
                ptr_current_node = ptr_current_node->ptr_next;
            } while (ptr_current_node != nullptr);
        }
    }

    void fillInc(int size) {
        int temp = 1;
        while (size > 0) {
            temp += rand() % 10 + 2;
            this->add_node(temp);
            size--;
        }
    }

    void fillDec(int size) {
        int temp = 500;
        while (size > 0) {
            temp -= rand() % 10 + 2;
            this->add_node(temp);
            size--;
        }
    }

    void fillRand(int size) {
        int temp;
        while (size > 0) {
            temp = rand() % 100 - 40;
            this->add_node(temp);
            size--;
        }
    }

    void count_sum() {
        this->sum = 0;
        Node *ptr_current_node = head;
        if (ptr_current_node == nullptr) {
            cout << "forward_list is empty" << endl;
        } else {
            do {
                sum += ptr_current_node->data;
                ptr_current_node = ptr_current_node->ptr_next;
            } while (ptr_current_node != nullptr);
        }
    }

    void count_series() {
        this->qty_of_series = 0;
        Node *ptr_current_node = head;
        if (ptr_current_node == nullptr) {
            cout << "forward_list is empty" << endl;

        } else {
            qty_of_series++;
            do {
                if (ptr_current_node->data > ptr_current_node->ptr_next->data) {
                    qty_of_series++;
                }
                ptr_current_node = ptr_current_node->ptr_next;
            } while (ptr_current_node->ptr_next != nullptr);
        }
    }

    static Node *find_min_element(Node *first_ptr) {
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

    static void swap_nodes(Node *&ptr_current_node, Node *&ptr_min_node) {
        int temp_data = ptr_current_node->data;
        ptr_current_node->data = ptr_min_node->data;
        ptr_min_node->data = temp_data;
    }

    void selectSort() {
        Node *ptr_current_node = this->head;
        Node *ptr_min;
        int i = 0;
        do {
            ptr_min = find_min_element(ptr_current_node);
            if (ptr_min == nullptr) {
                break;
            }
            swap_nodes(ptr_current_node, ptr_min);
            ptr_current_node = ptr_current_node->ptr_next;
            i++;
        } while (ptr_current_node->ptr_next != nullptr);
    }
};


int main() {
    srand(time(NULL));
    forward_list list;
    list.fillRand(10);
    list.printList();
    list.count_sum();
    list.count_series();
    cout << endl
         << "sum: " << list.get_sum() << endl;
    cout << "series: " << list.get_series() << endl;
    list.selectSort();
    cout << endl;
    list.printList();
    list.count_sum();
    list.count_series();
    cout << endl
         << "sum: " << list.get_sum() << endl;
    cout << "series: " << list.get_series() << endl;
    return 0;
}
