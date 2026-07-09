#include <iostream>
#include "student.h"

using namespace std;

int main() {
    Student s1, s2;
    s1.SetName("Ivan I.I");
    s1.SetGroup(3);
    s1.SetRandomGrade();
    s1.SetRating();

    s2.SetName("Roman I.D");
    s2.SetGroup(5);
    s2.SetRandomGrade();
    s2.SetRating();

    s1.Print();
    s2.Print();
}