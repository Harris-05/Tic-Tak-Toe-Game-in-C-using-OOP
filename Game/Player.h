#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
    std::string name;
    char symbol;

public:
    Player(const std::string& n, char s) : name(n), symbol(s) {}

    char getSymbol() const { return symbol; }
    std::string getName() const { return name; }

    // Waits for mouse click on the board, returns cell index (row*3 + col)
    int makeMove(sf::RenderWindow& window) {
        while (true) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return -1;
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        // Board starts at (100,100), each cell 100x100
                        if (x >= 100 && x < 400 && y >= 100 && y < 400) {
                            int col = (x - 100) / 100;
                            int row = (y - 100) / 100;
                            return row * 3 + col;
                        }
                    }
                }
            }
        }
    }
};
