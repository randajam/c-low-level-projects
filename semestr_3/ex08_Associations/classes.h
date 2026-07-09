#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class Position {
private:
    std::string code;
    std::string name;
    double baseHourlyRate;

public:
    Position(const std::string& code,
             const std::string& name,
             double baseHourlyRate): code(code), name(name), baseHourlyRate(baseHourlyRate) {}

    const std::string& GetCode() const { return code; }
    const std::string& GetName() const { return name; }
    double GetBaseHourlyRate() const {
        return baseHourlyRate;
    }
};

class Employee {
private:
    int number;
    std::string fullName;
    int rating;
    Position* position;

public:
    Employee(int number,
             const std::string& fullName,
             int rating,
             Position* pos): number(number), fullName(fullName), rating(rating), position(pos) {}

    int GetNumber() const { return number; }
    const std::string& GetFullName() const { return fullName; }
    int GetRating() const { return rating; }

    Position* GetPosition() const {
        if (position) {
            return position;
        } else {
            return nullptr;
        }
    }

    double GetHourlyRate() const {
        int bonus = 0;
        if (rating <= 5 && rating >= 1) bonus = 0.05 * (rating - 1) * position->GetBaseHourlyRate();
        return position->GetBaseHourlyRate() + bonus;
    }
};

class Customer {
private:
    std::string name;
    std::string contactPerson;
    std::string contactPhone;
    std::string contactEmail;

public:
    Customer(const std::string& name,
             const std::string& contactPerson,
             const std::string& contactPhone,
             const std::string& contactEmail): name(name), contactPerson(contactPerson), contactPhone(contactPhone), contactEmail(contactEmail) {}

    const std::string& GetName() const { return name; }
    const std::string& GetContactPerson() const { return contactPerson; }
    const std::string& GetContactPhone() const { return contactPhone; }
    const std::string& GetContactEmail() const { return contactEmail; }
};

class Task {
private:
    int number;
    std::string description;

    std::tm dueDate {};
    std::tm closeDate {};

    double hoursSpent;
    bool billable;

    Employee* responsible;

public:
    Task(int number,
         const std::string& description,
         const std::tm& dueDate,
         const std::tm& closeDate,
         double hoursSpent,
         bool billable,
         Employee* responsible): number(number), description(description),
                                dueDate(dueDate), closeDate(closeDate), hoursSpent(hoursSpent),
                                billable(billable), responsible(responsible) {}

    int GetNumber() const { return number; }
    const std::string& GetDescription() const { return description; }

    const std::tm& GetDueDate() const { return dueDate; }
    const std::tm& GetCloseDate() const { return closeDate; }

    double GetHoursSpent() const { return hoursSpent; }
    bool IsBillable() const { return billable; }

    Employee* GetResponsible() const { return responsible; }

    void SetDescription(const std::string& d) { description = d; }
    void SetDueDate(const std::tm& d) { dueDate = d; }
    void SetCloseDate(const std::tm& d) { closeDate = d; }

    static int days_between(const std::tm& a, const std::tm& b) {
        std::tm ta = a;
        std::tm tb = b;

        ta.tm_hour = tb.tm_hour = 0;
        ta.tm_min = tb.tm_min = 0;
        ta.tm_sec = tb.tm_sec = 0;
        ta.tm_isdst = tb.tm_isdst = -1;

        time_t time_a = mktime(&ta);
        time_t time_b = mktime(&tb);

        double diff = difftime(time_b, time_a);

        return static_cast<int>(diff / 86400);
    }

    double CalculateCost() const {
        if (!billable) { return 0.0; }

        double baseCost = hoursSpent * responsible->GetHourlyRate();

        int delay = days_between(dueDate, closeDate);
        
        if (delay < 0) return baseCost;

        double penalty = std::min(0.25, delay * 0.01);

        return baseCost * (1.0 + penalty);
    }
};

class Project {
private:
    std::string key;
    std::string title;
    double initialCost;

    Customer* customer;

    Task** tasks;
    int taskCount;
    int taskCapacity;

public:
    Project(const std::string& key,
            const std::string& title,
            double initialCost,
            Customer* customer): key(key), title(title), initialCost(initialCost), customer(customer) , taskCount(0), taskCapacity(4) {
                tasks = new Task*[taskCapacity];
            }

    ~Project() {
        for (int i = 0; i < taskCount; i++) {
            delete tasks[i];
        }
        delete[] tasks;
    }

    const std::string& GetKey() const { return key; }
    const std::string& GetTitle() const { return title; }
    double GetInitialCost() const { return initialCost; }
    Customer* GetCustomer() const { return customer; }

    void AddTask(Task* task) {
        if (!task) throw std::invalid_argument("Task pointer is null");

        if (taskCount == taskCapacity)
            ExpandTasks();

        tasks[taskCount++] = task;
    }

    void EditTask(int number) { 
        Task* t = nullptr;

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i]->GetNumber() == number) {
                t = tasks[i];
                break;
            }
        }

        if (!t) {
            std::cout << "Task not found\n";
            return;
        }

        std::cout << "Enter new description: ";
        std::string desc;
        std::getline(std::cin >> std::ws, desc);

        std::tm due{}, close{};
        std::cout << "Enter new due date (Y M D): ";
        std::cin >> due.tm_year >> due.tm_mon >> due.tm_mday;

        std::cout << "Enter new close date (Y M D): ";
        std::cin >> close.tm_year >> close.tm_mon >> close.tm_mday;

        t->SetDescription(desc);
        t->SetDueDate(due);
        t->SetCloseDate(close);

        std::cout << "Task updated\n";
    }

    void RemoveTask(int number) {
        int idx = -1;

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i]->GetNumber() == number) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            std::cout << "Task not found\n";
            return;
        }

        delete tasks[idx];

        for (int i = idx; i < taskCount - 1; i++)
            tasks[i] = tasks[i + 1];

        taskCount--;
    }

    double GetTotalCost() const {
        double total = initialCost;

        for (int i = 0; i < taskCount; i++) {
            total += tasks[i]->CalculateCost();
        }

        return total;
    }

    void ExpandTasks() {
        int newCap = taskCapacity * 2;
        Task** newArr = new Task*[newCap];

        for (int i = 0; i < taskCount; i++)
            newArr[i] = tasks[i];

        delete[] tasks;
        tasks = newArr;
        taskCapacity = newCap;
    }
};
