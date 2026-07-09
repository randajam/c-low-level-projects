#include <iostream>
#include "set.h"

using namespace std;

int main() {
    Set set1(4);
    cout << set1.find('g') << endl;
    Set set2 = set1 + 'h';
    set2.print();
    Set set3 = set2 - 'h';
    set3.print();
    Set set4 = set1 + set2;
    set4.print();
    Set set5 = set2 - set1;
    set5.print();

    set5 = set1 + 'g';
    set5.print();
    cout << (set1 == set2);
    cout << endl;
    cout << (set1 == set3);
    cout << endl;
    return 0;
}