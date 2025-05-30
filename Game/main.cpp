#include <iostream>
#include "Game.h"

using namespace std;
int main() {
        bool playWithAI;
        cout << "--------Welcome To TIC-TAC-TOE------------" << endl;
        cout << "Do you want to play against the computer? (y/n): ";
        char choice;
        cin >> choice;
        string n1, n2;
        char s1, s2;
        if (choice == 'y' || choice == 'Y') {
            playWithAI = true;
            n2 = "Computer";
            cout << "Enter PLayer 1 name " << endl;
            cin >> n1;
            cout << "Enter PLayer 1 symbol" << endl;
            cin >> s1;
            cout << "Enter Player 2 symbol" << endl;
            cin >> s2;
        }
        else {
            playWithAI = false;
            cout << "Enter PLayer 1 name " << endl;
            cin >> n1;
            cout << "Enter PLayer 1 symbol" << endl;
            cin >> s1;
            cout << "Enter Player 2 name " << endl;
            cin >> n2;
            cout << "Enter Player 2 symbol" << endl;
            cin >> s2;
        }

        Game g(s1, s2, n1, n2, playWithAI);
        g.playGame();

        return 0;
    }


