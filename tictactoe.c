#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
int xWins = 0;
int oWins = 0;
int draws = 0;
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
    printf(CYAN);
    printf("\n\n\t\t TIC TAC TOE GAME\n");
    printf(RESET);
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

//AI move for player O
void aiMove() {
    int move;

    do {
        move = rand() % 9 + 1;
    } while (!isValidMove(move));

    inputValue(move, 'O');
} 
// Main function
int main() {
    srand(time(0));
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
            printf(GREEN "\nPlayer X Turn -> Enter position (1-9): " RESET);
        } else {
            printf(GREEN "\nPlayer O Turn -> Enter position (1-9): " RESET);
        }
        
        if(player == 'X') {

    scanf("%d", &input);

    while (!isValidMove(input)) {
        printf(RED "\nInvalid Move! Try Again: " RESET);
        scanf("%d", &input);
    }

    inputValue(input, player);

}
else {

    printf(YELLOW "\nComputer is thinking...\n" RESET);

    aiMove();
}
        while (!isValidMove(input)) {
            printf(RED "\nInvalid Move! Try Again: " RESET);
            scanf("%d", &input);
        }

        inputValue(input, player);

        if (check()) {
            system("cls");
            draw();
            if (player == 'X') {
    xWins++;
    printf(GREEN "\nPlayer X Wins!\n" RESET);
} else {
    oWins++;
    printf(YELLOW "\nPlayer O Wins!\n" RESET);
}
            return 0;
        }

        player = (player == 'X') ? 'O' : 'X'; // Switch turns
        system("cls");
    }

draw();
draws++;

printf(CYAN "\nIt's a Draw!\n" RESET);

printf("\n====================\n");
printf("      SCOREBOARD\n");
printf("====================\n");
printf("Player X Wins : %d\n", xWins);
printf("Player O Wins : %d\n", oWins);
printf("Draws          : %d\n", draws);

char choice;

printf("\nPlay Again? (y/n): ");
scanf(" %c", &choice);

if(choice == 'y' || choice == 'Y') {
    system("cls");
    main();
}

return 0;
}