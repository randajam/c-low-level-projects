#include <iostream>
#include <fstream>

#include "ExpressionTree.h"

using namespace std;

int main() {
    ExprTree tree;
    ofstream out("out.txt");
    
    ifstream in_pre("input_prefix.txt");
    tree.build_prefix(in_pre);
    tree.expression(out);

    ifstream in_in("input_infix.txt");
    tree.build_infix(in_in);
    tree.expression(out);

    cout << tree.evaluate() << endl;

    tree.commute();
    cout << tree.evaluate() << endl;

    return 0;
}