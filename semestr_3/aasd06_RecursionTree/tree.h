#pragma once

#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->value) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return node;
    }

    bool exists(Node* node, int val) const {
        if (!node) return false;
        if (node->value == val) return true;
        if (val < node->value) return exists(node->left, val);
        return exists(node->right, val);
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->value) node->left = remove(node->left, val);
        else if (val > node->value) node->right = remove(node->right, val);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* tmp = node->right;
                delete node;
                return tmp;
            } else if (!node->right) {
                Node* tmp = node->left;
                delete node;
                return tmp;
            } else {
                Node* mn = findMin(node->right);
                node->value = mn->value;
                node->right = remove(node->right, mn->value);
            }
        }
        return node;
    }

    void preorder(Node* node) const {
        if (!node) return;
        cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->value << " ";
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    int count_value(Node* node, int val) {
        if (!node) return 0;

        return (node->value == val) +
               count_value(node->left, val) +
               count_value(node->right, val);
    }

    int sum(Node* node) {
        return node ? node->value + sum(node->left) + sum(node->right) : 0;
    }

    int height(Node* node) {
        if (!node) {
            return 0;
        } else {
            return 1 + max(height(node->left), height(node->right));
        }
    }

    int count_leaves(Node* node, int level) {
        if (!node) {
            return 0;
        } else if (level == 1) {
            return 1;
        } else {
            return count_leaves(node->left, level-1) + count_leaves(node->right, level-1);
        }
    }

    void print_leaves(Node* node) {
        if (!node) return;
        if (!node->left && !node->right) {
            cout << node->value << " ";
        } else {
            print_leaves(node->left);
            print_leaves(node->right);
        }
    }

    Node* copy(Node* other) {
        if (!other) {
            return nullptr;
        } else {
            Node* newNode = new Node(other->value);
            newNode->left = copy(other->left);
            newNode->right = copy(other->right);
            return newNode;
        }
    }

    bool isEqual(Node* node1, Node* node2) {
        if (!node1 && !node2) {
            return true;
        } else if (!node1 || !node2) {
            return false;
        } else {
            return node1->value == node2->value && isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree& other) {
        if (other.root) {
            root = copy(other.root);
        } else {
            root = nullptr;
        }
    }

    ~BinaryTree() {
        destroy(root);
    }

    void insert(int val) {
        root = insert(root, val);
    }

    bool exists(int val) const {
        return exists(root, val);
    }

    void remove(int val) {
        root = remove(root, val);
    }

    void print_preorder() const {
        preorder(root);
        cout << endl;
    }

    void print_inorder() const {
        inorder(root);
        cout << endl;
    }

    void print_postorder() const {
        postorder(root);
        cout << endl;
    }

    int count_value(int val) {
        return count_value(root, val);
    }

    int sum() {
        return sum(root);
    }

    int height() {
        return height(root);
    }

    int count_leaves(int level) {
        return count_leaves(root, level);
    }

    void print_leaves() {
        print_leaves(root);
        cout << endl;
    }

    void clear() {
        destroy(root);
        root = nullptr;
    }

    bool operator==(const BinaryTree& other) {
        if (root && other.root) {
            return isEqual(root, other.root);
        } else {
            return !root && !other.root;
        }
    }
};