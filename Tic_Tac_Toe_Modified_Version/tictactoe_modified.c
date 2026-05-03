#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"

char board[3][3];
int wins = 0, losses = 0, draws = 0;

void initBoard() {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + count++;
        }
    }
}

void drawBoard() {
    system("cls");
    printf("\n" BOLD MAGENTA "  --- TIC TAC TOE MODIFIED ---" RESET "\n\n");
    printf(CYAN "      Score: " GREEN "W: %d  " RED "L: %d  " BLUE "D: %d" RESET "\n\n", wins, losses, draws);
    
    for (int i = 0; i < 3; i++) {
        printf("\t ");
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') printf(BOLD RED " %c " RESET, board[i][j]);
            else if (board[i][j] == 'O') printf(BOLD BLUE " %c " RESET, board[i][j]);
            else printf(YELLOW " %c " RESET, board[i][j]);

            if (j < 2) printf(BOLD "|" RESET);
        }
        printf("\n");
        if (i < 2) printf("\t ---+---+---\n");
    }
    printf("\n");
}

int checkWin(char b[3][3]) {
    // Rows
    for (int i = 0; i < 3; i++)
        if (b[i][0] == b[i][1] && b[i][1] == b[i][2]) return (b[i][0] == 'X' ? 10 : -10);
    // Cols
    for (int i = 0; i < 3; i++)
        if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) return (b[0][i] == 'X' ? 10 : -10);
    // Diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) return (b[0][0] == 'X' ? 10 : -10);
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) return (b[0][2] == 'X' ? 10 : -10);

    return 0;
}

int isMovesLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') return 1;
    return 0;
}

int minimax(char b[3][3], int depth, int isMax) {
    int score = checkWin(b);
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(b)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] != 'X' && b[i][j] != 'O') {
                    char temp = b[i][j];
                    b[i][j] = 'X'; // AI is X in this logic
                    int val = minimax(b, depth + 1, !isMax);
                    if (val > best) best = val;
                    b[i][j] = temp;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b[i][j] != 'X' && b[i][j] != 'O') {
                    char temp = b[i][j];
                    b[i][j] = 'O'; // Human is O
                    int val = minimax(b, depth + 1, !isMax);
                    if (val < best) best = val;
                    b[i][j] = temp;
                }
            }
        }
        return best;
    }
}

void aiMove(int level) {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    if (level == 3) { // Hard - Minimax
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    int moveVal = minimax(board, 0, 0);
                    board[i][j] = temp;
                    if (moveVal > bestVal) {
                        bestRow = i;
                        bestCol = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
    } else if (level == 2) { // Medium - Simple logic
        // Check if AI can win
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';
                    if (checkWin(board) == 10) { bestRow = i; bestCol = j; break; }
                    board[i][j] = temp;
                }
            }
            if (bestRow != -1) break;
        }
        // Block opponent
        if (bestRow == -1) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] != 'X' && board[i][j] != 'O') {
                        char temp = board[i][j];
                        board[i][j] = 'O';
                        if (checkWin(board) == -10) { bestRow = i; bestCol = j; break; }
                        board[i][j] = temp;
                    }
                }
                if (bestRow != -1) break;
            }
        }
    }

    // Random move for easy or if no better move found in medium
    if (bestRow == -1) {
        int spots[9][2];
        int count = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    spots[count][0] = i; spots[count][1] = j; count++;
                }
        if (count > 0) {
            int r = rand() % count;
            bestRow = spots[r][0];
            bestCol = spots[r][1];
        }
    }

    if (bestRow != -1) board[bestRow][bestCol] = 'X';
}

int main() {
    srand(time(NULL));
    int choice, level, move;
    char playAgain;

    do {
        initBoard();
        printf(BOLD BLUE "Select Mode:\n" RESET);
        printf("1. Single Player (AI)\n2. Two Players\nChoice: ");
        scanf("%d", &choice);

        level = 1;
        if (choice == 1) {
            printf(BOLD CYAN "Select Level (1: Easy, 2: Medium, 3: Hard): " RESET);
            scanf("%d", &level);
        }

        int turn = 0; // 0 for O (Player), 1 for X (AI/P2)
        while (1) {
            drawBoard();
            if (turn == 0) {
                printf("Player O, enter move (1-9): ");
                scanf("%d", &move);
                int r = (move - 1) / 3, c = (move - 1) % 3;
                if (move < 1 || move > 9 || board[r][c] == 'X' || board[r][c] == 'O') {
                    printf(RED "Invalid move! Try again." RESET "\n");
                    system("pause");
                    continue;
                }
                board[r][c] = 'O';
            } else {
                if (choice == 1) {
                    aiMove(level);
                } else {
                    printf("Player X, enter move (1-9): ");
                    scanf("%d", &move);
                    int r = (move - 1) / 3, c = (move - 1) % 3;
                    if (move < 1 || move > 9 || board[r][c] == 'X' || board[r][c] == 'O') {
                        printf(RED "Invalid move! Try again." RESET "\n");
                        system("pause");
                        continue;
                    }
                    board[r][c] = 'X';
                }
            }

            int res = checkWin(board);
            if (res == 10) { drawBoard(); printf(BOLD RED "X Wins!\n" RESET); if (choice == 1) losses++; break; }
            if (res == -10) { drawBoard(); printf(BOLD GREEN "O Wins!\n" RESET); wins++; break; }
            if (!isMovesLeft(board)) { drawBoard(); printf(BOLD YELLOW "It's a Draw!\n" RESET); draws++; break; }

            turn = !turn;
        }

        printf("\nPlay again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
