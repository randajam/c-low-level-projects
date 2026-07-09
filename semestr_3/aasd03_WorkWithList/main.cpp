#include <iostream>

struct node {
    int data;
    node* next;
};

// Создание списка из массива для удобства
node* create_list(const int arr[], int n) {
    if (n == 0) return nullptr;
    node* head = new node{arr[0], nullptr};
    node* tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = new node{arr[i], nullptr};
        tail = tail->next;
    }
    return head;
}

// Очистка списка
void del_list(node* head) {
    while (head) {
        node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// 1. Сумма всех элементов
int sum(node* head) {
    int total = 0;
    while (head) {
        total += head->data;
        head = head->next;
    }
    return total;
}

// 2. Количество элементов
int count(node* head) {
    int cnt = 0;
    while (head) {
        cnt += 1;
        head = head->next;
    }
    return cnt;
}

// 3. Максимальный элемент
int max_element(node* head) {
    int max_val = head->data;
    head = head->next;
    while (head) {
        if (head->data > max_val)
            max_val = head->data;
        head = head->next;
    }
    return max_val;
}

// 4. Правоассоциативная свёртка (foldr)
int foldr(node* head, int(*op)(int, int)) {
    if (!head->next) {return head->data;}
    return op(head->data, foldr(head->next, op));
}

// 5. Левая ассоциативная свёртка (foldl)
int foldl(node* head, int(*op)(int, int)) {
    int acc = head->data;
    head = head->next;
    while (head) {
        acc = op(acc, head->data);
        head = head->next;
    }
    return acc;
}

// Вывод списка
void print_list(node* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    node* head = create_list(arr, 5);

    std::cout << "List: ";
    print_list(head);

    std::cout << "Sum: " << sum(head) << std::endl;
    std::cout << "Count: " << count(head) << std::endl;
    std::cout << "Foldr: " << foldr(head, [](int x, int y) {return x - y;}) << std::endl;
    std::cout << "Foldl: " << foldl(head, [](int x, int y) {return x - y;}) << std::endl;

    del_list(head);
    return 0;
}