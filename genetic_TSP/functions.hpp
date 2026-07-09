#pragma once

#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <iostream>

#include "random.hpp"
#include "TSPProblem.hpp"

using namespace std;

const double MUTATION_RATE = 0.3;
const double SK = 0.5;

// Прогресс бар для котроля процесса
class ProgressBar {
public:
    explicit ProgressBar(int total_steps) : total(total_steps), step(0), best_result(-1) {}

    void update(double best_res = 0, int steps = 1) {
        step += steps;
        best_result = best_res;
        std::cout << "\r[" << std::string(step * 50 / total, '#') << std::string(50 - step * 50 / total, '-') << "] "
                  << step << "/" << total << " completed. Best res = " << best_res;
        std::flush(std::cout);
    }

private:
    int total;
    int step;
    double best_result;
};

struct Individual {
    vector<int> path;
    double distance;

    bool operator<(const Individual& other) const {
        return distance < other.distance;
    }
};

vector<vector<double>> random_distances(int n) {
    // Создаем генератор случайных чисел
    random_device rd;
    mt19937 gen(1); // детерминированно
    // mt19937 gen(rd()) //  недетерминированно
    uniform_int_distribution<> dis(0, 100);
    
    // Заполняем массив городов случайными координатами
    vector<City> cities(n); // создаём вектор нужного размера
    for (auto& city : cities) {
        city.x = dis(gen); // генерируем случайные координаты X
        city.y = dis(gen); // генерируем случайные координаты Y
    }
    
    // Создаем двумерный вектор для хранения расстояний
    vector<vector<double>> distances(n, vector<double>(n)); // задаём размеры
    
    // Вычисление евклидова расстояния между всеми парами городов
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i != j) {
                double dx = cities[i].x - cities[j].x;
                double dy = cities[i].y - cities[j].y;
                distances[i][j] = distances[j][i] = sqrt(dx*dx + dy*dy); // сохраняем расстояние
            } else {
                distances[i][j] = 0.0; // диагональ заполнять нулями
            }
        }
    }

    return distances;
}

template<typename T>
void print_matrix(const vector<vector<T>>& matrix) {
    if (matrix.empty()) {
        cout << "Matrix is empty." << endl;
        return;
    }

    // Получаем размер матрицы
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    // Устанавливаем ширину поля для лучшей визуализации
    size_t field_width = 8; // Ширина поля для каждого элемента

    // Проходим по каждому ряду и столбцу
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cout << setw(field_width) << right << matrix[i][j]; // Установка ширины поля и выравнивания вправо
        }
        cout << endl; // Переход на новую строку после завершения ряда
    }
}

// Генеративная функция 1: частично жадный алгоритм, остальная часть случайная
vector<int> gen1(int start, int num_cities, const vector<vector<double>>& distances) {
    vector<int> path(num_cities);
    path[0] = start;
    
    // Массив свободных городов (кроме стартового)
    vector<bool> visited(num_cities, false);
    visited[start] = true;

    // Начало жадного выбора городов
    int current_city = start;
    int greedy_count = max(static_cast<int>(num_cities / 3), 1); // Приблизительно треть городов выбираем жадно
    
    for (int i = 1; i <= greedy_count; ++i) {
        // Найти ближайшую незасечённую вершину
        int next_city = -1;
        double min_dist = numeric_limits<double>::max();

        for (int j = 0; j < num_cities; ++j) {
            if (!visited[j] && distances[current_city][j] < min_dist) {
                next_city = j;
                min_dist = distances[current_city][next_city];
            }
        }

        path[i] = next_city; // Добавляем новый город в маршрут
        visited[next_city] = true; // Ставим метку о посещённом городе
        current_city = next_city; // Текущим становится новый город
    }

    // Остальные города добавляем случайным образом
    vector<int> remaining_cities;
    for (int i = 0; i < num_cities; ++i) {
        if (!visited[i]) {
            remaining_cities.push_back(i);
        }
    }
    
    shuffle(remaining_cities.begin(), remaining_cities.end(), Random::rng());

    // Дополняем маршрут оставшимися городами
    for (int i = greedy_count + 1; i < num_cities; ++i) {
        path[i] = remaining_cities[i - greedy_count - 1];
    }

    return path;
}

// Генеративная функция 2: полностью случайная генерация маршрута
vector<int> gen2(int start, int num_cities) {
    vector<int> path(num_cities);
    path[0] = start;
    
    // Все промежуточные города распределяем случайным образом
    vector<int> remaining_cities;
    for (int i = 0; i < num_cities; i++) {
        if (i != start) {
            remaining_cities.push_back(i); // Городам присваиваются номера от 1 до N-1
        }
    }
    
    shuffle(remaining_cities.begin(), remaining_cities.end(), Random::rng());

    copy(remaining_cities.begin(), remaining_cities.end(), path.begin() + 1);

    return path;
}


