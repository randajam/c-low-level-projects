#include <vector>

#include "file_working.hpp"
#include "genetic_algorithm.hpp"

using namespace std;

// Количество городов
const int NUM_CITIES = 1000;
const int POP_SIZE = 100;
const int MAX_GENERATION = 100000;

int main() {
    TSPProblem problem = TSPProblem::random(NUM_CITIES);

    GeneticAlgorithm ga(problem, POP_SIZE);
    ga.run(MAX_GENERATION);
    
    return 0;
}


