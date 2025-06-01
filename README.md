# Tic Tac Toe Game in C++ (OOP-Based with AI and SFML GUI)

Welcome to this Tic Tac Toe game implemented in C++ using Object-Oriented Programming (OOP) principles. This project features both a command-line and a graphical user interface powered by SFML, alongside an intelligent AI opponent that uses the Minimax algorithm.

## Features

* Two-player mode (X vs O)
* Single-player mode against AI with Minimax algorithm
* Graphical interface with SFML for an interactive experience
* Intuitive mouse-based input handling
* Real-time visual feedback for moves and game status
* Input validation, turn-based logic, and game outcome detection (win/draw)
* Modular design with clean separation of logic and rendering
* Smooth AI move animation and delay for natural gameplay pacing

## Project Structure

* **Game.h** – Manages the main game loop, event handling, and game state
* **Player.h** – Handles player data and human inputs
* **AIPlayer.h** – Contains AI logic based on the Minimax algorithm
* **Board.h** – Maintains the board state and handles rendering of grid and symbols using SFML

## How to Compile and Run

### Requirements

* C++ compiler supporting C++11 or later (e.g., g++, clang++)
* SFML library installed (version 2.5 or later recommended)
* Compatible terminal and graphical environment (for SFML window)

### Compilation

Compile all source files and link SFML libraries. Example using g++:

```bash
g++ main.cpp -o TicTacToe -lsfml-graphics -lsfml-window -lsfml-system
```

### Running

Run the executable to launch the graphical Tic Tac Toe game window. Use mouse clicks to make moves, and play against another human or the AI.

---
