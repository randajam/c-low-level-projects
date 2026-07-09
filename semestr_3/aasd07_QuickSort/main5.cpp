#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "function.h"

using namespace std;

int main() {
    ifstream fin("Data_100000.txt");
    vector<Person> a;

    if (!fin.is_open()) {
        cout << "Файл не найден!\n";
        return 1;
    }

    string name, patr, surn, date, code;

    while (fin >> name >> patr >> surn >> date >> code) {
        Person p;
        p.name = name;
        p.patronymic = patr;
        p.surname = surn;
        p.code = code;

        char dot;
        stringstream ss(date);
        ss >> p.day >> dot >> p.month >> dot >> p.year;

        a.push_back(p);
    }

    fin.close();

    counting_sort(a, 31, [&](const Person& p) { return p.day; });
    counting_sort(a, 12, [&](const Person& p) { return p.month; });

    counting_sort(a, 2025, [&](const Person& p) { return p.year; });

    for (int i = 0; i < 20 && i < a.size(); i++) {
        cout << a[i].surname << " " << a[i].name << " " << a[i].patronymic
             << " — " << a[i].day << "." << a[i].month << "." << a[i].year
             << " (" << a[i].code << ")\n";
    }
}
