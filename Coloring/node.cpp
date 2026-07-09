#include "node.h"
#include <iostream>

using namespace std;

node* new_node(int id, int color = 0){
    node* n = new node;
    n->id = id;
    n->color = color;
    n->next = NULL;
    return n;
}

void append_node(node*& head, int id, int color = 0){
    node* n = new_node(id, color);
    if (head == NULL) {
        head = n;
        return;
    }
    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = n;
    return;
}

node* find_node(node* head, int id) {
    node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void print_node(node* head) {
    node* temp = head;
    while (temp != NULL) {
        cout << temp->id << " ";
        temp = temp->next;
    }
    cout << endl;
}

void print_colors(node* head) {
    node* temp = head;
    while (temp != NULL) {
        cout << temp->id << ": " << temp->color << endl;
        temp = temp->next;
    }
    cout << endl;
}

void free_node(node* head) {
   while (head != NULL) {
       node* temp = head;
       head = head->next;
       delete temp;
   }
}

int node_size(node* head) {
    int count = 0;
    node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int max_elem(node* head) {
    node* temp = head;
    int max = 0;
    while (temp != NULL) {
        if (temp->id > max) {
            max = temp->id;
        }
        temp = temp->next;
    }
    return max;
}