#include <iostream>
#include <fstream>
#include "list.h"
using namespace std;

int main() {
    node* head = nullptr;

    ifstream in("input.txt");
    read_list_from_file(head, in);

    show_list(head);
    push_end(head, 4);
    push_end(head, 7);

    cout << "----\n";
    show_list(head);

    del(head);
    return 0;
}
