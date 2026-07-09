#pragma once 

#include <vector>
#include "random.hpp"
#include <iostream>
#include <iomanip>

using namespace std;


struct City {
    int x;
    int y;
};

class TSPProblem {

public:
    int num_cities;

    vector<City> cities;
    vector<vector<double>> distances;

    TSPProblem(int n) : num_cities(n) {}

    static TSPProblem random(int n)
    {
        TSPProblem problem(n);

        problem.cities.resize(n);

        for (auto &c : problem.cities) {
            c.x = Random::randint(0,100);
            c.y = Random::randint(0,100);
        }

        problem.distances.resize(n, vector<double>(n));

        for (int i=0;i<n;i++) {
            for (int j=0;j<=i;j++)
            {
                if (i==j) {
                    problem.distances[i][j]=0;
                    continue;
                }

                double dx = problem.cities[i].x - problem.cities[j].x;
                double dy = problem.cities[i].y - problem.cities[j].y;

                double d = sqrt(dx*dx + dy*dy);

                problem.distances[i][j]=problem.distances[j][i]=d;
            }
        }

        return problem;
    }

    double count_distance(const vector<int>& path) const
    {
        double d = 0;

        for(int i=0;i<path.size()-1;i++)
            d += distances[path[i]][path[i+1]];

        d += distances[path.back()][path[0]];

        return d;
    }

    void print_matrix() {
        if (distances.empty()) {
            cout << "Matrix is empty." << endl;
            return;
        }

        // Получаем размер матрицы
        size_t rows = distances.size();
        size_t cols = distances[0].size();

        // Устанавливаем ширину поля для лучшей визуализации
        size_t field_width = 8; // Ширина поля для каждого элемента

        // Проходим по каждому ряду и столбцу
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << setw(field_width) << right << distances[i][j]; // Установка ширины поля и выравнивания вправо
            }
            cout << endl; // Переход на новую строку после завершения ряда
        }
    }
    
};

vector<int> nearest_neighbor(const TSPProblem& problem, int start) {
    int n = problem.num_cities;

    vector<int> path(n);
    vector<bool> visited(n, false);

    path[0] = start;
    visited[start] = true;

    int current = start;

    for (int i = 1; i < n; i++) {

        int best_city = -1;
        double best_dist = numeric_limits<double>::max();

        for (int j = 0; j < n; j++) {
            if (!visited[j] && problem.distances[current][j] < best_dist) {
                best_dist = problem.distances[current][j];
                best_city = j;
            }
        }

        path[i] = best_city;
        visited[best_city] = true;
        current = best_city;
    }

    return path;
}