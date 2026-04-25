#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

// Reads an integer and clears the input buffer to prevent infinite loop on invalid input
int readInt(int *out) {
    int result = scanf("%d", out);
    while (getchar() != '\n');
    return result;
}

// Clear the board
void removeNumber() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Display the board
void draw() {
    printf("\n\t\t\t\t\t\t");
    printf(" %c %c %c %c %c \n", board[0][0], 186, board[0][1], 186, board[0][2]);
    printf("\t\t\t\t\t\t");
    printf("%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205);
    printf("\t\t\t\t\t\t");
    printf(" %c %c %c %c %c \n", board[1][0], 186, board[1][1], 186, board[1][2]);
    printf("\t\t\t\t\t\t");
    printf("%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205);
    printf("\t\t\t\t\t\t");
    printf(" %c %c %c %c %c \n", board[2][0], 186, board[2][1], 186, board[2][2]);
}

// Check for a win
int check() {
    // Horizontal
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
    }

    // Vertical
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return 1;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }

    return 0;
}

// Make a move
void inputValue(int input, char player) {
    int row = (input - 1) / 3;
    int col = (input - 1) % 3;
    board[row][col] = player;
}

// Validate a move
int isValidMove(int input) {
    if (input < 1 || input > 9) {
        return 0;
    }
    int row = (input - 1) / 3;
    int col = (input - 1) % 3;
    return board[row][col] == ' ';
}

// Main function
int main() {
    int input;
    char player = 'X'; // Player X starts the game
    int status = 0;

    draw();
    printf("Press any key to start!\n");
    getch();

    system("cls");
    removeNumber();

    for (int i = 0; i < 9; i++) {
        draw();

        if (player == 'X') {
            printf("Player X, your turn! Enter a number (1-9): ");
        } else {
            printf("Player O, your turn! Enter a number (1-9): ");
        }
        
        if (readInt(&input) != 1) input = -1;
        while (!isValidMove(input)) {
            printf("Invalid move! Enter a valid number (1-9): ");
            if (readInt(&input) != 1) input = -1;
        }

        inputValue(input, player);

        if (check()) {
            system("cls");
            draw();
            if (player == 'X') {
                printf("Player X wins!\n");
            } else {
                printf("Player O wins!\n");
            }
            return 0;
        }

        player = (player == 'X') ? 'O' : 'X'; // Switch turns
        system("cls");
    }

    draw();
    printf("It's a draw!\n");
    return 0;
}