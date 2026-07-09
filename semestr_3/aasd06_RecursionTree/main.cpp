#include <iostream>
#include "tree.h"

using namespace std;

int main() {
    BinaryTree tree;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        tree.insert(x);
    }
    tree.print_postorder();
    cout << tree.count_value(10) << endl;
    cout << tree.sum() << endl;
    cout << tree.height() << endl;
    cout << tree.count_leaves(3) << endl;
    tree.print_leaves();

    BinaryTree tree2(tree);
    tree2.print_postorder();
    cout << (tree == tree2) << endl;

    tree.clear();

    return 0;
}