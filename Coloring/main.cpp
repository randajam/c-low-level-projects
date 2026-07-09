#include <iostream>

#include "node.h"
#include "contiguity_list.h"

using namespace std;

int main() {
    int n;
    cout << "Введите количество элементов в списке: ";
    cin >> n;

    // Создаем список смежности
    ContiguityList* list = ContiguityList_Create(n);
    ContiguityList_print(list);
    ContiguityList_Sort(list);
    ContiguityList_print(list);

    // Создаем массив цветов
    node* colors_list = NULL;
    int last_color = 0;

    ContiguityList* tmp_list = list;

    // Пока не дойдем до конца списка смежности
    while (tmp_list != NULL) {
        // Если текущей вершины нет в списке цветов
        if (find_node(colors_list, tmp_list->id) == NULL) {
            last_color++;
            append_node(colors_list, tmp_list->id, last_color);
            // Ищем все не смежные вершины с текущей вершиной
            for (int i = 1; i <= n; i++) {
                if (i != tmp_list->id && find_node(colors_list, i) == NULL) {
                    if (find_node(tmp_list->node, i) == NULL) {
                        // Если нашли не смежную вершину, то добавляем ее в список цветов с текущим цветом
                        append_node(colors_list, i, last_color);
                    }
                }
            }
        }
        tmp_list = tmp_list->next;
    }

    print_colors(colors_list);

    return 0;
}