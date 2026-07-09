#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct graph {
  int x1, y1;
  int x2, y2;
  float weight;
};

struct node {
  struct graph graph;
  struct node* next;
};

node* init_elem(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) {
  node* tmp = new node;
  tmp->graph.x1 = x1;
  tmp->graph.y1 = y1;
  tmp->graph.x2 = x2;
  tmp->graph.y2 = y2;

  int dx = x2 - x1;
  int dy = y2 - y1;
  tmp->graph.weight = sqrt((dx * dx) + (dy * dy));

  tmp->next = nullptr;
  return tmp;
}

void print_nodes(node* graphs, ofstream& fout) {
  node* tmp = graphs;
  while (tmp != nullptr) {
    fout << "(" << tmp->graph.x1 << "," << tmp->graph.y1 << ") (" << tmp->graph.x2 << "," << tmp->graph.y2 << ") weight:" << tmp->graph.weight << "\n";
    tmp = tmp->next;
  }
}

void add_last(node*& graphs, int x1, int y1, int x2, int y2) {
  if (graphs == nullptr) {
    graphs = init_elem(x1, y1, x2, y2);
    return;
  }

  node* tmp = graphs;
  while (tmp->next != nullptr) {
    tmp = tmp->next;
  }

  tmp->next = init_elem(x1, y1, x2, y2);
}

node* read_graph(ifstream& fin) {
  int x1, y1, x2, y2;
  node* graph = nullptr;
  while (fin >> x1 >> y1 >> x2 >> y2) {
    add_last(graph,x1,y1,x2,y2);
  }
  return graph;
}

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");
  node* graphs = read_graph(fin);
  print_nodes(graphs, fout);
  fin.close();
  fout.close();
  return 0;
}