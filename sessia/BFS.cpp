#include <iostream>
#include <fstream>

using namespace std;

struct treeNode {
    treeNode *left, *right;
    int data;
};

treeNode *createNode(int data) {
    treeNode *p = new treeNode;
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void push_tree(treeNode *&root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else {
        treeNode *p = root;
        treeNode *prev = root;
        bool flag = true;
        while (p && flag) {
            prev = p;
            if (data == p->data) { flag = false; }
            else {
                if (data > p->data) {
                    p = p->right;
                } else {
                    p = p->left;
                }
            }
        }
        if (flag) {
            if (data > prev->data) {
                prev->right = createNode(data);
            } else {
                prev->left = createNode(data);
            }
        }
    }
}

void create_tree(treeNode *&root, ifstream &fin) {
    root = NULL;
    int data;
    while (fin >> data) {
        push_tree(root, data);
    }
}

void print_tree(treeNode *root) {
    if (root) {
        print_tree(root->left);
        cout << root->data << " ";
        print_tree(root->right);
    }
    cout << endl;
}

void remove_node(treeNode *&root, int data) {
    treeNode *marker = root, *parent = root, *p, *p_parent;
    while (marker && marker->data != data) {
        parent = marker;
        if (data > marker->data) {
            marker = marker->right;
        } else {
            marker = marker->left;
        }
    }
    if (marker == NULL) {
        return;
    }
    if (marker->right && marker->left) {
        p = marker->left;
        p_parent = marker;
        while (p->right) {
            p_parent = p;
            p = p->right;
        }
        int localMax = p->data;
        if (p_parent == marker) {
            marker->left = p->left;
            delete p;
        } else {
            p_parent->right = p->left;
            delete p;
        }
        marker->data = localMax;
        return;
    } 
    else if (marker->right) {
        if (marker == parent->right) {
            p = marker;
            parent->right = marker->right;
            delete p;
        } else {
            p = marker;
            parent->left = marker->right;
            delete p;
        }
    }
    else if (marker->left) {
        if (marker == parent->left) {
            p = marker;
            parent->left = marker->left;
            delete p;
        } else {
            p = marker;
            parent->right = marker->left;
            delete p;
        }
    }
    else {
        if (marker == parent->left) {
            p = marker;
            parent->left = NULL;
            delete p;
        } else {
            p = marker;
            parent->right = NULL;
            delete p;
        }
    }
}

struct queueNode {
    /*FIFO - First In First Out*/
    treeNode *node;
    queueNode *next;
};

void push_queue(queueNode *&first, queueNode *&last, treeNode *temp) {
    queueNode *p;
    if (first) {
        p = new queueNode;
        p->node = temp;
        p->next = NULL;
        last->next = p;
        last = p;
    } else {
        p = new queueNode;
        p->node = temp;
        p->next = NULL;
        first = p;
        last = p;
    }
}

void pop_queue(queueNode *&first, treeNode *&temp) {
    queueNode *p;
    temp = first->node;
    p = first->next;
    delete first;
    first = p;
}

void BFS(treeNode *root) {
    queueNode *first, *last;
    treeNode *temp;
    temp = root;
    if (temp) {
        first = NULL;
        last = NULL;
        push_queue(first, last, temp);
        int a = 1, b = 1;
        do {
            pop_queue(first, temp);
            b--;
            a--;
            cout << temp->data << " ";

            if (temp->left) {
                push_queue(first, last, temp->left);
                b++;
                cout << "l";
            }
            if (temp->right) {
                push_queue(first, last, temp->right);
                b++;
                cout << "r";
            }
            if (a == 0) {
                cout << endl;
                a = b;
            }
        } while (first);
    }
}

int main(void) {
    treeNode *root;
    ifstream fin("text.txt");
    create_tree(root, fin);
    //print_tree(root);
    BFS(root);
    remove_node(root, 15);
    BFS(root);
    fin.close();
    return 0;
}