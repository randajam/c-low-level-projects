#pragma once
#include <stdexcept>

template <typename T>
class Priority_Queue {
private:
    int capacity;
    int size;
    T* mas;

    void heapify_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (mas[i] < mas[p]) {
                std::swap(mas[i], mas[p]);
                i = p;
            } else break;
        }
    }

    void heapify_down(int i) {
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int smallest = i;

            if (l < size && mas[l] < mas[smallest]) smallest = l;
            if (r < size && mas[r] < mas[smallest]) smallest = r;

            if (smallest != i) {
                std::swap(mas[i], mas[smallest]);
                i = smallest;
            } else break;
        }
    }

public:

    Priority_Queue() : capacity(16), size(0) {
        mas = new T[capacity];
    }

    Priority_Queue(const Priority_Queue& other)
        : capacity(other.capacity), size(other.size)
    {
        mas = new T[capacity];
        for (int i = 0; i < size; i++)
            mas[i] = other.mas[i];
    }

    Priority_Queue(T* arr, int n) : capacity(n), size(n) {
        mas = new T[capacity];
        for (int i = 0; i < n; i++) mas[i] = arr[i];

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify_down(i);
    }

    ~Priority_Queue() {
        delete[] mas;
    }

    void insert(T val) {
        if (size == capacity) {
            capacity *= 2;
            T* tmp = new T[capacity];
            for (int i = 0; i < size; i++) tmp[i] = mas[i];
            delete[] mas;
            mas = tmp;
        }

        mas[size] = val;
        heapify_up(size);
        size++;
    }

    T get_min() {
        if (size == 0) throw std::runtime_error("Queue is empty");
        return mas[0];
    }

    T extract_min() {
        if (size == 0) throw std::runtime_error("Queue is empty");

        T min_val = mas[0];
        mas[0] = mas[size - 1];
        size--;

        heapify_down(0);
        return min_val;
    }

    int get_size() {
        return size;
    }
};



void heapify(int* mas, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && mas[left] < mas[smallest])
        smallest = left;

    if (right < n && mas[right] < mas[smallest])
        smallest = right;

    if (smallest != i) {
        std::swap(mas[i], mas[smallest]);
        heapify(mas, n, smallest);
    }
}

void heap_sort(int* mas, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(mas, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(mas[0], mas[i]);
        heapify(mas, i, 0);
    }

    for (int i = 0; i < n / 2; i++)
        std::swap(mas[i], mas[n - 1 - i]);
}

template <typename T>
T kth_min(T* A, int n, int k) {
    if (k < 1 || k > n)
        throw std::runtime_error("k is out of range");

    Priority_Queue<T> pq(A, n);

    for (int i = 1; i < k; i++) {
        pq.extract_min();
    }

    return pq.get_min();
}
