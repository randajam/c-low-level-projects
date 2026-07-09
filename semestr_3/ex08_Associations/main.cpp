#include <iostream>
#include <string>
#include <ctime>
#include "classes.h"

using namespace std;

std::tm MakeDate(int y, int m, int d) {
    std::tm t{};
    t.tm_year = y - 1900; // tm_year отсчитывается от 1900
    t.tm_mon  = m - 1;    // tm_mon отсчитывается с 0
    t.tm_mday = d;
    return t;
}

int main() {
    Position pos1("DEV", "Developer", 200);
    Position pos2("LEAD", "Lead Developer", 300);
    Position pos3("QA", "QA Engineer", 150);

    Employee emp1(1, "Stepan Zakharov", 5, &pos2);
    Employee emp2(2, "Maria Ivanova", 4, &pos1);
    Employee emp3(3, "Alexey Petrov", 3, &pos1);
    Employee emp4(4, "Olga Smirnova", 2, &pos1);
    Employee emp5(5, "Ivan Fedorov", 1, &pos3);
    Employee emp6(6, "Dmitry Kuznetsov", 2, &pos3);
    Employee emp7(7, "Anna Volkova", 4, &pos2);

    Employee* employees[] = {&emp1,&emp2,&emp3,&emp4,&emp5,&emp6,&emp7};
    int empCount = 7;

    Customer cust1("Acme Corp", "Ivan Ivanov", "+79990001122", "contact@acme.com");
    Customer cust2("Beta Ltd", "Maria Petrova", "+79991112233", "beta@beta.com");
    Customer cust3("Gamma Inc", "Sergey Sidorov", "+79992223344", "gamma@gamma.com");

    Customer* customers[] = {&cust1,&cust2,&cust3};
    int custCount = 3;

    cout << "Enter project key: ";
    string key;
    getline(cin, key);

    cout << "Enter project title: ";
    string title;
    getline(cin, title);

    cout << "Enter initial project budget: ";
    double budget;
    cin >> budget;

    cout << "\nSelect customer:\n";
    for (int i = 0; i < custCount; i++)
        cout << i+1 << ". " << customers[i]->GetName() << endl;

    int custChoice;
    cin >> custChoice;
    Customer* customer = customers[custChoice-1];

    Project project(key, title, budget, customer);

    // -----------------------------
    // Меню управления
    // -----------------------------
    while (true) {
        cout << "\n===== PROJECT MENU =====\n";
        cout << "1. Add task\n";
        cout << "2. Edit task\n";
        cout << "3. Remove task\n";
        cout << "4. Show total cost\n";
        cout << "5. Exit\n";
        cout << "Choose: ";

        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int number;
            string description;
            double hoursSpent;
            bool billable;
            int y1,m1,d1,y2,m2,d2;
            int empChoice;

            cout << "Task number: ";
            cin >> number;
            cin.ignore();

            cout << "Description: ";
            getline(cin, description);

            cout << "Hours spent: ";
            cin >> hoursSpent;

            cout << "Billable (1=yes, 0=no): ";
            cin >> billable;

            cout << "Due date (Y M D): ";
            cin >> y1 >> m1 >> d1;

            cout << "Close date (Y M D): ";
            cin >> y2 >> m2 >> d2;

            cout << "Select responsible employee:\n";
            for (int i = 0; i < empCount; i++)
                cout << i+1 << ". " << employees[i]->GetFullName() << endl;

            cin >> empChoice;
            Employee* responsible = employees[empChoice-1];

            Task* t = new Task(
                number,
                description,
                MakeDate(y1,m1,d1),
                MakeDate(y2,m2,d2),
                hoursSpent,
                billable,
                responsible
            );

            project.AddTask(t);
            cout << "Task added.\n";
        }
        else if (cmd == 2) {
            int num;
            cout << "Enter task number to edit: ";
            cin >> num;
            cin.ignore();
            project.EditTask(num);
        }
        else if (cmd == 3) {
            int num;
            cout << "Enter task number to remove: ";
            cin >> num;
            project.RemoveTask(num);
        }
        else if (cmd == 4) {
            cout << "Total project cost = " << project.GetTotalCost() << "\n";
        }
        else if (cmd == 5) {
            break;
        }
        else {
            cout << "Wrong command!\n";
        }
    }

    return 0;
}
