#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct node {
    node* left;
    node* right;
    char data;
};

class ExprTree {
private:
    node* root;

    void delete_tree(node* node) {
        if (node) {
            delete_tree(node->left);
            delete_tree(node->right);
            delete node;
        }
    }

    node* build_prefix_rec(ifstream& in) {
        char c;
        if (!(in >> c)) return nullptr;

        node* n = new node{nullptr, nullptr, c};

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            n->left = build_prefix_rec(in);
            n->right = build_prefix_rec(in);
        }

        return n;
    }

    int eval(node* n) const {
        if (!n) return 0;

        if (n->data >= '0' && n->data <= '9') {
            return n->data - '0';
        }

        int L = eval(n->left);
        int R = eval(n->right);

        switch(n->data) {
            case '+': return L + R;
            case '-': return L - R;
            case '*': return L * R;
            case '/': return R != 0 ? L / R : 0;
            case '%': return R != 0 ? L % R : 0;
        }
        return 0;
    }

    void commute_recursive(node* n) {
        if (!n) return;

        commute_recursive(n->left);
        commute_recursive(n->right);

        if (n->data == '+' || n->data == '-' || n->data == '*') {
            std::swap(n->left, n->right);
        }
    }

public:
    ExprTree(): root(nullptr) {}
    ~ExprTree() {
        delete_tree(root);
    };

    void build_prefix(ifstream& in) {
        if (in.eof()) {
            cout << "Error opening file" << endl;
            return;
        }

        delete_tree(root);
        root = build_prefix_rec(in);
    }

    void build_infix(ifstream& in) {
        if (!in.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        delete_tree(root);
        root = nullptr;

        auto precedence = [](char op) {
            if (op == '+' || op == '-') return 1;
            if (op == '*' || op == '/') return 2;
            return 0;
        };

        auto apply_op = [&](char op, vector<node*>& st) {
            node* r = st.back(); st.pop_back();
            node* l = st.back(); st.pop_back();
            node* n = new node{l, r, op};
            st.push_back(n);
        };

        vector<node*> nodes;
        vector<char> ops;

        char c;
        while (in >> c) {
            if (isdigit(c)) {
                nodes.push_back(new node{nullptr, nullptr, c});
            }
            else if (c == '(') {
                ops.push_back(c);
            }
            else if (c == ')') {
                while (!ops.empty() && ops.back() != '(') {
                    apply_op(ops.back(), nodes);
                    ops.pop_back();
                }
                if (!ops.empty()) ops.pop_back();
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                while (!ops.empty() && precedence(ops.back()) >= precedence(c)) {
                    apply_op(ops.back(), nodes);
                    ops.pop_back();
                }
                ops.push_back(c);
            }
        }

        while (!ops.empty()) {
            apply_op(ops.back(), nodes);
            ops.pop_back();
        }

        if (!nodes.empty())
            root = nodes.back();
    }

    void expression(ofstream& out) {
        if (!out.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        struct Frame {
            node* n;
            int state; 
        };

        vector<Frame> st;
        if (root)
            st.push_back({root, 0});

        while (!st.empty()) {
            Frame& f = st.back();

            if (f.state == 0) {  
                if (f.n->left || f.n->right)
                    out << "(";

                f.state = 1;
                if (f.n->left)
                    st.push_back({f.n->left, 0});
            }
            else if (f.state == 1) {
                out << f.n->data;

                f.state = 2;
                if (f.n->right)
                    st.push_back({f.n->right, 0});
            }
            else {
                if (f.n->left || f.n->right)
                    out << ")";

                st.pop_back();
            }
        }
        out << '\n';
    }

    int evaluate() const {
        return eval(root);
    }

    void commute() { 
        commute_recursive(root);
    }
};