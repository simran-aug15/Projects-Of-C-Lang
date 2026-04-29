#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

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

// Computer move logic
void computerMove(char comp, char human) {
    // 1. Try to win
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(i)) {
            inputValue(i, comp);
            if (check()) { return; } // Winning move found
            inputValue(i, ' '); // Undo
        }
    }
    // 2. Try to block
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(i)) {
            inputValue(i, human);
            if (check()) { 
                inputValue(i, comp); // Block the win
                return; 
            }
            inputValue(i, ' '); // Undo
        }
    }
    // 3. Random move
    int available[9];
    int count = 0;
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(i)) {
            available[count++] = i;
        }
    }
    if (count > 0) {
        int r = rand() % count;
        inputValue(available[r], comp);
    }
}

// Game loop logic
void playGame(int mode) {
    int input;
    char player = 'X'; // Human 1 is X
    char computerChar = 'O'; // Computer is O (if mode == 2)
    int moves = 0;

    system("cls");
    removeNumber();

    while (moves < 9) {
        draw();

        if (mode == 2 && player == computerChar) {
            printf("Computer's turn...\n");
            computerMove(computerChar, 'X');
        } else {
            if (player == 'X') {
                printf("Player X, your turn! Enter a number (1-9): ");
            } else {
                printf("Player O, your turn! Enter a number (1-9): ");
            }
            
            scanf("%d", &input);
            while (!isValidMove(input)) {
                printf("Invalid move! Enter a valid number (1-9): ");
                scanf("%d", &input);
            }

            inputValue(input, player);
        }

        if (check()) {
            system("cls");
            draw();
            if (mode == 2 && player == computerChar) {
                printf("Computer wins!\n");
            } else {
                printf("Player %c wins!\n", player);
            }
            printf("\nPress any key to return to the menu...");
            getch();
            return;
        }

        player = (player == 'X') ? 'O' : 'X'; // Switch turns
        moves++;
        system("cls");
    }

    draw();
    printf("It's a draw!\n");
    printf("\nPress any key to return to the menu...");
    getch();
}

void showMenu() {
    system("cls");
    printf("\n=============================\n");
    printf("        TIC-TAC-TOE\n");
    printf("=============================\n");
    printf("1) Player vs Player\n");
    printf("2) Player vs Computer\n");
    printf("3) Help / Instructions\n");
    printf("4) Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
}

void showHelp() {
    system("cls");
    printf("\n--- Instructions ---\n");
    printf("The game is played on a grid that's 3 squares by 3 squares.\n");
    printf("Players take turns putting their marks (X or O) in empty squares.\n");
    printf("The first player to get 3 of their marks in a row (up, down, across, or diagonally) is the winner.\n");
    printf("When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.\n");
    printf("\nBoard layout maps to numbers 1-9:\n");
    printf(" 1 | 2 | 3 \n");
    printf("-----------\n");
    printf(" 4 | 5 | 6 \n");
    printf("-----------\n");
    printf(" 7 | 8 | 9 \n");
    printf("\nPress any key to return to the menu...");
    getch();
}

// Main function
int main() {
    int choice;
    srand(time(NULL));

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        if (choice == 1) {
            playGame(1);
        } else if (choice == 2) {
            playGame(2);
        } else if (choice == 3) {
            showHelp();
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice! Press any key to try again.");
            getch();
        }
    }
    return 0;
}