#pragma once 

#include <iostream>
#include <fstream>

using namespace std;

struct node {
    int data;
    node* next;
};

void show_list(node* head);
void read_list_from_file(node*& head, ifstream& file);
void push_end(node* head, int elem);
void del(node*& head);