#include "list.h"
#include <iostream>
#include <fstream>

using namespace std;

void show_list(node* head) {
    if (head == nullptr) {
        return;
    }
    cout << head->data << " " << head << endl;
    show_list(head->next);
}

void read_list_from_file(node*& head, ifstream& file) {
    int x;
    if (!(file >> x)) return;

    head = new node{x, nullptr};
    read_list_from_file(head->next, file);
}

void push_end(node* head, int x) {
    if (head->next == nullptr) {
        node* elem = new node{x, nullptr};
        head->next = elem;
        return;
    }
    push_end(head->next, x);
}

void del(node*& head) {
    if (!head) return;
    del(head->next);
    delete head;
    head = nullptr;
}