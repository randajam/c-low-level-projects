#include <iostream>

using namespace std;

struct node {
    char ch;
    node* next;
    node* end;
};

void add(node* head, char ch) {
    if (head == nullptr) {
        node* elem = new node;
        elem->ch = ch;
        elem->next = nullptr;
        elem->end = nullptr;
        head = elem;
    } else {
        node* tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        node* elem = new node;
        elem->ch = ch;
        elem->next = nullptr;
        elem->end = tmp;
        tmp->next = elem;
    }
}

void print(node* head) {
    node* tmp = head;
    while (tmp != nullptr) {
        cout << tmp->ch;
        tmp = tmp->next;
    }
}

bool is_palindrom(node* head) {
    node* left = head;
    node* right = head;
    while (right->next != nullptr) {
        right = right->next;
    }
    while ((left != right) && (left->next != right)) {
        if (left->ch != right->ch) {
            return false;
        }
        left = left->next;
        right = right->end;
    }
    return true;
}

int main() {
    node* head = nullptr;
    char ch;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ch;
        add(head, ch);
    }
    
    cout << head;
    return 0;
}