#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

//---------------Part1--------------

template <class T>
void insertion_sort(T* mas, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        T key = mas[i];
        int j = i - 1;

        while (j >= left && mas[j] > key) {
            mas[j + 1] = mas[j];
            j--;
        }
        mas[j + 1] = key;
    }
}


template <class T>
void merge_blocks(T* mas, T* buf, int left, int mid, int right) {
    int rightSize = right - mid + 1;
    int leftSize = mid - left;

    // копируем правую половину целиком
    for (int i = 0; i < rightSize; i++)
        buf[i] = mas[i + mid];

    // перемещаем левую половину вправо
    for (int i = mid - 1; i >= left; i--) { 
        mas[i + rightSize] = mas[i];
    }
    
    mid = left + rightSize;
    leftSize = rightSize;

    int i = 0;          // индекс в buf
    int j = mid;        // индекс правой части
    int k = left;       // позиция для записи в mas

    while (i < leftSize && j <= right) {
        if (buf[i] <= mas[j]) mas[k++] = buf[i++];
        else                  mas[k++] = mas[j++];
    }

    while (i < leftSize)
        mas[k++] = buf[i++];
}


template <class T>
void merge_sort(T* mas, int size) {
    const int INSERTION_THRESHOLD = 20;

    if (size <= INSERTION_THRESHOLD) {
        insertion_sort(mas, 0, size - 1);
        return;
    }

    T* buf = new T[size / 2];

    for (int i = 0; i < size; i += INSERTION_THRESHOLD) {
        int right = std::min(i + INSERTION_THRESHOLD - 1, size - 1);
        insertion_sort(mas, i, right);
    }

    for (int block = INSERTION_THRESHOLD; block < size; block *= 2) {
        for (int left = 0; left < size; left += 2 * block) {

            int mid = std::min(left + block, size);
            int right = std::min(left + 2 * block - 1, size - 1);

            if (mid <= right) {
                merge_blocks(mas, buf, left, mid, right);
            }
        }
    }

    delete[] buf;
}

//---------------Part2--------------

struct elem {
    int info;
    elem* next;
};

elem* move(elem* top, int n) {
    while (n-- > 0 && top != nullptr)
        top = top->next;
    return top;
}

elem* merge(elem* top1, elem* top2) {
    if (!top1) return top2;
    if (!top2) return top1;

    elem* head;

    if (top1->info < top2->info) {
        head = top1;
        top1 = top1->next;
    } else {
        head = top2;
        top2 = top2->next;
    }

    elem* tail = head;

    while (top1 && top2) {
        if (top1->info < top2->info) {
            tail->next = top1;
            top1 = top1->next;
        } else {
            tail->next = top2;
            top2 = top2->next;
        }
        tail = tail->next;
    }

    tail->next = top1 ? top1 : top2;

    return head;
}

void merge_sort_list(elem*& top) {
    if (!top || !top->next) return;

    int n = 0;
    for (elem* p = top; p; p = p->next) n++;

    for (int block = 1; block < n; block *= 2) {

        elem* new_head = nullptr;
        elem* new_tail = nullptr;

        elem* left = top;

        while (left != nullptr) {

            elem* mid = move(left, block-1);

            if (!mid) {
                if (!new_head) new_head = left;
                else new_tail->next = left;

                new_tail = left;
                while (new_tail->next) new_tail = new_tail->next;
                break;
            }
            
            elem* right = mid->next;
            mid->next = nullptr;
            elem* next_left = nullptr;
            mid = right;
            right = move(mid, block-1);
            if (right) {
                next_left = right->next;
                right->next = nullptr;
            }
            
            elem* merged = merge(left, mid);

            if (!new_head) {
                new_head = merged;
                new_tail = merged;
            } else {
                new_tail->next = merged;
            }

            while (new_tail->next) new_tail = new_tail->next;

            left = next_left;
        }

        top = new_head;
    }
}


// ---------------------- UTILS -------------------------

elem* make_list(std::initializer_list<int> vals) {
    elem* head = nullptr;
    elem* tail = nullptr;

    for (int v : vals) {
        elem* p = new elem{v, nullptr};
        if (!head) head = p;
        else tail->next = p;
        tail = p;
    }
    return head;
}

vector<int> to_vector(elem* top) {
    vector<int> out;
    while (top) {
        out.push_back(top->info);
        top = top->next;
    }
    return out;
}

bool check(elem* top, initializer_list<int> expected) {
    vector<int> got = to_vector(top);
    vector<int> exp(expected);
    return got == exp;
}

void free_list(elem* top) {
    while (top) {
        elem* nxt = top->next;
        delete top;
        top = nxt;
    }
}

void test_case(const char* name, initializer_list<int> input, initializer_list<int> expected) {
    elem* top = make_list(input);    
    merge_sort_list(top);
    
    bool ok = check(top, expected);
    cout << (ok ? "[ OK ] " : "[ FAIL ] ") << name << endl;
    free_list(top);
}

//---------------Part3--------------

template <typename T>
void quick_sort(T* mas, int size) {
    int left = 0;
    int right = size - 1;

    while (left < right) {

        T pivot = mas[(left + right) / 2];
        int i = left;
        int j = right;

        while (i <= j) {
            while (mas[i] < pivot) i++;
            while (mas[j] > pivot) j--;
            if (i <= j) {
                std::swap(mas[i], mas[j]);
                i++;
                j--;
            }
        }

        if (j - left < right - i) {
            if (left < j)
                quick_sort(mas + left, j - left + 1);

            left = i;
        } else {
            if (i < right)
                quick_sort(mas + i, right - i + 1);

            right = j;
        }
    }
}

//---------------Part4--------------
template <class T>
int* optimal_merge(T* mas1, int size1, T* mas2, int size2) {
    if (size1 > size2) return nullptr;

    int* result = new int[size1];

    int finger = 0;
    int window = size2 / size1;

    for (int i = 0; i < size1; i++) {
        T x = mas1[i];

        int left = finger;
        int right = min(finger + window, size2-1);

        while (right < size2 - 1 && mas2[right] < x) {
            left = right;
            right = min(right + window, size2 - 1);
        }

        int pos = -1;
        int l = left, r = right;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (mas2[mid] < x) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        result[i] = l;
        finger = l;
    }

    return result;
}

template <class T>
void print_array(T* mas, T* mas1, int size1, T* mas2, int size2) {
    int p1{}, p2{};
    for (int i = 0; i < size1; i++) {
        while (p2 < mas[i]) cout << mas2[p2++] << " ";
        cout << mas1[p1++] << " ";
    }
    while (p2 < size2) cout << mas2[p2++] << " ";
}

//---------------Part5--------------
struct Person {
    string name;
    string patronymic;
    string surname;
    int day, month, year;
    string code;
};

template <class T, class KeyGetter>
void counting_sort(vector<T>& a, int maxKey, KeyGetter get_key) {
    int n = a.size();
    vector<int> count(maxKey + 1, 0);
    vector<T> output(n);

    for (int i = 0; i < n; i++)
        count[get_key(a[i])]++;

    for (int i = 1; i <= maxKey; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int k = get_key(a[i]);
        output[--count[k]] = a[i];
    }

    a = output;
}
