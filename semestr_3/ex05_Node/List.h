#pragma once 

struct node {
    int data;
    node* next;
};

class List {
private:
    node* first;
public:
    List();
    void push_front(int);
    void push_end(int);
    void display();
    ~List();
    int pop_first();
    bool isEmpty();
    bool findValue(int);
};