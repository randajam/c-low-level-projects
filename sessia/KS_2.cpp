#include <iostream>

using namespace std;

bool is_variable(char* str, int &i);
bool is_constant(char* str, int &i);

int main(void) {
    char str[1000];
    int pos_id = -1;
    cin.getline(str, 1000);
    cout << str;
    bool result = true;

    do {
        pos_id++;
        result *= is_variable(str, pos_id);
        result *= (str[pos_id++] == ':');
        result *= (str[pos_id++] == '=');   
        result *= is_constant(str, pos_id);
        if (str[pos_id] == '+') {
            pos_id++;
            result *= is_variable(str, pos_id);
        }
    } while (result && str[pos_id] == ';');

    if (str[pos_id] != '$') result = false;
    
    if (result) {
        cout << "\nYES" << endl;
    } else {
        cout << "\nNO" << endl;
    }

    return 0;
}

bool is_variable(char* str, int &i) {
    bool result = true;

    if (str[i] >= 'A' && str[i] <= 'Z') {
        i++;
        do {
            if (str[i] == '[') {
                do {
                    i++;
                    if (str[i] >= 'A' && str[i] <= 'Z') {
                        i++;
                    } else if (!is_constant(str, i)) {
                        result = false;
                    }
                } while (result && str[i] == ',');

                if (str[i] != ']') {
                    result = false;
                } 
                i++;
            } else if (str[i] == '.') {
                i++;
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    i++;
                } else {
                    result = false;
                    i++;
                }
            } else if (str[i] == '@') {
                i++;
            } else {
                result = false;
            }
        } while (result && (str[i] == '[' || str[i] == '.' || str[i] == '@'));
    } else {
        result = false;
        i++;
    }

    return result;
}

bool is_constant(char* str, int &i) {
    bool result = true;
    if (str[i] >= '0' && str[i] <= '9') {
        while (str[i] >= '0' && str[i] <= '9') {
            i++;
        }
    }
    else {
        result = false;
    }
    return result;
}