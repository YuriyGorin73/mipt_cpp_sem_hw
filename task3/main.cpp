#include <iostream>

const int ROWS = 5;
const int COLS = 10;

void clear(char board[ROWS][COLS]) {
    for (int y = 0; y < ROWS; y++)
        for (int x = 0; x < COLS; x++)
            board[y][x] = ' ';
}

bool put(char board[ROWS][COLS], int x, int y, char symbol) {
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS)
        return false;

    board[y][x] = symbol;
    return true;
}

bool text(char board[ROWS][COLS], int x, int y, const char* word) {
    int length = 0;
    while (word[length] != '\0')
        length++;

    if (y < 0 || y >= ROWS || x < 0 || x + length > COLS)
        return false;

    for (int i = 0; i < length; i++)
        board[y][x + i] = word[i];

    return true;
}

void print(const char board[ROWS][COLS]) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++)
            std::cout << board[y][x];
        std::cout << '\n';
    }
}

bool equal(const char* first, const char* second) {
    int i = 0;
    while (first[i] && second[i]) {
        if (first[i] != second[i])
            return false;
        i++;
    }
    return first[i] == second[i];
}

int main() {
    char board[ROWS][COLS];
    char command[20];

    clear(board);

    while (std::cin >> command) {
        if (equal(command, "quit"))
            break;

        if (equal(command, "clear")) {
            clear(board);
        } else if (equal(command, "put")) {
            int x, y;
            char symbol;
            std::cin >> x >> y >> symbol;

            if (!put(board, x, y, symbol))
                std::cout << "error\n";
        } else if (equal(command, "text")) {
            int x, y;
            char word[100];
            std::cin >> x >> y >> word;

            if (!text(board, x, y, word))
                std::cout << "error\n";
        } else if (equal(command, "print")) {
            print(board);
        } else {
            std::cout << "error\n";
        }
    }

    return 0;
}