// Вычисление расстояния (с учетом возврата в изначальный город)
double count_distance(const vector<int>& path, const vector<vector<double>>& distances) {
    double res = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        res += distances[path[i]][path[i+1]];
    }
    res += distances[path[path.size()-1]][path[0]];
    return res;
}

// Генератор изначальной популяции
vector<Individual> generate_initial_population(int start, int num_cities, int pop_size, const vector<vector<double>>& distances) {
    vector<Individual> population(pop_size);
    
    for (int i = 0; i < pop_size; i++) {
        Individual ind;
        if (Random::randprob() < 0.5) {
            ind.path = gen1(start, num_cities, distances);        
        } else {
            ind.path = gen2(start, num_cities);
        }
        ind.distance = count_distance(ind.path, distances);
        population[i] = move(ind);
    }

    return population;
}

// Сортировка популяции по длине представителей
void sort_population_by_distance(vector<Individual>& population) {
    sort(population.begin(), population.end());
}

// Функция скрещивания: часть первого родителя, часть второго
vector<int> crossing(const vector<int>& parent1, const vector<int>& parent2, double sk = SK) {
    int size = parent1.size();
    vector<int> child(size);

    int sector_begin = static_cast<int>(sk * size);

    copy(parent1.begin() + sector_begin, parent1.end(), child.begin() + sector_begin);

    // Формируем маску посещённых городов
    vector<bool> used(size, false);
    for (int i = sector_begin; i < size; i++) {
        used[parent1[i]] = true;
    }

    // Заполняем оставшуюся часть ребенка свободными городами из второго родителя
    int pos = 0;
    for (int gene : parent2) {
        if (!used[gene]) {
            child[pos++] = gene;
            used[gene] = true;
        }
    }

    return child;
}

// Функция мутации: поменять местами два случайных города в маршруте
vector<int> mutation_swap(const vector<int>& original_path, double mutation_rate = MUTATION_RATE) {
    // Создаем копию оригинального маршрута
    vector<int> mutated_path(original_path);

    // Проверяем вероятность мутации
    if (Random::randprob() < mutation_rate) {
        // Определяем диапазон для выбора случайных позиций
        int path_length = mutated_path.size();

        // Генерируем два случайных индекса
        int idx1 = Random::randint(1, path_length - 1);
        int idx2 = Random::randint(1, path_length - 1);

        // Меняем местами два города
        swap(mutated_path[idx1], mutated_path[idx2]);
    }

    return mutated_path;
}


// Основная функция прогона всех популяций
void run_generations(int max_generations, 
                    vector<Individual> population, 
                    vector<vector<double>> distances) {
    int pop_size = population.size();
    sort_population_by_distance(population);

    ProgressBar pb(max_generations);

    double best_dist = population[0].distance;   

    for (int gen = 0; gen < max_generations; gen++) {
        int wr_group_size = Random::randint(static_cast<int>(pop_size * 0.04), static_cast<int>(pop_size * 0.15));
        vector<Individual> wr_group(wr_group_size);

        // Создаем рандомную подвыборку из популяции
        vector<int> idx_r(pop_size);
        for (int i = 0; i < pop_size; i++) idx_r[i] = i;
        shuffle(idx_r.begin(), idx_r.end(), Random::rng());
        vector<int> idx(wr_group_size);
        copy(idx_r.begin(), idx_r.begin() + wr_group_size, idx.begin());

        // Находим индекс худшего представителя
        int bad_idx;
        double bad_distance = 0;

        for (int i = 0; i < wr_group_size; i++) {
            wr_group[i] = population[idx[i]];
            if (wr_group[i].distance > bad_distance) {
                bad_idx = idx[i];
                bad_distance = wr_group[i].distance;
            }
        }

        // Получаем ребенка
        sort_population_by_distance(wr_group);
        vector<int> child = crossing(wr_group[0].path, wr_group[1].path);
        child = mutation_swap(child);

        // Заменяем худшего представителя wr_group в популяции на child
        population[bad_idx].path = child;
        population[bad_idx].distance = count_distance(child, distances);

        // Обновляем прогресс бар
        if (population[bad_idx].distance < best_dist) best_dist = population[bad_idx].distance;
        pb.update(best_dist);
    }
    sort_population_by_distance(population);
}
