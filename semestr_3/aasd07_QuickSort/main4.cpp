#include <iostream>
#include "function.h"
#include <vector>

using namespace std;

int main() {
    vector<int> arr1 = {2,4,7,8,9,15};
    vector<int> arr2 = {1,3,4,6,7,10,13,15,17};
    int* result = optimal_merge(arr1.data(), arr1.size(), arr2.data(), arr2.size());
    for (int i = 0; i < arr1.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    print_array(result, arr1.data(), arr1.size(), arr2.data(), arr2.size());
    return 0;
}