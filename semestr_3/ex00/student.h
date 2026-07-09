#pragma once

#include <string>

using namespace std;

class Student {
    private:
        string name;
        int group;
        double grade[5];
        double rating;

    public:
        void SetRating();
        double GetRating();
        void SetRandomGrade();
        double GetGrade(int i);
        void SetName(string name);
        string GetName();
        void SetGroup(int group);
        int GetGroup();
        void Print();
};