class Game {
    Board board;
    Player* players[2];
    AIPlayer* ai;
    int currPlayer;
    bool vsAI;
    sf::RenderWindow window;
    sf::Font font;

    // UI elements
    sf::Text titleText;
    sf::Text menuOptions[3];  // Play PvP, Play vs AI, Exit
    int selectedMenuIndex;

    sf::RectangleShape gridLines[4];  // 2 vertical, 2 horizontal lines
    sf::Text cells[9];

    bool gameOver;
    sf::Text statusText;

public:
    Game() : window(sf::VideoMode(600, 600), "Tic Tac Toe"), ai(nullptr), vsAI(false), currPlayer(0), selectedMenuIndex(0), gameOver(false) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Failed to load font\n";
            exit(1);
        }

        titleText.setFont(font);
        titleText.setString("Tic Tac Toe");
        titleText.setCharacterSize(48);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(150, 50);

        // Setup menu options
        std::string opts[3] = { "Play Player vs Player", "Play Player vs AI", "Exit" };
        for (int i = 0; i < 3; i++) {
            menuOptions[i].setFont(font);
            menuOptions[i].setString(opts[i]);
            menuOptions[i].setCharacterSize(30);
            menuOptions[i].setPosition(150, 150 + i * 60);
            menuOptions[i].setFillColor(i == selectedMenuIndex ? sf::Color::Yellow : sf::Color::White);
        }

        // Setup grid lines (3x3 cells, each 100x100 with margin)
        for (int i = 0; i < 2; i++) {
            gridLines[i].setSize(sf::Vector2f(4, 300));       // vertical lines
            gridLines[i].setFillColor(sf::Color::White);
            gridLines[i].setPosition(200 + i * 100, 150);
            gridLines[i + 2].setSize(sf::Vector2f(300, 4));     // horizontal lines
            gridLines[i + 2].setFillColor(sf::Color::White);
            gridLines[i + 2].setPosition(100, 250 + i * 100);
        }

        // Setup cell texts
        for (int i = 0; i < 9; i++) {
            cells[i].setFont(font);
            cells[i].setCharacterSize(80);
            cells[i].setFillColor(sf::Color::Cyan);
            // Center each text inside a 100x100 cell
            int row = i / 3;
            int col = i % 3;
            cells[i].setPosition(110 + col * 100, 160 + row * 100);
            cells[i].setString("");
        }

        statusText.setFont(font);
        statusText.setCharacterSize(24);
        statusText.setFillColor(sf::Color::White);
        statusText.setPosition(100, 500);
    }

    ~Game() {
        delete players[0];
        delete players[1];
        if (ai) delete ai;
    }

    void run() {
        while (window.isOpen()) {
            showMainMenu();
            if (!window.isOpen()) break;
            startGame();
        }
    }

private:
    void showMainMenu() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedMenuIndex = (selectedMenuIndex + 2) % 3;
                        updateMenuColors();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        selectedMenuIndex = (selectedMenuIndex + 1) % 3;
                        updateMenuColors();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedMenuIndex == 0) {
                            vsAI = false;
                            setupPlayers();
                            return;
                        }
                        else if (selectedMenuIndex == 1) {
                            vsAI = true;
                            setupPlayers();
                            return;
                        }
                        else if (selectedMenuIndex == 2) {
                            window.close();
                        }
                    }
                }
            }

            window.clear(sf::Color::Black);
            window.draw(titleText);
            for (int i = 0; i < 3; i++)
                window.draw(menuOptions[i]);
            window.display();
        }
    }

    void updateMenuColors() {
        for (int i = 0; i < 3; i++) {
            menuOptions[i].setFillColor(i == selectedMenuIndex ? sf::Color::Yellow : sf::Color::White);
        }
    }

    void setupPlayers() {
        delete players[0];
        delete players[1];
        if (ai) {
            delete ai;
            ai = nullptr;
        }

        players[0] = new Player("Player 1", 'X');
        if (vsAI) {
            players[1] = new Player("Computer", 'O');
            ai = new AIPlayer('O', 'X');
        }
        else {
            players[1] = new Player("Player 2", 'O');
        }
        currPlayer = 0;
        board.clearBoard();
        resetCellsText();
        gameOver = false;
        statusText.setString("");
    }

    void startGame() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }

                // Human move handling (both PvP and Player vs AI - when it's the human's turn)
                if (!gameOver && (!vsAI || currPlayer == 0) &&
                    event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    int move = getCellFromClick(event.mouseButton.x, event.mouseButton.y);
                    if (move != -1 && board.isEmptyCell(move / 3, move % 3)) {
                        board.updateBoard(move / 3, move % 3, players[currPlayer]->getSymbol());
                        updateCellText(move, players[currPlayer]->getSymbol());

                        if (board.checkWin(players[currPlayer]->getSymbol())) {
                            statusText.setString(players[currPlayer]->getName() + " wins!");
                            gameOver = true;
                        }
                        else if (board.isFull()) {
                            statusText.setString("It's a draw!");
                            gameOver = true;
                        }
                        else {
                            switchPlayer();
                        }
                    }
                }
            }

            // AI move (only runs in Player vs AI mode when it's the AI's turn)
            static bool aiThinking = false;
            static sf::Clock aiTimer;

            if (!gameOver && vsAI && currPlayer == 1) {
                if (!aiThinking) {
                    statusText.setString(players[currPlayer]->getName() + "'s Turn");

                    window.clear(sf::Color::Black);
                    for (int i = 0; i < 4; i++) window.draw(gridLines[i]);
                    for (int i = 0; i < 9; i++) window.draw(cells[i]);
                    window.draw(statusText);
                    window.display();

                    aiThinking = true;
                    aiTimer.restart();
                }
                else if (aiTimer.getElapsedTime().asSeconds() > 0.5f) {
                    int bestMove = ai->findBestMove(board);
                    if (bestMove != -1) {
                        board.updateBoard(bestMove / 3, bestMove % 3, players[currPlayer]->getSymbol());
                        updateCellText(bestMove, players[currPlayer]->getSymbol());

                        if (board.checkWin(players[currPlayer]->getSymbol())) {
                            statusText.setString(players[currPlayer]->getName() + " wins!");
                            gameOver = true;
                        }
                        else if (board.isFull()) {
                            statusText.setString("It's a draw!");
                            gameOver = true;
                        }
                        else {
                            switchPlayer();
                        }
                    }
                    aiThinking = false;
                }
            }
            else {
                aiThinking = false;
            }

            // Only update turn message if game is not over AND statusText wasn't already updated due to win/draw
            if (!gameOver && !(vsAI && currPlayer == 1 && aiThinking)) {
                statusText.setString(players[currPlayer]->getName() + "'s Turn");
            }

            // Draw everything
            window.clear(sf::Color::Black);
            for (int i = 0; i < 4; i++) window.draw(gridLines[i]);
            for (int i = 0; i < 9; i++) window.draw(cells[i]);
            window.draw(statusText);
            window.display();

            if (gameOver) {
                sf::sleep(sf::seconds(3));
                return;
            }
        }
    }



    int getCellFromClick(int x, int y) {
        if (x >= 100 && x < 400 && y >= 150 && y < 450) {
            int col = (x - 100) / 100;
            int row = (y - 150) / 100;
            return row * 3 + col;
        }
        return -1;
    }

    void updateCellText(int cellIndex, char symbol) {
        cells[cellIndex].setString(std::string(1, symbol));
    }

    void resetCellsText() {
        for (int i = 0; i < 9; i++)
            cells[i].setString("");
    }

    void switchPlayer() {
        currPlayer = 1 - currPlayer;
    }
};
