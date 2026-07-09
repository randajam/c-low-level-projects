#ifndef NODE_H_
#define NODE_H_

struct node {
    int id;
    int color;
    struct node *next;
};

node* new_node(int id, int color);
void append_node(node*& head, int id, int color);
node* find_node(node* head, int id);
void print_node(node* head);
void print_colors(node* head);
void free_node(node* head);
int node_size(node* head);
int max_elem(node* head);

#endif // NODE_H_