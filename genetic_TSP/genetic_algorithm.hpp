#pragma once

#include "TSPProblem.hpp"
#include "random.hpp"
#include "progress_bar.hpp"

#include <algorithm>

struct Individual {
    vector<int> path;
    double distance;

    bool operator<(const Individual& other) const {
        return distance < other.distance;
    }
};

class GeneticAlgorithm {
private:

    const TSPProblem& problem;

    int population_size;
    double mutation_rate;
    int wr_group_size;
    double crossover_point;
    int start;

    vector<Individual> population;

    vector<int> nn_cut_path(int, int, vector<bool>&);
    vector<int> gen1();
    vector<int> gen2();

    Individual crossover_base(const Individual&, const Individual&);
    Individual crossover(const Individual&, const Individual&);
    void mutate(Individual&, float);

public:

    GeneticAlgorithm(const TSPProblem& problem, int pop_size);

    void initialize_population();

    void run(int generations);

    const Individual& best() const;

    void print_info() const;
};

GeneticAlgorithm::GeneticAlgorithm(const TSPProblem& problem, int pop_size):
    problem(problem), 
    population_size(pop_size), 
    mutation_rate(0.5),
    wr_group_size(17),
    crossover_point(0.5),
    start(0)
    {
        initialize_population();
    }

vector<int> GeneticAlgorithm::nn_cut_path(int start, int len, vector<bool>& visited) {
    // Собираем кусок жадным алгоритмом от рандомного города
    vector<int> cut_path(len);

    cut_path[0] = start;
    visited[start] = true;
    int current_city = start;

    for (int i = 1; i < len; ++i) {
        // Найти ближайшую незасечённую вершину
        int next_city = -1;
        double min_dist = numeric_limits<double>::max();

        for (int j = 0; j < problem.num_cities; ++j) {
            if (!visited[j] && problem.distances[current_city][j] < min_dist) {
                min_dist = problem.distances[current_city][j];
                next_city = j;
            }
        }

        cut_path[i] = next_city; // Добавляем новый город в маршрут
        visited[next_city] = true; // Ставим метку о посещённом городе
        current_city = next_city; // Текущим становится новый город
    }
    return cut_path; 
}

vector<int> GeneticAlgorithm::gen1() {
    vector<int> path(problem.num_cities);
    path[0] = start;
    
    // Массив свободных городов (кроме стартового)
    vector<bool> visited(problem.num_cities, false);
    visited[start] = true;

    // Начало жадного выбора городов
    int greedy_count = max(static_cast<int>(problem.num_cities * 0.5), 1); // Приблизительно треть городов выбираем жадно
    
    // Собираем кусок жадным алгоритмом от рандомного города
    int cut_start = Random::randint(0, problem.num_cities-1);
    while(cut_start == start) cut_start = Random::randint(0, problem.num_cities-1);
    
    vector<int> cut_path = nn_cut_path(cut_start, greedy_count, visited);

    // Остальные города добавляем случайным образом
    vector<int> remaining_cities;
    for (int i = 0; i < problem.num_cities; ++i) {
        if (!visited[i]) {
            remaining_cities.push_back(i);
        }
    }

    shuffle(remaining_cities.begin(), remaining_cities.end(), Random::rng());

    // Дополняем маршрут оставшимися городами
    
    int a = Random::randint(1, problem.num_cities - greedy_count - 1);
    copy(cut_path.begin(), cut_path.end(), path.begin() + a);
    

    for (int i = 1; i < problem.num_cities; i++) {
        if (i < a)
            path[i] = remaining_cities[i - 1];
        if (i >= a + greedy_count)
            path[i] = remaining_cities[i - greedy_count - 1];
        }

    return path;
}

vector<int> GeneticAlgorithm::gen2() {
    vector<int> path(problem.num_cities);
    path[0] = start;
    
    // Все промежуточные города распределяем случайным образом
    vector<int> remaining_cities;
    for (int i = 0; i < problem.num_cities; i++) {
        if (i != start) {
            remaining_cities.push_back(i); // Городам присваиваются номера от 1 до N-1
        }
    }
    
    shuffle(remaining_cities.begin(), remaining_cities.end(), Random::rng());
    copy(remaining_cities.begin(), remaining_cities.end(), path.begin() + 1);

    return path;
}

