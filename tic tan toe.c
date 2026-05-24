#include <iostream>
using namespace std;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Print board
void printBoard() {
    for (int i = 0; i < 9; i += 3) {
        cout << board[i] << " | " << board[i+1] << " | " << board[i+2] << endl;
        cout << "---------" << endl;
    }
}

// Check winner
bool checkWinner(char b[], char player) {
    int win[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; i++) {
        if (b[win[i][0]] == player &&
            b[win[i][1]] == player &&
            b[win[i][2]] == player)
            return true;
    }
    return false;
}

// Check if board full
bool isFull(char b[]) {
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
            return false;
    return true;
}

// Minimax function
int minimax(char b[], bool isAI) {
    if (checkWinner(b, 'O')) return 1;
    if (checkWinner(b, 'X')) return -1;
    if (isFull(b)) return 0;

    if (isAI) {
        int best = -100;
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'O';
                int score = minimax(b, false);
                b[i] = ' ';
                best = max(best, score);
            }
        }
        return best;
    } else {
        int best = 100;
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'X';
                int score = minimax(b, true);
                b[i] = ' ';
                best = min(best, score);
            }
        }
        return best;
    }
}

// Find best move
int bestMove() {
    int bestScore = -100;
    int move = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(board, false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

// Main game loop
int main() {
    while (true) {
        printBoard();

        int userMove;
        cout << "Enter position (0-8): ";
        cin >> userMove;

        if (board[userMove] != ' ') {
            cout << "Invalid move!\n";
            continue;
        }

        board[userMove] = 'X';

        if (checkWinner(board, 'X')) {
            printBoard();
            cout << "You win!\n";
            break;
        }

        if (isFull(board)) {
            printBoard();
            cout << "Draw!\n";
            break;
        }

        int aiMove = bestMove();
        board[aiMove] = 'O';
        cout << "AI chose: " << aiMove << endl;

        if (checkWinner(board, 'O')) {
            printBoard();
            cout << "AI wins!\n";
            break;
        }

        if (isFull(board)) {
            printBoard();
            cout << "Draw!\n";
            break;
        }
    }
    return 0;
}
