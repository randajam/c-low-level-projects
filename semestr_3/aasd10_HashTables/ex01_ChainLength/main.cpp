#include "functions.h"
#include <random>
#include <iostream>
#include <chrono>

using namespace std;

void source(long long N) {
    Hash mas(N);
    for (int i = 0; i < N; i++) {
        mas.add(100 * rand());
    }

    long long mean = 0;
    int min = 1e9, max = 0;
    for (int i = 0; i < N / 100; i++) {
        int len = mas.chain_length(i);
        mean += len;
        if (len > max) max = len;
        if (len < min) min = len;
    }
            
    mean /= N / 100;
    cout << "Mean len: " << mean << endl;
    cout << "Min len: " << min << endl;
    cout << "Max len: " << max << endl;
}

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    source(1e3);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time for 1e3: " << duration.count() << " ms\n\n";

    
    start = high_resolution_clock::now();
    source(1e4);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Time for 1e4: " << duration.count() << " ms\n\n";

    start = high_resolution_clock::now();
    source(1e5);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Time for 1e5: " << duration.count() << " ms\n\n";

    start = high_resolution_clock::now();
    source(1e6);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Time for 1e6: " << duration.count() << " ms\n\n";

    return 0;
}