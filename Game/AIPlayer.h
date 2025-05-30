
#pragma once
#include "Board.h"
#include <limits>

class AIPlayer {
    char aiSymbol;
    char humanSymbol;

public:
    AIPlayer(char aiSym, char humanSym) : aiSymbol(aiSym), humanSymbol(humanSym) {}

    int findBestMove(Board& board) {
        int bestScore = std::numeric_limits<int>::min();
        int move = -1;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isEmptyCell(i, j)) {
                    board.placeSymbol(i, j, aiSymbol);
                    int score = minimax(board, false);
                    board.removeSymbol(i, j);

                    if (score > bestScore) {
                        bestScore = score;
                        move = i * 3 + j;
                    }
                }
            }
        }
        return move;
    }

private:
    int minimax(Board& board, bool isMaximizing) {
        if (board.checkWin(aiSymbol)) return +1;
        if (board.checkWin(humanSymbol)) return -1;
        if (board.isFull()) return 0;

        int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isEmptyCell(i, j)) {
                    board.placeSymbol(i, j, isMaximizing ? aiSymbol : humanSymbol);
                    int score = minimax(board, !isMaximizing);
                    board.removeSymbol(i, j);

                    if (isMaximizing)
                        bestScore = std::max(score, bestScore);
                    else
                        bestScore = std::min(score, bestScore);
                }
            }
        }

        return bestScore;
    }
};
