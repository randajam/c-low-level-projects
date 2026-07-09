#include <iostream>
#include <fstream>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<stdio.h>

using namespace std;

struct graph {
    double x;
    double y;
    int vert;
    graph* next;
};

void addLast(graph*& first, int i, double a, double b) {
    graph* tmp = new graph;
    tmp->x = a;
    tmp->y = b;
    tmp->vert = i;
    tmp->next = NULL;

    if (first == NULL) {
        first = tmp;
    } else {
        graph* p = first;
        while (p != NULL && p->next != NULL) {
            p = p->next;
        }   
        p->next = tmp;
    }
}

graph* create_list() {
    graph* first = NULL;
    ifstream fin("input.txt");
    double a, b;
    int i = 1;
    while (fin >> a >> b) {
        addLast(first, i++, a, b);
    }

    fin.close();

    return first;
}

void show_list(graph* first) {
    graph* p = first;
    while (p) {
        cout << p->vert << " = (" << p->x << ", " << p->y << ")" << endl;
        p = p->next;
    }
    cout << endl;
}

int size_list(graph* first) {
    int i = 1;
    while (first) {
        first = first->next;
        i++;
    }
    return i;
}

double** matrix(graph* first, int n) {
    graph* p = first;
    graph* p2 = first;
    
    double** A = new double* [n + 1];

    for (int i = 0; i < n + 1; i++) {
        A[i] = new double[n + 1];
    }
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            A[i][j] = 0;
        }
    }
    for (int i = 0; i < n + 1; i++) {
        A[0][i] = i;
        A[i][0] = i;
    }

    while (p) {
        while (p2) {
            if (p->vert != p2->vert) {
                A[p->vert][p2->vert] = sqrt((p->x - p2->x) * (p->x - p2->x) + (p->y - p2->y) * (p->y - p2->y));
            }
            p2 = p2->next;
        }
        p = p->next;
        p2 = first;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << left << A[i][j] << " ";
        }
        cout << endl;
    }

    return A;
}

void perebor(double** A, int n) {
    double min = 0, cur = 0;
    int* B = new int[n + 1];
    for (int i = 0; i < n + 1; i++) {
        B[i] = i + 1;
    }
    B[n - 1] = 1;

    for (int i = 0; i < n - 1; i++) {
        min += A[B[i]][B[i + 1]];
    }

    while(next_permutation(B + 1, B + n - 1)) {
        for (int i = 0; i < n - 1; i++)
            cur += A[B[i]][B[i + 1]];
        if (cur < min)
            min = cur;
        cur = 0;
    }

    cout << "Минимальная длина пути: " << min << endl;
}

void random(double** A, int n) {
    double path = 0;
    int r;
    int* B = new int[n + 1];
    int* C = new int[n - 2];
    B[0] = 1;
    B[n - 1] = 1;

    for (int i = 0; i < n - 2; i++) {
        C[i] = i + 2;
    }

    srand(time(NULL));

    for (int i = 1; i < n - 1; i++) {
        do {
            r = rand() % (n - 2);
        } while (C[r] == 0);

        B[i] = C[r];
        C[r] = 0;
    }

    cout << "Случайный маршрут: ";
    for (int i = 0; i < n; i++) {
        cout << B[i] << " ";
    }
    for (int i = 0; i < n - 1; i++) {
        path += A[B[i]][B[i + 1]];
    }

    cout << "-> его путь: " << path << endl;
}

int main(void) {
    graph* first = create_list();
    show_list(first);
    int n = size_list(first);
    double** A = matrix(first, n);
    
    perebor(A, n);
    random(A, n);

    return 0;
}