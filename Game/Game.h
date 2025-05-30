#pragma once
#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "Players.h"
#include "AIPlayer.h"

using namespace std;

class Game {
    Board board;
    Player* players[2];
    AIPlayer* ai;
    int currPlayer;
    bool vsAI;

public:
    Game(char s1, char s2, string n1, string n2, bool playWithAI = false) {
        players[0] = new Player(n1, s1);

        if (playWithAI) {
            vsAI = true;
            ai = new AIPlayer(s2, s1);
            players[1] = new Player("Computer", s2);
        }
        else {
            vsAI = false;
            ai = nullptr;
            players[1] = new Player(n2, s2);
        }

        currPlayer = rand() % 2;
    }

    ~Game() {
        delete players[0];
        delete players[1];
        if (ai) delete ai;
    }

    void switchPlayer() {
        currPlayer = 1 - currPlayer;
    }

    void playMove() {
        int move;
        if (vsAI && currPlayer == 1) {
            cout << "AI is thinking...\n";
            move = ai->findBestMove(board);
            cout << "AI chooses: " << move+1 << endl;
        }
        else {
            move = players[currPlayer]->makeMove();
        }

        while (!board.updateBoard(move, players[currPlayer]->getSymbol())) {
            move = players[currPlayer]->makeMove();
        }
    }

    void playGame() {
        while (true) {
            board.displayBoard();
            playMove();

            if (board.checkWin(players[currPlayer]->getSymbol())) {
                board.displayBoard();
                cout << players[currPlayer]->getname() << " wins!" << endl;
                break;
            }

            if (board.isFull()) {
                board.displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }

            switchPlayer();
        }
    }
};
