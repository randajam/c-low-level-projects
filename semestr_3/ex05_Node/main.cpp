#include <iostream>

#include "List.h"

using namespace std;

int main() {
    List list;
    list.push_front(2);
    list.push_end(6);
    list.display();
    cout << list.pop_first() << endl;
    list.display();
    cout << list.isEmpty() << endl;
    cout << list.findValue(6) << endl;
    return 0;
}