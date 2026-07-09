#include <iostream>
#include <string>

using namespace std;

string alphabet = "*абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

void source(string train, int position, string res);

int main() {
    setlocale(LC_ALL, "ru");
    string train = "211221-21221";
    cout << "First:" << endl;
    source("211221", 0, "");
    cout << "Second:" << endl;
    source("21221", 0, "");
    cout << endl;
    source(train, 0, "");

    return 0;
}

void source(string train, int position, string res) {
    if (position >= train.size()) {
        cout << res << endl;
        return;
    }

    switch (train[position]) {
    case '1':
        source(train, position + 1, res + "А");
        if (position + 1 <= train.size() && train[position + 1] == '2') {
            source(train, position + 2, res + "К");
        }
        if (position + 1 <= train.size() && train[position + 1] == '1') {
            source(train, position + 2, res + "Й");
        }
        break;
    case '2':
        source(train, position + 1, res + "Б");
        if (position + 1 <= train.size() && train[position + 1] == '1') {
            source(train, position + 2, res + "У");
        }
        if (position + 1 <= train.size() && train[position + 1] == '2') {
            source(train, position + 2, res + "Ф");
        }
        break;
    case '-':
        source(train, position + 1, res + '-');
    }
}
