#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

// Consts
const int BOARD_SIZE = 10;
const int CELL_SIZE = 50;
const int MINES = 10;

const int MINE = -1;
const int EMPTY = 0;

// Global variables
int board[BOARD_SIZE][BOARD_SIZE];
bool revealed[BOARD_SIZE][BOARD_SIZE];
bool flagged[BOARD_SIZE][BOARD_SIZE];
bool questionMarked[BOARD_SIZE][BOARD_SIZE];
sf::Font font;

// Colors for different numbers
sf::Color colors[] = {
    sf::Color::Blue, sf::Color::Green, sf::Color::Red,
    sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan,
    sf::Color::White, sf::Color::Black
};

// Function prototypes
void initializeBoard();
void reveal(int x, int y);
void checkForGameEnd(sf::RenderWindow& window);
void handleMouseClick(int x, int y, sf::Mouse::Button button);

int main(int argc, char* argv[]) {
    srand(time(0));
    initializeBoard();
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE), "Saper");
    sf::Texture cellTexture, mineTexture, noMineTexture, flagTexture, questionMarkTexture;

    if (!cellTexture.loadFromFile("res/cell.png") ||
        !mineTexture.loadFromFile("res/mine.png") ||
        !noMineTexture.loadFromFile("res/noMine.png") ||
        !flagTexture.loadFromFile("res/flag.png") ||
        !questionMarkTexture.loadFromFile("res/questionMark.png") ||
        !font.loadFromFile("res/font.ttf")) {
        return 1;
    }

    sf::Sprite cellSprite(cellTexture), mineSprite(mineTexture), noMineSprite(noMineTexture),
        flagSprite(flagTexture), questionMarkSprite(questionMarkTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / CELL_SIZE;
                int y = event.mouseButton.y / CELL_SIZE;
                handleMouseClick(x, y, event.mouseButton.button);
                checkForGameEnd(window);
            }
        }

        window.clear();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cellSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                window.draw(cellSprite);

                if (flagged[i][j]) {
                    flagSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                    window.draw(flagSprite);
                }
                else if (questionMarked[i][j]) {
                    questionMarkSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                    window.draw(questionMarkSprite);
                }
                else if (revealed[i][j]) {
                    if (board[i][j] == MINE) {
                        mineSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                        window.draw(mineSprite);
                    }
                    else if (board[i][j] == EMPTY) {
                        noMineSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                        window.draw(noMineSprite);
                    }
                    else {
                        sf::Text text;
                        text.setFont(font);
                        text.setString(std::to_string(board[i][j]));
                        text.setCharacterSize(24);
                        text.setFillColor(colors[board[i][j] - 1]);

                        sf::FloatRect textRect = text.getLocalBounds();
                        text.setOrigin(textRect.left + textRect.width / 2.0, textRect.top + textRect.height / 2.0);
                        text.setPosition(i * CELL_SIZE + CELL_SIZE / 2.0, j * CELL_SIZE + CELL_SIZE / 2.0);
                        window.draw(text);
                    }
                }
            }
        }
        window.display();
    }

    return 0;
}

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
            revealed[i][j] = false;
            flagged[i][j] = false;
            questionMarked[i][j] = false;
        }
    }

    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[x][y] == EMPTY) {
            board[x][y] = MINE;
            minesPlaced++;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == MINE) continue;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int ni = i + dx, nj = j + dy;
                    if (ni >= 0 && ni < BOARD_SIZE && nj >= 0 && nj < BOARD_SIZE) {
                        if (board[ni][nj] == MINE) {
                            board[i][j]++;
                        }
                    }
                }
            }
        }
    }
}

void reveal(int x, int y) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return;
    if (revealed[x][y]) return;
    revealed[x][y] = true;
    if (board[x][y] == EMPTY) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                reveal(x + dx, y + dy);
            }
        }
    }
}

void checkForGameEnd(sf::RenderWindow& window) {
    bool lost = false;
    bool won = true;

    // Check for loss
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (revealed[i][j] && board[i][j] == MINE) {
                lost = true;
                break;
            }
        }
        if (lost) break;
    }

    if (lost) {
        sf::Text text;
        text.setFont(font);
        text.setString("Game Over");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Red);
        text.setPosition(BOARD_SIZE * CELL_SIZE / 4, BOARD_SIZE * CELL_SIZE / 4);
        window.draw(text);
        window.display();

        // Wait a moment before closing the window
        Sleep(3000);
        window.close();
        return;
    }

    // Check for win
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != MINE && !revealed[i][j]) {
                won = false;
                break;
            }
        }
        if (!won) break;
    }

    if (won) {
        sf::Text text;
        text.setFont(font);
        text.setString("You Won!");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Green);
        text.setPosition(BOARD_SIZE * CELL_SIZE / 4, BOARD_SIZE * CELL_SIZE / 4);
        window.draw(text);
        window.display();

        // Wait a moment before closing the window
        Sleep(3000);
        window.close();
    }
}


void handleMouseClick(int x, int y, sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        if (!flagged[x][y]) reveal(x, y);
    }
    else if (button == sf::Mouse::Right) {
        if (flagged[x][y]) {
            flagged[x][y] = false;
            questionMarked[x][y] = true;
        }
        else if (questionMarked[x][y]) {
            questionMarked[x][y] = false;
        }
        else {
            flagged[x][y] = true;
        }
    }
}
