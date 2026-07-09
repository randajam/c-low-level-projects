#include "functions.h"
#include <iostream>

using namespace std;

void FindDel(int n, int m) {
    if (m * m > n) return;
    if (n % m == 0) {
        cout << m << " ";
        if (m != n / m) {
            cout << n / m << " ";
        }
    }
    FindDel(n, m + 1);
}

int BinSearch(int arr[10], int x, int low, int hight) {
    int middle = (low + hight) / 2;
    if (arr[middle] == x) {
        return middle;
    }
    else if (arr[middle] > x) {
        return BinSearch(arr, x, low, middle + 1);
    }
    else {
        return BinSearch(arr, x, middle - 1, hight);
    }
}

void BubbleSort(int arr[10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}