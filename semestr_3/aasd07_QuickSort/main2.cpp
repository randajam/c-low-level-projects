#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

#include "function.h"

int main() {

    test_case("Empty list", {}, {});
    test_case("Single element", {5}, {5});
    test_case("All equal", {7,7,7,7}, {7,7,7,7});
    test_case("Already sorted", {1,2,3,4,5}, {1,2,3,4,5});
    test_case("Reverse order", {5,4,3,2,1}, {1,2,3,4,5});
    test_case("Mixed numbers", {3,1,4,2,9,7,6}, {1,2,3,4,6,7,9});
    test_case("With duplicates", {4,1,3,4,2,4}, {1,2,3,4,4,4});

    return 0;
}
