#pragma once

#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void save_matrix_to_csv(const string &filename, const vector<vector<double>> &matrix) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file\n";
        return;
    }

    for (const auto &row : matrix) {
        for (size_t col = 0; col < row.size(); ++col) {
            file << row[col];
            if (col < row.size() - 1) {
                file << ", "; // Разделитель столбцов
            }
        }
        file << '\n'; // Перенос строки
    }

    file.close();
}

bool load_matrix_from_csv(const string &filename, vector<vector<double>> &matrix) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<double> row;
        string value;
        while (getline(iss, value, ',')) {
            row.push_back(stod(value));
        }
        matrix.push_back(row);
    }

    file.close();
    return true;
}