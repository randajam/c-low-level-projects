#pragma once
#include <random>

class Random {
public:
    static std::mt19937& rng(int random_state = 1) {
        static std::mt19937 gen(random_state);
        return gen;
    }

    static int randint(int a, int b, bool random_state = 1) {
        std::uniform_int_distribution<int> d(a,b);
        std::random_device rd;
        return d(rng());
    }

    static double randprob() {
        std::uniform_real_distribution<double> d(0.0,1.0);
        return d(rng());
    }
};