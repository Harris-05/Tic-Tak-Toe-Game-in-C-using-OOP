#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Board {
private:
    std::array<std::array<char, 3>, 3> cells;

public:
    Board() {
        reset();
    }

    void reset() {
        for (auto& row : cells)
            for (char& cell : row)
                cell = ' ';
    }

    bool isEmptyCell(int row, int col) const {
        return cells[row][col] == ' ';
    }

    bool updateBoard(int row, int col, char symbol) {
        if (symbol == ' ' || cells[row][col] == ' ') {
            cells[row][col] = symbol;
            return true;
        }
        return false;
    }

    char getCell(int row, int col) const {
        return cells[row][col];
    }

    bool isFull() const {
        for (auto& row : cells)
            for (char cell : row)
                if (cell == ' ')
                    return false;
        return true;
    }

    bool checkWin(char symbol) const {
        for (int i = 0; i < 3; ++i) {
            if (cells[i][0] == symbol && cells[i][1] == symbol && cells[i][2] == symbol)
                return true;
            if (cells[0][i] == symbol && cells[1][i] == symbol && cells[2][i] == symbol)
                return true;
        }
        return (cells[0][0] == symbol && cells[1][1] == symbol && cells[2][2] == symbol) ||
            (cells[0][2] == symbol && cells[1][1] == symbol && cells[2][0] == symbol);
    }

    void draw(sf::RenderWindow& window, sf::Font& font) const {
        sf::RectangleShape line(sf::Vector2f(300, 5));
        line.setFillColor(sf::Color::Black);

        for (int i = 1; i < 3; ++i) {
            line.setPosition(100, i * 100);
            line.setSize(sf::Vector2f(300, 5));
            window.draw(line);

            line.setSize(sf::Vector2f(5, 300));
            line.setPosition(i * 100, 100);
            window.draw(line);
        }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (cells[i][j] != ' ') {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(cells[i][j]);
                    text.setCharacterSize(60);
                    text.setFillColor(sf::Color::Black);
                    text.setPosition(100 + j * 100 + 25, 100 + i * 100 + 10);
                    window.draw(text);
                }
            }
    }
};
