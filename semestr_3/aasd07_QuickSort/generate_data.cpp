#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

// ------------------------
// Проверка високосного года
// ------------------------
bool isLeap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// ------------------------
// Количество дней в месяце
// ------------------------
int daysInMonth(int month, int year) {
    switch (month) {
        case 2: return isLeap(year) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

int main() {
    ofstream fout("Data_100000.txt");
    if (!fout.is_open()) {
        cout << "Ошибка: не удалось открыть файл!" << endl;
        return 1;
    }

    // ------------------------
    // Списки ФИО
    // ------------------------
    vector<string> names = {
        "Иван", "Петр", "Алексей", "Сергей", "Дмитрий", "Максим", "Егор",
        "Антон", "Андрей", "Кирилл", "Роман", "Олег", "Михаил", "Никита"
    };

    vector<string> patronymics = {
        "Иванович", "Петрович", "Алексеевич", "Сергеевич", "Дмитриевич",
        "Максимович", "Егорович", "Антонович", "Андреевич", "Кириллович"
    };

    vector<string> surnames = {
        "Иванов", "Петров", "Сидоров", "Сергеев", "Дмитриев", "Алексеев",
        "Кузнецов", "Соколов", "Смирнов", "Попов", "Васильев", "Захаров"
    };

    // ------------------------
    // Рандомизация
    // ------------------------
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distName(0, names.size() - 1);
    uniform_int_distribution<> distPatr(0, patronymics.size() - 1);
    uniform_int_distribution<> distSurn(0, surnames.size() - 1);

    uniform_int_distribution<> distYear(1950, 2020);
    uniform_int_distribution<> distMonth(1, 12);
    uniform_int_distribution<> distCode(100000, 999999);

    const int N = 100000;

    for (int i = 0; i < N; i++) {
        string name = names[distName(gen)];
        string patr = patronymics[distPatr(gen)];
        string surn = surnames[distSurn(gen)];

        int year = distYear(gen);
        int month = distMonth(gen);
        int day = uniform_int_distribution<>(1, daysInMonth(month, year))(gen);

        int code = distCode(gen);

        // Формат ДД.ММ.ГГГГ
        char dateBuf[20];
        sprintf(dateBuf, "%02d.%02d.%04d", day, month, year);

        fout << name << " "
             << patr << " "
             << surn << " "
             << dateBuf << " "
             << code;

        if (i + 1 < N) fout << "\n";
    }

    fout.close();
    cout << "Файл Data_100000.txt успешно создан!" << endl;
    return 0;
}
