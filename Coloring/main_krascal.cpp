#include <iostream>

#include "node.h"
#include "contiguity_list.h"

using namespace std;

/*
1 2 0 6
2 5 0 3
5 6 0 6
6 4 0 2
4 1 0 5
1 3 0 1
4 3 0 5
6 3 0 4
5 3 0 6
2 3 0 5
*/

int main(void) {
    int n;
    cout << "Введите количество элементов в списке: ";
    cin >> n;

    // Создаем список смежности
    ContiguityList* list = ContiguityList_Create(n);
    ContiguityList_print(list);
    ContiguityList_Sort(list);
    ContiguityList_print(list);

    // Создаем массив с вершинами
    node* filter = NULL;
    for (int i = 1; i < n + 1; i++) {
        append_node(filter, i, 0);
    }
    n = ContiguityList_max_elem(list);
    node* vertex = NULL;
    for (int i = 1; i < n + 1; i++) {
        append_node(vertex, i, 0);
    }

    ContiguityList* tmp = list;
    int connect_component = 1;
    while (tmp != NULL) {
        int ver1, ver2;
        ver1 = tmp->node->id;
        ver2 = tmp->node->next->id;
        int n1 = find_node(vertex, ver1)->color;
        int n2 = find_node(vertex, ver2)->color;
        
        if (n1 == 0 && n2 == 0) {
            find_node(vertex, ver1)->color = connect_component;
            find_node(vertex, ver2)->color = connect_component;
            find_node(filter, tmp->id)->color = 1;
        }
        else if (n1 != n2 != 0) {
            if (n1 > n2) {
                node* tmp_list = vertex;
                while (tmp_list != NULL) {
                    if (tmp_list->color == n2) {
                        tmp_list->color = n1;
                    }
                    tmp_list = tmp_list->next;
                }
            } else {
                node* tmp_list = vertex;
                while (tmp_list != NULL) {
                    if (tmp_list->color == n1) {
                        tmp_list->color = n2;
                    }
                    tmp_list = tmp_list->next;
                }
            }         
            find_node(filter, tmp->id)->color = 1;   
        } 

        connect_component++;
        tmp = tmp->next;
    }

    print_node(vertex);
    print_colors(vertex);

    print_node(filter);
    print_colors(filter);

    return 0;
}