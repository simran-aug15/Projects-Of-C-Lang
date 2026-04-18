#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char board[3][3];

// Reset board with numbers 1 to 9
void resetBoard() {
    char value = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = value++;
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
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
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

// Validate move
int isValidMove(int input) {
    if (input < 1 || input > 9) {
        return 0;
    }

    int row = (input - 1) / 3;
    int col = (input - 1) % 3;

    return board[row][col] != 'X' && board[row][col] != 'O';
}

int main() {
    char choice;

    do {
        int input;
        char player = 'X';

        resetBoard();

        system("cls");
        draw();
        printf("Press any key to start!\n");
        getch();

        system("cls");

        for (int i = 0; i < 9; i++) {
            draw();

            printf("Player %c, your turn! Enter a number (1-9): ", player);
            scanf("%d", &input);

            while (!isValidMove(input)) {
                printf("Invalid move! Enter a valid number (1-9): ");
                scanf("%d", &input);
            }

            inputValue(input, player);

            if (check()) {
                system("cls");
                draw();
                printf("Player %c wins!\n", player);
                break;
            }

            if (i == 8) {
                system("cls");
                draw();
                printf("It's a draw!\n");
            }

            player = (player == 'X') ? 'O' : 'X';
            system("cls");
        }

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}