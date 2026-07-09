#include "set.h"
#include <iostream>

using namespace std;

Set::Set(int size) {
    if (size > 256 || size < 0) {
        return;
    }
    for (int i = 0; i < size; i++) {
        cin >> this->members[i];
    }
    this->len = size;
}

Set::Set() {
    len = 0;
}

int Set::find(char h) {
    for (int i = 0; i < this->len; i++) {
        if (this->members[i] == h) {
            return i;
        }
    }
    return -1;
}

bool Set::is_member(char h) {
    for (int i = 0; i < this->len; i++) {
        if (this->members[i] == h) {
            return true;
        }
    }
    return false;
}

void Set::print() {
    for (int i = 0; i < this->len; i++) {
        cout << this->members[i] << " ";
    }
    cout << endl;
}

Set Set::operator+(const char h) {
    Set set_new;
    for (int i = 0; i < this->len; i++) {
        set_new.members[i] = this->members[i];
    }
    if (this->len < 255) {
        set_new.len = this->len + 1;
        set_new.members[this->len] = h;
    }
    return set_new;
}

Set Set::operator-(const char h) {
    Set set_new;
    for (int i = 0; i < this->len; i++) {
        if (this->members[i] != h) {
            set_new.members[set_new.len] = this->members[i];
            set_new.len += 1;
        }
    }
    return set_new;
}

Set Set::operator+(const Set &s) {
    Set set_new;
    for (int i = 0; i < this->len; i++) {
        set_new.members[i] = this->members[i];
        set_new.len += 1;
    }
    for (int i = 0; i < s.len; i++) {
        set_new.members[i + this->len] = s.members[i];
        set_new.len += 1;
    }
    return set_new;
}

Set Set::operator-(Set &s) {
    Set set_new;
    if (this->len > s.len) {
        for (int i = 0; i < this->len; i++) {
            if (s.is_member(this->members[i]) == true) {
                set_new.members[set_new.len] = this->members[i];
                set_new.len += 1;
            }
        }
    } else {
        for (int i = 0; i < s.len; i++) {
            if (this->is_member(s.members[i]) == true) {
                set_new.members[set_new.len] = s.members[i];
                set_new.len += 1;
            }
        }
    }
    return set_new;
}

Set Set::operator=(const Set &s) {
    for (int i = 0; i < s.len; i++) {
        this->members[i] = s.members[i];
    }
    this->len = s.len;
    return *this;
}

bool Set::operator==(const Set &s) {
    if (this->len != s.len) {
        return false;
    }
    for (int i = 0; i < s.len; i++) {
        if (this->members[i] != s.members[i]) {
            return false;
        }
    }
    return true;
}