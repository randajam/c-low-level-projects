#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <climits>

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
            if (matrix[tmp->vert - 1][tmp2->vert - 1] == 0) {
                matrix[tmp->vert - 1][tmp2->vert - 1] = INFINITY;
            }
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
    cout << endl;
}

void delete_matrix_graph(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void constants(double** matrix, int n, double*& d_i, double*& d_j, bool** filter) {
    for (int i = 0; i < n; i++) {
        double min = INFINITY;
        for (int j = 0; j < n; j++) {
            if (filter[i][j] == 1 && matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        if (min != INFINITY) {
            d_i[i] = min;
        } else {
            d_i[i] = 0;
        }
    }       
    // Reduce columns
    for (int j = 0; j < n; j++) {
        double min = INFINITY;
        for (int i = 0; i < n; i++) {
            if (filter[i][j] == 1 && matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        if (min != INFINITY) {
            d_j[j] = min;
        } else {
            d_j[j] = 0;
        }
    }

}

void reduce_matrix(double**& matrix, int n, double*& d_i, double*& d_j) {
    // Reduce rows
    for (int i = 0; i < n; i++) {
        double min = INFINITY;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        d_i[i] = min;
        if (min != INFINITY) {
           for (int j = 0; j < n; j++) {
                matrix[i][j] -= min;
                if (matrix[i][j] <= 0.0000000001) {
                    matrix[i][j] = 0;
                }
           }
        }
    }       
    // Reduce columns
    for (int j = 0; j < n; j++) {
        double min = INFINITY;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        d_j[j] = min;
        if (min != INFINITY) {
            for (int i = 0; i < n; i++) {
                matrix[i][j] -= min;
                if (matrix[i][j] <= 0.0000000001) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

void rebro_vetv(double** matrix, int n, int& i_vetv, int& j_vetv, bool** filter) {
    double* d_i = new double[n]; // Вектор минимальных элементов в строках
    double* d_j = new double[n]; // Вектор минимальных элементов в столбцах
    i_vetv = 0;
    j_vetv = 0;
    double max_sum = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (filter[i][j] == 1 && matrix[i][j] == 0) {
                matrix[i][j] = INFINITY; // Устанавливаем нулевые ребра на INFINITY
                constants(matrix, n, d_i, d_j, filter); // Optimization
                //cout << d_i[i] << " " << d_j[j] << " " << i << ' ' << j << "\n";
                if ((d_i[i] + d_j[j]) > (max_sum)) {
                    i_vetv = i;
                    j_vetv = j;
                    max_sum = d_i[i] + d_j[j];
                    //cout << max_sum << " " << i_vetv << ' ' << j_vetv << "\n";
                }
                matrix[i][j] = 0; // Возвращаем нулевые ребра на место
            }
        }
    }
}

double exclusion_rebro(double** matrix, int n, int i_vetv, int j_vetv, bool** filter) {
    double* d_i = new double[n]; // Вектор минимальных элементов в строках
    double* d_j = new double[n]; // Вектор минимальных элементов в столбцах
    double tmp = matrix[i_vetv][j_vetv];

    matrix[i_vetv][j_vetv] = INFINITY;
    constants(matrix, n, d_i, d_j, filter);
    //reduce_matrix(matrix, n, d_i, d_j);
    matrix[i_vetv][j_vetv] = tmp;

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += d_i[i];
        sum += d_j[i];
    }
    return sum;
}

double include_rebro(double** matrix, int n, int i_vetv, int j_vetv, bool** filter) {
    double* d_i = new double[n]; // Вектор минимальных элементов в строках
    double* d_j = new double[n]; // Вектор минимальных элементов в столбцах
    double tmp = matrix[j_vetv][i_vetv];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == i_vetv || j == j_vetv) {
                filter[i][j] = 0;
            }
        }
    }
    
    constants(matrix, n, d_i, d_j, filter);
    matrix[j_vetv][i_vetv] = INFINITY;
    //reduce_matrix(matrix, n, d_i, d_j);
    matrix[j_vetv][i_vetv] = tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == i_vetv || j == j_vetv) {
                filter[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << d_i[i] << " ";
    }
    cout << endl;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += d_i[i] + d_j[i];
    }

    return sum;
}

void print_matrix_graph_filter(double** matrix, int n, bool** filter) {
    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (filter[i][j]) {
                cout << setw(11) << matrix[i][j];
            }
        }
        if (filter[i][0]) {
            cout << "\n";
        }
    }
}

