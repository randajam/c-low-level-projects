#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct ListNode {
    double x;
    double y;
    int vert;
    ListNode *next;
};

void add_last(ListNode*& head, double x, double y, int vert) {
    ListNode* tmp = new ListNode;
    tmp->x = x;
    tmp->y = y;
    tmp->vert = vert;
    tmp->next = NULL;

    if(head == NULL) {
        head = tmp;
    }
    else {
        ListNode* tmp2 = head;
        while(tmp2->next != NULL) {
            tmp2 = tmp2->next;
        }
        tmp2->next = tmp;
    }

}

ListNode* create_list_by_file() {
    ListNode* head = NULL;
    fstream fin("input.txt", ios::in);
    int n = 1;
    double x, y;
    while(fin >> x >> y) {
        add_last(head, x, y, n);
        n++;
    }
    fin.close();
    return head;
}

void print_list(ListNode* head) {
    ListNode* tmp = head;
    while (tmp != NULL) {
        cout << tmp->vert << " = (" << tmp->x << "; " << tmp->y << ")" << endl;
        tmp = tmp->next;
    }
}

void delete_list(ListNode*& head) {
    while(head != NULL) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int len_list(ListNode* head) {
    ListNode* tmp = head;
    int len = 0;
    while (tmp != NULL) {
        len++;
        tmp = tmp->next;
    }
    return len;
}

double** create_matrix_graph(ListNode* head) {
    int n = len_list(head);
    double** matrix = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    for (ListNode* tmp = head; tmp != NULL; tmp = tmp->next) {
        for (ListNode* tmp2 = head; tmp2 != NULL; tmp2 = tmp2->next) {
            matrix[tmp->vert - 1][tmp2->vert - 1] = sqrt(pow(tmp->x - tmp2->x, 2) + pow(tmp->y - tmp2->y, 2));
        }
    }

    return matrix;
}

void print_matrix_graph(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << left << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void delete_matrix_graph(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void near_neighbors(double** matrix, int n) {
    int* nearest = new int[n];
    int* path = new int[n + 1];
    for (int i = 0; i < n; i++) {
        nearest[i] = 0;
    }
    for (int i = 0; i < n + 1; i++) {
        path[i] = 0;
    }

    int start = 0;
    double min_dist = 0;

    for (int count = 0; count < n; count++) {
        path[count] = start + 1;
        nearest[start] = 1;

        double dist = 0;
        for (int j = 0; j < n; j++) {
            if (!nearest[j] && dist == 0) {
                dist = matrix[start][j];
                path[count + 1] = j + 1;
            }
            if (!nearest[j] && matrix[start][j] < dist) {
                dist = matrix[start][j];
                path[count + 1] = j + 1;
            }
        }
        min_dist += dist;
        start = path[count + 1] - 1;
    }
    path[n] = 1;
    min_dist += matrix[path[n - 1] - 1][0];

    cout << "Последовательность вершин пути минимального расстояния: ";
    for (int i = 0; i < n + 1; i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    cout << "Минимальное расстояние: " << min_dist;

    delete[] nearest;
    delete[] path;
}

int main(void) {
    ListNode* head = create_list_by_file();
    print_list(head);
    int len = len_list(head);
    double** matrix = create_matrix_graph(head);
    print_matrix_graph(matrix, len);
    near_neighbors(matrix, len);

    
    delete_matrix_graph(matrix, len);
    delete_list(head);
    print_list(head);

    return 0;
}