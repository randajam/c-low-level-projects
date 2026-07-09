#include <iostream>
#include "student.h"

int main() {
    double marks1[4] = {5, 4, 5, 5};
    double marks2[4] = {4, 4, 4, 4};
    double marks3[4] = {5, 5, 5, 5};

    Student s1("Ivan", "Petrov", "IU7-21", marks1);
    Student s2("Olga", "Ivanova", "IU7-22", marks2);

    Aspirant a1("Nikita", "Sidorov", "IU7-M1", "computer_science", marks3);
    Aspirant a2("Maria", "Kuznetsova", "IU7-M1", "biology", marks1);

    std::cout << "Student 1 scholarship: " << s1.getSchoolarship() << "\n";
    std::cout << "Student 2 scholarship: " << s2.getSchoolarship() << "\n\n";

    std::cout << "Aspirant 1 scholarship: " << a1.getSchoolarship() << "\n";
    std::cout << "Aspirant 2 scholarship: " << a2.getSchoolarship() << "\n";

    return 0;
}
