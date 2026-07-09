#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

class Queue {
private:
    int* data;
    int len;
    int head;
    int tail;
    int count;
public:
    Queue() {
        this->len = 10;
        data = new int[len];
        head = tail = count = 0;
    }
    Queue(int N) {
        if (N <= 0) throw std::invalid_argument("Queue size must be positive!");
        this->len = N;
        data = new int[len];
        head = tail = count = 0;
    }

    ~Queue() {
        delete[] data;
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    int max_size() const {
        return len;
    }

    int front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty!");
        }
        return data[head];
    }

    int pop_front() {
        if (empty()) {
            throw std::out_of_range("Queue is empty!");
        }
        int x = data[head];
        head = (head + 1) % len;
        count--;
        return x;
    }

    void push_back(int x) {
        if (count == len) {
            throw std::out_of_range("Queue overflow!");
        }
        data[tail] = x;
        tail = (tail + 1) % len;
        count++;
    }
};

class Player {
private:
    Queue cards;
public:
    Player(): cards() {}
    Player(int N): cards(2*N) {}

    bool empty() const { return cards.empty(); }
    int pop_card() { return cards.pop_front(); }

    void push_cards(int a, int b) {
        cards.push_back(a);
        cards.push_back(b);
    }

    void input(const int* p = nullptr) {
        int N = cards.max_size() / 2;

        if (p) {
            for (int i = 0; i < N; i++)
                cards.push_back(p[i]);
        } else {
            for (int i = 0; i < N; i++) {
                int x;
                cin >> x;
                cards.push_back(x);
            }
        }
    }
};

class Game {
private:
    Player player1, player2;
    int step;
public:
    Game(): player1(), player2(), step(0) {}
    Game(int N): player1(N), player2(N), step(0) {}

    void init() {
        cout << "Please, input first player cards:\n";
        player1.input();
        cout << "Please, input second player cards:\n";
        player2.input();
    }

    void init(const int* p1, const int* p2) {
        if (p1 == nullptr || p2 == nullptr) 
            throw std::invalid_argument("Pointers must be initialized!");
        player1.input(p1);
        player2.input(p2);
    }

    bool firstWins(int a, int b) {
        if (a == 0 && b == 9) return true;
        if (a == 9 && b == 0) return false;
        return a > b;
    }

    void make_move() {
        int a = player1.pop_card();
        int b = player2.pop_card();

        if (firstWins(a, b)) player1.push_cards(a, b);
        else player2.push_cards(a, b);

        step++;
    }

    void run() {
        bool flag = true;
        while (!player1.empty() && !player2.empty() && flag) {
            make_move();
            if (step >= 1e6) flag = false;
        }

        if (!flag) cout << "botva" << endl;
        else if (player1.empty()) cout << "second " << step << endl;
        else if (player2.empty()) cout << "first " << step << endl;
    }
};