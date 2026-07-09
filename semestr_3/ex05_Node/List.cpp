#include "List.h"
#include <iostream>

using namespace std;

List::List () {
    this->first = nullptr;
}

void List::push_front(int a) {
    node* elem = new node;
    elem->data = a;
    elem->next = this->first;
    if (this->first == nullptr) {
        this->first = elem;
        return;
    }
    this->first = elem;
}

void List::push_end(int a) {
    node* elem = new node;
    elem->data = a;
    elem->next = nullptr;

    if (this->first == nullptr) {
        this->first = elem;
        return;
    }

    node* tmp = this->first;
    while (tmp->next != nullptr) {
        tmp = tmp->next;
    }
    tmp->next = elem;
}

void List::display() {
    node* tmp = this->first;
    while (tmp != nullptr) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

List::~List() {
    node* tmp = this->first;
    while(tmp != nullptr) {
        if (tmp->next == nullptr) {
            delete tmp;
            tmp = nullptr;
        } else {
            node* tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
    }
}

int List::pop_first() {
    if (this->first == nullptr) {
        return -1;
    } else {
        node* tmp = this->first;
        this->first = this->first->next;
        int a = tmp->data;
        delete tmp;
        return a;
    }
}

bool List::isEmpty() {
    if (this->first == nullptr) {
        return true;
    }
    return false;
}

bool List::findValue(int a) {
    node* tmp = this->first;
    while (tmp != nullptr) {
        if (tmp->data == a) {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}