#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

class Board {
    char cells[3][3];

public:
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cells[i][j] = ' ';
            }
        }
    }

    void displayBoard() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << cells[i][j];
                if (j < 2) cout << " | ";
            }
            cout << endl;
            if (i < 2) cout << "--+---+--" << endl;
        }
    }

    char getCell(int row, int col) const {
        return cells[row][col];
    }

    bool isEmptyCell(int row, int col) const {
        return cells[row][col] == ' ';
    }

    bool updateBoard(int place, char symbol) {
        int row = place / 3;
        int col = place % 3;
        if (cells[row][col] == ' ') {
            cells[row][col] = symbol;
            return true;
        }
        cout << "Place already taken. Try again." << endl;
        return false;
    }

    bool isFull() const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (cells[i][j] == ' ')
                    return false;
        return true;
    }

    bool checkWin(char symbol) const {
        for (int i = 0; i < 3; i++) {
            if (cells[i][0] == symbol && cells[i][1] == symbol && cells[i][2] == symbol) return true;
            if (cells[0][i] == symbol && cells[1][i] == symbol && cells[2][i] == symbol) return true;
        }
        if (cells[0][0] == symbol && cells[1][1] == symbol && cells[2][2] == symbol) return true;
        if (cells[0][2] == symbol && cells[1][1] == symbol && cells[2][0] == symbol) return true;
        return false;
    }

    void placeSymbol(int row, int col, char symbol) {
        cells[row][col] = symbol;
    }

    void removeSymbol(int row, int col) {
        cells[row][col] = ' ';
    }
};
