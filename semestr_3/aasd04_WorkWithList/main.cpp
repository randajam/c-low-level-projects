#include <iostream>

struct node {
    int data;
    node* next;
};

// Создание списка из массива для удобства
node* create_list(const int arr[], int n) {
    if (n == 0) return nullptr;
    node* head = new node{arr[0], nullptr};
    node* tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = new node{arr[i], nullptr};
        tail = tail->next;
    }
    return head;
}

// Очистка списка
void del_list(node* head) {
    while (head) {
        node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void del_elem(node*& head, int a) {
    if (head == nullptr) return;
    else if (head->data == a) {
        node* tail = head;
        head = tail->next;
        delete tail;
        return;
    }
    del_elem(head->next, a);
}

void del_all_elem(node*& head, int a) {
    if (head == nullptr) return;
    else if (head->data == a) {
        node* tail = head;
        head = tail->next;
        delete tail;
    }
    del_all_elem(head->next, a);
}

void insert(node*& head, int a, int y) {
    if (head == nullptr) {
        head = new node{a, nullptr};
        return;
    } else if (head->data == a) {
        node* elem = new node{y, head->next};
        head->next = elem;
        return;
    }
    insert(head->next, a, y);
}

void copy(node* head, node*& new_head) {
    if (head == nullptr) {
        new_head = nullptr;
    } else {
        new_head = new node{head->data, nullptr};
        copy(head->next, new_head->next);
    }
}

bool is_equal(node* head1, node* head2) {
    if (head1 == nullptr && head2 == nullptr) {
        return true;
    } else if (head1 == nullptr || head2 == nullptr) {
        return false;
    } else {
        return head1->data == head2->data && is_equal(head1->next, head2->next);
    }
}

// Вывод списка
void print_list(node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    int arr[] = {1, 2, 3, 1, 5};
    node* head = create_list(arr, 5);

    std::cout << "List: ";
    print_list(head);

    del_all_elem(head, 1);
    print_list(head);

    insert(head, 3, 8);
    print_list(head);

    node* new_head;
    copy(head, new_head);
    print_list(new_head);

    std::cout << is_equal(head, new_head) << "\n";
    std::cout << is_equal(head, nullptr) << "\n";

    del_list(head);
    del_list(new_head);
    
    return 0;
}