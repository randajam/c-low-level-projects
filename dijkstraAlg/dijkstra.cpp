#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct graph {
    int x;
    int y;
    float weight;
};

struct node {
    struct graph graph;
    struct node* next;
};
  
node* init_elem(int x = 0, int y = 0, float weight = 0.0) {
    node* tmp = new node;
    tmp->graph.x = x;
    tmp->graph.y = y;
    tmp->graph.weight = weight;
    tmp->next = nullptr;

    return tmp;
}
  
void print_nodes(node* graphs, ofstream& fout) {
    node* tmp = graphs;
    while (tmp != nullptr) {
      fout << "(" << tmp->graph.x << "," << tmp->graph.y << ") weight:" << tmp->graph.weight << "\n";
      tmp = tmp->next;
    }
}
  
void add_last(node*& graphs, int x, int y, float weight) {
    if (graphs == nullptr) {
      graphs = init_elem(x, y, weight);
      return;
    }
  
    node* tmp = graphs;
    while (tmp->next != nullptr) {
      tmp = tmp->next;
    }
  
    tmp->next = init_elem(x, y, weight);
}
  
node* read_graph(ifstream& fin) {
    int x, y;
    float weight;
    node* graph = nullptr;
    while (fin >> x >> y >> weight) {
      add_last(graph,x,y,weight);
    }
    return graph;
}

bool rebro(node* graph, int x, int y) {
    node* tmp = graph;
    while (tmp != nullptr) {
        if (tmp->graph.x == x and tmp->graph.y == y or tmp->graph.x == y and tmp->graph.y == x) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void matrix(node* graph) {
    int max_versh = 0;
    node* tmp = graph;
    for (; tmp != nullptr; tmp = tmp->next) {
        if (tmp->graph.x > max_versh)
            max_versh = tmp->graph.x;
        if (tmp->graph.y > max_versh)
            max_versh = tmp->graph.y;
    }
    max_versh++;
    int** a = new int*[max_versh];
    for (int i = 0; i < max_versh; i++) {
        a[i] = new int[max_versh];
        for (int j = 0; j < max_versh; j++)
            a[i][j] = 0;
    }
    tmp = graph;
    for (; tmp != nullptr; tmp = tmp->next) {
        a[tmp->graph.x][tmp->graph.y] = tmp->graph.weight;
        a[tmp->graph.y][tmp->graph.x] = tmp->graph.weight;
    }
    for (int i = 0; i < max_versh; i++) {
        if (i == 0) {
            printf("%d", i);
        } else {
            printf("%4d", i);
        }
    }
    cout << "\n";
    for (int i = 1; i < max_versh; i++) {
        cout << i;
        for (int j = 1; j < max_versh; j++) {
            printf("%4d", a[i][j]);
        }
        cout << "\n";
    }
    for (int i = 0; i < max_versh; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int max_versh(node* graph) {
    node* temp = graph;
    int SIZE = 0;
    while (temp != NULL) {
        if (temp->graph.x > SIZE) {
            SIZE = temp->graph.x;
        }
        if (temp->graph.y > SIZE) {
            SIZE = temp->graph.y;
        }
        temp = temp->next;
    }
    return SIZE;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    node* graphs = read_graph(fin);
    matrix(graphs);
    fin.close();
    fout.close();
    
    int SIZE = max_versh(graphs);

    int** a = new int*[SIZE];
    for (int i = 0; i < SIZE; i++) {
        a[i] = new int[SIZE];
        for (int j = 0; j < SIZE; j++)
            a[i][j] = 0;
    }
    
    node* tmp = graphs;
    for (; tmp != NULL; tmp = tmp->next) {
        a[tmp->graph.x - 1][tmp->graph.y - 1] = tmp->graph.weight;
        a[tmp->graph.y - 1][tmp->graph.x - 1] = tmp->graph.weight;
    }

    printf("\nМатрица смежности: \n");
    for(int i = 0; i < SIZE;i++) {
        for(int j = 0; j < SIZE;j++) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }

    int* min_dist = new int[SIZE];
    int* check_versh = new int[SIZE];
    for (int i = 0; i<SIZE; i++) {
        min_dist[i] = 10000;
        check_versh[i] = 1;
    }

    int min_index, min, begin_index, temp;
    std::cin >> begin_index;   
    begin_index = begin_index - 1;
    min_dist[begin_index] = 0;

    do {
        min_index = 10000;
        min = 10000;
        for (int i = 0; i<SIZE; i++) {
            if ((check_versh[i] == 1) && (min_dist[i]<min)) { 
                min = min_dist[i];
                min_index = i;
            }
        }

        if (min_index != 10000) {
            for (int i = 0; i<SIZE; i++) {
                if (a[min_index][i] > 0) {
                    temp = min + a[min_index][i];
                    if (temp < min_dist[i]) {
                        min_dist[i] = temp;
                    }
                }
            }
            check_versh[min_index] = 0;
        }

    } while (min_index < 10000);

    printf("\nКратчайшие расстояния до вершин: \n");
    for (int i = 0; i<SIZE; i++) {
        printf("%4d ", min_dist[i]);
    }

    
    int ver[SIZE];
    int end = 4;
    ver[0] = end + 1;
    int k = 1;
    int weight = min_dist[end];

    while (end != begin_indssex) {
        for (int i = 0; i<SIZE; i++) {
            if (a[i][end] != 0) {
                int temp = weight - a[i][end];
                if (temp == min_dist[i]) {                 
                    weight = temp; 
                    end = i;     
                    ver[k] = i + 1; 
                    k++;
                }
            }
        }
    }

    printf("\nВывод кратчайшего пути\n");
    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);

    return 0;
}