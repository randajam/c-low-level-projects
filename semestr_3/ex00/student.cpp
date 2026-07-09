#include "student.h"
#include <iostream>
#include <string>

void Student::SetRating() {
    double rat;
    for (int i = 0; i < 5; i++) {
        rat += this->grade[i];
    }
    this->rating = rat / 5;
}

void Student::SetRandomGrade() {
    for (int i = 0; i < 5; i++) {
        this->grade[i] = rand() % 5 + 1;
    }
}

void Student::SetName(string name) {
    this->name = name;
}

void Student::SetGroup(int group) {
    this->group = group;
}

double Student::GetRating() {
    return this->rating;
}

double Student::GetGrade(int i) {
    return this->grade[i];
}

string Student::GetName() {
    return this->name;
}

int Student::GetGroup() {
    return this->group;
}

void Student::Print() {
    cout << "Student: " << this->name << endl;
    cout << "Group: " << this->group << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Grade " << i + 1 << ": " << this->grade[i] << endl;
    }
    cout << "Rating: " << this->rating << endl;
}s