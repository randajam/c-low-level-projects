#pragma once

#include <iostream>

using namespace std;

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
