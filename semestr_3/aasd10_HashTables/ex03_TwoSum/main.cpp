#include <iostream>
#include <random>

#include "functions.h"

using namespace std;

void source(int* nums, int size, int target) {
    Hash map(size);
    
    for (int i = 0; i < size; i++) {
        int add_target = target - nums[i];
        int j = map.get(add_target);

        if (map.contain(add_target) && (nums[i] + nums[j]) == target) {
            if (j != i) {
                cout << map.get(add_target) << " " << i << endl;
                return;
            } 
        }

        map.add_val(nums[i], i);
    }

    cout << "Error" << endl;
}

int main() {
    int size, target;

    cin >> size;

    int* nums = new int[size];
    for (int i = 0; i < size; i++) cin >> nums[i];

    cin >> target;

    source(nums, size, target);
    delete[] nums;

    size = 100000;
    nums = new int[size];
    for (int i = 0; i < size; i++) nums[i] = rand() % 100;

    source(nums, size, 23);

    return 0;
}