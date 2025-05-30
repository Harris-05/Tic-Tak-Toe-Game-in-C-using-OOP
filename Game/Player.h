#pragma once
#include <iostream>
using namespace std;

class Player {
    string name;
    char symbol;

public:
    Player(string n, char s) : name(n), symbol(s) {}

    string getname() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    int makeMove() const {
        int move;
        cout << name << " (" << symbol << ") - Enter your move (1-9): ";
        cin >> move;
        move--;
        return move;
    }
};
