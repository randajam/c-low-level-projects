#include <iostream>
#include "Game.h"

using namespace std;

int main() {

    // Тест 1: first
    {    
        int p1[] = {9, 8, 7, 6, 5};
        int p2[] = {4, 3, 2, 1, 0};
        Game g(5);
        g.init(p1, p2);
        cout << "TEST 1: ";
        g.run();
    }
    // Тест 2: second
    {   
        int p1[] = {0, 1, 2, 9, 8};
        int p2[] = {3, 4, 5, 6, 7};
        Game g(5);
        g.init(p1, p2);
        cout << "TEST 2: ";
        g.run();
    }
    // Тест 3: botva
    {    
        int p1[] = {2, 4, 1, 3, 5};
        int p2[] = {3, 5, 2, 4, 1};
        Game g(5);
        g.init(p1, p2);
        cout << "TEST 3: ";
        g.run();
    }
    cout << endl;
    
    // По заданию: second 5

    Game game(6);
    game.init();
    game.run();
    
    return 0;
}
