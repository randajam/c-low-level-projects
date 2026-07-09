#pragma once

#include <random>

using namespace std;

struct Node {
    int val;
    Node* next;
};

class Hash {
private:
    uint64_t p;
    uint64_t a;
    uint64_t b;

    int size;
    int M;

    Node** arr;

    int hash(int x) {
        return (a * x + b) % p % M;
    }
public:
    Hash(int N) {
        p = 1000000007;
        a = rand() % (p - 1) + 1;
        b = rand() % p;
        
        size = N;
        M = N / 100;

        arr = new Node*[M];
        for (int i = 0; i < M; i++) 
            arr[i] = nullptr;
    }

    ~Hash() {
        for (int i = 0; i < M; i++) {
            Node* cur = arr[i];
            while (cur) {
                Node* nxt = cur->next;
                delete cur;
                cur = nxt;
            }
        }
        delete[] arr;
    }

    void add(int x) {
        int h = hash(x);
        Node* new_node = new Node{x, nullptr};

        if (arr[h] == nullptr) {
            arr[h] = new_node;
        } else {
            Node* cur = arr[h];
            while (cur->next) {
                cur = cur->next;
            }
            cur->next = new_node;
        }
        
    }

    int chain_length(int i) const {
        int len = 0;
        Node* cur = arr[i];
        while (cur) {
            len++;
            cur = cur->next;
        }
        return len;
    }
};
