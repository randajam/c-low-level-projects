#include <iostream>

#include "contiguity_list.h"
#include "node.h"

using namespace std;

ContiguityList* ContiguityList_Create(int n) {
    ContiguityList* head = NULL;
    ContiguityList* tail = NULL;
    for (int i = 1; i <= n; i++) {
        if (head == NULL) {
            head = new ContiguityList;
            head->id = i;
            head->node = NULL;
            head->next = NULL;
            tail = head;
        }
        else {
            tail->next = new ContiguityList;
            tail->next->id = i;
            tail->next->node = NULL;
            tail->next->next = NULL;
            tail = tail->next;
        }

        int x = 0;
        do {
            cin >> x;
            if (x != 0) {
                append_node(tail->node, x, 0);
                //tail->len_node++;
            }
        } while (x != 0);
        cin >> tail->len_node;
    }
    return head;
}

void ContiguityList_print(ContiguityList* head) {
    while (head != NULL) {
        cout << "Node " << head->id << ": ";
        node* tmp = head->node;
        while (tmp != NULL) {
            cout << tmp->id << " ";
            tmp = tmp->next;
        }
        cout << "Len: " << head->len_node;
        cout << endl;
        head = head->next;
    }
    cout << endl;
}

void ContiguityList_Sort(ContiguityList* head) {
    ContiguityList* tmp1 = head;
    ContiguityList* tmp2 = head;
    while (tmp1 != NULL) {
        tmp2 = head;
        while (tmp2->next != NULL) {
            if (tmp2->len_node > tmp2->next->len_node) {
                int tmp_id = tmp2->id;
                tmp2->id = tmp2->next->id;
                tmp2->next->id = tmp_id;

                int tmp_len_node = tmp2->len_node;
                tmp2->len_node = tmp2->next->len_node;
                tmp2->next->len_node = tmp_len_node;

                node* tmp_node = tmp2->node;
                tmp2->node = tmp2->next->node;
                tmp2->next->node = tmp_node;
            }
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
    }
}

int ContiguityList_max_elem(ContiguityList* head) {
    int elem = 0;
    while (head != NULL) {
        if (max_elem(head->node) > elem) {
            elem = max_elem(head->node);
        }
        head = head->next;
    }
    return elem;
}
