#ifndef CONTIGUITY_LIST_H
#define CONTIGUITY_LIST_H

#include "node.h"

struct ContiguityList {
    int id;
    int len_node;
    struct node* node;
    struct ContiguityList* next;
};

ContiguityList* ContiguityList_Create(int n);
void ContiguityList_print(ContiguityList* list);
void ContiguityList_Sort(ContiguityList* list);
int ContiguityList_max_elem(ContiguityList* head);

#endif  // CONTIGUITY_LIST_H