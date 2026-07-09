#include "functions.h"

double pow(int x, int n) {
    if (n == 0) {
        return 1;
    }
    else if (n < 0) {
        return 1 / (x * pow(x, -n - 1));
    } 
    else {
        return x * pow(x, n - 1);
    }
}

double C(int n, int m) {
    if (m > n || m < 1) {
        return 0;
    } 
    if (m == n) {
        return 1;
    }
    return C(n - 1, m - 1) + C(n - 1, m);
}

bool isSquare(int n, int k) {
    if (n == k) {
        return true;
    } if (n < k) {
        return false;
    }
    return isSquare(n - k, k);
}

double sum(int n) {
    if (n == 0) {
        return 0;
    }
    return n + sum(n - 1);
}