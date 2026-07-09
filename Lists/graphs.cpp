#include <iostream>
#include <fstream>
#include <iomanip>

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
        cout << i << " ";
    }
    cout << "\n";
    for (int i = 1; i < max_versh; i++) {
        cout << i << " ";
        for (int j = 1; j < max_versh; j++) {
        cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < max_versh; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    node* graphs = read_graph(fin);
    print_nodes(graphs, fout);
    cout << rebro(graphs, 2, 3) << "\n";
    matrix(graphs);
    fin.close();
    fout.close();
    return 0;
  }