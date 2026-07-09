#pragma once

class Set {
public:
    int len;
    char members[256];
    
    Set(int size);
    Set();
    int find(char h);
    bool is_member(char h);
    void print();
    Set operator+(const char h);
    Set operator-(const char h);
    Set operator+(const Set &s);
    Set operator-(Set &s);
    Set operator=(const Set &s);
    bool operator==(const Set &s);
};