void GeneticAlgorithm::initialize_population() {
    population.resize(population_size);

    for (int i = 0; i < population_size; i++) {
        Individual ind;
        if (Random::randprob() < 0.3) {
            ind.path = gen1();        
        } else {
            ind.path = gen2();
        }
        ind.distance = problem.count_distance(ind.path);
        population[i] = move(ind);
    }
}

Individual GeneticAlgorithm::crossover_base(const Individual& p1, const Individual& p2) {
    int size = p1.path.size();
    vector<int> child(size);

    int sector_begin = static_cast<int>(crossover_point * size);

    copy(p1.path.begin() + sector_begin, p1.path.end(), child.begin() + sector_begin);

    // Формируем маску посещённых городов
    vector<bool> used(size, false);
    for (int i = sector_begin; i < size; i++) {
        used[p1.path[i]] = true;
    }

    // Заполняем оставшуюся часть ребенка свободными городами из второго родителя
    int pos = 0;
    for (int gene : p2.path) {
        if (!used[gene]) {
            child[pos++] = gene;
            used[gene] = true;
        }
    }

    return Individual{child, problem.count_distance(child)};
}

Individual GeneticAlgorithm::crossover(const Individual& p1, const Individual& p2) { 
    int size = p1.path.size();
    vector<int> child(size);

    int c1 = Random::randint(0, size - 2);
    int c2 = Random::randint(c1 + 1, size - 1);

    for (int i = c1; i <= c2; i++) {
        child[i] = p1.path[i];
    }

    vector<bool> used(size, false);
    for (int i = c1; i <= c2; i++) {
        used[p1.path[i]] = true;
    }

    int pos = 0;
    for (int gene : p2.path) {
        if (!used[gene]) {

            // пропускаем занятый сегмент
            while (pos >= c1 && pos <= c2)
                pos++;

            child[pos] = gene;
            used[gene] = true;
            pos++;
        }
    }

    return Individual{child, problem.count_distance(child)};
}

void GeneticAlgorithm::mutate(Individual& p, float mutate_rate=0.05) {
    // Проверяем вероятность мутации
    if (Random::randprob() < mutation_rate) {
        // Определяем диапазон для выбора случайных позиций
        int path_length = p.path.size();

        if (Random::randprob() <= mutate_rate) {
            int idx1 = Random::randint(1, path_length - 1);
            int idx2 = Random::randint(1, path_length - 1);
            while (idx1 == idx2) idx2 = Random::randint(1, path_length - 1);
            
            swap(p.path[idx1], p.path[idx2]);
        } else {
            int a = Random::randint(1, path_length - 2);
            int b = Random::randint(a + 1, path_length - 1);
            reverse(p.path.begin() + a, p.path.begin() + b + 1);
        }
          
        p.distance = problem.count_distance(p.path);
    }
}

void GeneticAlgorithm::print_info() const {
    cout << endl << endl;
    cout << string(30, '-') << endl;
    cout << "Num cities: " << problem.num_cities << endl;
    cout << "Pop size: " << population_size << endl;
    cout << "Wr_grop_size: " << wr_group_size << endl;
    cout << string(30, '-') << endl;
    cout << endl;
}

void GeneticAlgorithm::run(int generations) {
    print_info();

    ProgressBar pd(generations);
    sort(population.begin(), population.end());
    double best_dist = population[0].distance;

    cout << "Best distance: " << best_dist << endl;

    vector<int> nn_path = nearest_neighbor(problem, start);
    cout << "NN distance: " << problem.count_distance(nn_path) << endl << endl;

    for (int gen = 0; gen < generations; gen++) {
        // Имитируем случайную подвыборку
        shuffle(population.begin(), population.end(), Random::rng());
        sort(population.begin(), population.begin() + wr_group_size);

        // Берем двух лучших представителей
        const Individual& parent1 = population[0];
        const Individual& parent2 = population[1];

        // Скрещиваем и заменяем худшего из подвыборки
        Individual child1 = crossover(parent1, parent2);
        mutate(child1);
        Individual child2 = crossover(parent2, parent1);
        mutate(child2);

        population[wr_group_size - 1] = move(child1);
        population[wr_group_size - 2] = move(child2);

        // Обновляем прогресс-бар
        pd.update(best().distance);

    }
    cout << endl;
}

const Individual& GeneticAlgorithm::best() const {
    return *min_element(population.begin(), population.end());
}