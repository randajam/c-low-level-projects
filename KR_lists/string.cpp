#include <iostream>

using namespace std;

struct node {
    char data;
    node* next;
};

node* void_create_nodes() {
    /*  
        Создает новый список, 
        считывая символы до
        символа перевода строки
    */

    node* root = new node();
    node* head = root;
    char ch;
    while ((ch = getchar()) != '\n') {
        root->data = ch;
        root->next = new node();
        root = root->next;
    }
    root->data = '\0';
    root->next = NULL;

    return head;
}

void view_node(node* head) {
    /*
        Выводит содержимое списка,
        не выводит '\0' и '\n'
    */
    node* root = head;
    while (root->next != NULL) {
        cout << root->data;
        root = root->next;
    }
    cout << endl;
}

int len_node(node* head) {
    /*
        Возвращает длину списка
        не считая '\0'
    */
    int n = 0;
    for (node* root = head; root->data != '\0'; root = root->next, n++);
    return n;
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool digit_word_in_node(node* head) {
    /*
        Проверяет строку на наличие cлова,
        состоящего только из цифр
        в списке, не считая '\0'
    */
    node* root = head;
    bool flag = false;
    bool is_digit_word = false;
    bool is_word = false;

    while (!flag && root != NULL) {
        if (is_word && is_digit_word && (root->data == ' ' || root->data == '\0')) {
            flag = true;
            is_digit_word = false;
            is_word = false;
        }
        else if (root->data == ' ' || root == head) {
            is_word = true;
            if (is_digit(root->next->data)) {
                is_digit_word = true;
            }
            else {
                is_digit_word = false;
            }
        }
        else if (is_word && !is_digit(root->data)) {
            is_digit_word = false;
        }
        root = root->next;
    }

    return flag;
}

bool is_alpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int counting_alpha(node* head) {
    /*
        Подсчитывает кол-во 
        отдельно стоящих букв
        в списке, не считая '\0'
    */
    node* root = head;
    int n = 0;

    while (root->next->next != NULL) {
        if (root == head && is_alpha(root->data) && root->next->data == ' ') {
            n++;
        }
        else if (root->data == ' ' && is_alpha(root->next->data) \
            && (root->next->next->data == ' ' || root->next->next->data == '\0')) {
            n++;
        }
        root = root->next;
    }

    return n;
    
}

int main(void) {
    node* head = void_create_nodes();
    view_node(head);
    cout << "Длина списка: " << len_node(head) << "\n";
    cout << "Кол-во букв: " << counting_alpha(head) << "\n";
    cout << "Содержится ли слово только из цифр: " << digit_word_in_node(head) << "\n";

    return 0;
}
