#pragma once
#include "string"

using std::string;

class Student {
protected:
    string firstName, lastName, group;
    double averageMark[4];
public:
    Student (string firstName, string lastName, string group, double marks[4]) {
        for (int i = 0; i < 4; i++) {
            averageMark[i] = marks[i];
        }
        this->firstName = firstName;
        this->lastName = lastName;
        this->group = group;
    }

    double averageScore() {
        double res = 0;
        for (int i = 0; i < 4; i++) res += averageMark[i];
        return res / 4;
    }

    virtual int getSchoolarship() {
        double avg_score = averageScore();
        if (avg_score >= 4.5) return 10000;
        else return 8000;
    }
};

class Aspirant : public Student {
private:
    string scientificWork;
public:
    Aspirant(string firstName, string lastName, 
        string group, string scientificWork, double marks[4]): Student(firstName, lastName, group, marks) {
        this->scientificWork = scientificWork;
    }
    int getSchoolarship() override {
        double avg_score = averageScore();
        int bonus = 0;
        if (scientificWork == "computer_science") bonus = 1000;
        if (avg_score >= 4.5) return 20000 + bonus;
        else return 18000 + bonus;
    }
};