double branch_and_bound(double** matrix, bool** filter, int n, double h_prev, int level, double H) {
    double* d_i = new double[n]; // Вектор минимальных элементов в строках
    double* d_j = new double[n]; // Вектор минимальных элементов в столбцах

    cout << "\n------------------------\n";
    cout << "Level = " << level << "\n";
    cout << "H = " << H << "\n";
    cout << "h_prev = " << h_prev << "\n";
    print_matrix_graph_filter(matrix, n, filter);
    cout << "Filter:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << filter[i][j];
        }
        cout << "\n";
    }
    cout << "------------------------\n";

    if (level == 0) {
        reduce_matrix(matrix, n, d_i, d_j);
        for (int i = 0; i < n; ++i) {
            H += d_i[i] + d_j[i];
        }
    }

    int razm = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (filter[i][j] == 1) {
                razm++;
            }
        }
    }
    if (razm == 4) {
        cout << "--------RAZM---------\n";
        return H;
    }
    int i_vetv = 0, j_vetv = 0;
    rebro_vetv(matrix, n, i_vetv, j_vetv, filter);
    cout << i_vetv << ' ' << j_vetv << "\n";

    double H_exclude = exclusion_rebro(matrix, n, i_vetv, j_vetv, filter);
    double H_include = include_rebro(matrix, n, i_vetv, j_vetv, filter);
    cout << "H_exclude = " << H_exclude << endl;
    cout << "H_include = " << H_include << endl;
    cout << "------------------------\n";
    if (level == 5) {
        cout << "---LEVEL---\n";
        return H;
    }
    double tmp_h;
    if (H_include <= H_exclude + 0,0000001 || H_include <= H_exclude + 0,0000001) {
        cout << "INFINITY\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == i_vetv || j == j_vetv) {
                    filter[i][j] = 0;
                }
            }
        }

        //double tmp = matrix[j_vetv][i_vetv];
        double** matrix1 = new double*[n]; // Выделяем память для указателей на строки
        for (int i = 0; i < n; i++) {
            matrix1[i] = new double[n]; // Выделяем память для каждой строки
            for (int j = 0; j < n; j++) {
                matrix1[i][j] = matrix[i][j];
            }
        }
        constants(matrix1, n, d_i, d_j, filter);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix1[i][j] -= d_i[i];
            }
        }
        matrix1[j_vetv][i_vetv] = INFINITY;

        int j_prev = -1;
        for (int i = 0; i < n; i++) {
            bool flag = false;
            for (int j = 0; j < n; j++) {
                if (!flag && filter[i][j] == 1 && j_prev == j - 1) {
                    matrix1[i][j] = INFINITY;
                    flag = true;
                    j_prev = j;
                }
            }
        }
        //reduce_matrix(matrix1, n, d_i, d_j);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << filter[i][j];
            }
            cout << "\n";
        }
        tmp_h = branch_and_bound(matrix1, filter, n, H + H_exclude, level + 1, H + H_include);
        //matrix[j_vetv][i_vetv] = tmp;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == i_vetv || j == j_vetv) {
                    filter[i][j] = 1;
                }
            }
        }
        cout <<"+++++++++++++\n";
    } /*else if (H_exclude < H_include) {
        cout << "EXL\n";
        matrix[i_vetv][j_vetv] = INFINITY;
        tmp_h = branch_and_bound(matrix, filter, n, H + H_include, level + 1, H + H_exclude);
    }*/

    if (tmp_h > H + H_exclude) {
        matrix[i_vetv][j_vetv] = INFINITY;
        reduce_matrix(matrix, n, d_i, d_j);
        tmp_h = branch_and_bound(matrix, filter, n, INFINITY, level + 1, H + H_exclude);
    }

    return tmp_h;
}

int main(void) {
    ListNode* head = create_list_by_file();
    print_list(head);
    int len = len_list(head);
    double** matrix = create_matrix_graph(head);
    /*
    int len = 5;
    double** matrix = new double*[len]; // Выделяем память для указателей на строки
    
    for(int i = 0; i < len; ++i) {
        matrix[i] = new double[len]; // Выделяем память для каждой строки
    }

    matrix[0][0] = INFINITY; matrix[0][1] = 20; matrix[0][2] = 18; matrix[0][3] = 12; matrix[0][4] = 8;
    matrix[1][0] = 5;       matrix[1][1] = INFINITY; matrix[1][2] = 14; matrix[1][3] = 7; matrix[1][4] = 11;
    matrix[2][0] = 12;      matrix[2][1] = 18; matrix[2][2] = INFINITY; matrix[2][3] = 6; matrix[2][4] = 11;
    matrix[3][0] = 11;      matrix[3][1] = 17; matrix[3][2] = 11; matrix[3][3] = INFINITY; matrix[3][4] = 12;
    matrix[4][0] = 5;       matrix[4][1] = 5; matrix[4][2] = 5; matrix[4][3] = 5; matrix[4][4] = INFINITY;
    print_matrix_graph(matrix, len);
*/
    bool **filter = new bool*[len];
    for (int i = 0; i < len; i++) {
        filter[i] = new bool[len];
        for (int j = 0; j < len; j++) {
            filter[i][j] = 1;
        }
    }

    double H = branch_and_bound(matrix, filter, len, INFINITY, 0, 0);
    cout << "H = " << H << endl;

    delete_matrix_graph(matrix, len);
    delete_list(head);
    print_list(head);

    return 0;
}