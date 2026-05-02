#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ─────────────────────────────────────────────
//  Board
// ─────────────────────────────────────────────
char board[3][3];

void resetBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = num++;
}

void draw() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("  ");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  -----------\n");
    }
    printf("\n");
}

// ─────────────────────────────────────────────
//  Move helpers
// ─────────────────────────────────────────────
int isValidMove(int input) {
    if (input < 1 || input > 9) return 0;
    int row = (input - 1) / 3;
    int col = (input - 1) % 3;
    return (board[row][col] != 'X' && board[row][col] != 'O');
}

void applyMove(int input, char player) {
    int row = (input - 1) / 3;
    int col = (input - 1) % 3;
    board[row][col] = player;
}

// ─────────────────────────────────────────────
//  Win / draw detection
// ─────────────────────────────────────────────
int checkWin(char p) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==p && board[i][1]==p && board[i][2]==p) return 1;
        if (board[0][i]==p && board[1][i]==p && board[2][i]==p) return 1;
    }
    if (board[0][0]==p && board[1][1]==p && board[2][2]==p) return 1;
    if (board[0][2]==p && board[1][1]==p && board[2][0]==p) return 1;
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') return 0;
    return 1;
}

// ─────────────────────────────────────────────
//  Minimax AI (Hard mode)
// ─────────────────────────────────────────────
int minimax(int isMaximizing) {
    if (checkWin('O')) return  10;
    if (checkWin('X')) return -10;
    if (isBoardFull())  return   0;

    int best = isMaximizing ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char saved = board[i][j];
                board[i][j] = isMaximizing ? 'O' : 'X';
                int score = minimax(!isMaximizing);
                board[i][j] = saved;
                if (isMaximizing) {
                    if (score > best) best = score;
                } else {
                    if (score < best) best = score;
                }
            }
        }
    }
    return best;
}

int bestMoveHard() {
    int bestScore = -1000, bestPos = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char saved = board[i][j];
                board[i][j] = 'O';
                int score = minimax(0);
                board[i][j] = saved;
                if (score > bestScore) {
                    bestScore = score;
                    bestPos   = i * 3 + j + 1;
                }
            }
        }
    }
    return bestPos;
}

// ─────────────────────────────────────────────
//  Easy AI: random valid move
// ─────────────────────────────────────────────
int bestMoveEasy() {
    int moves[9], count = 0;
    for (int i = 1; i <= 9; i++)
        if (isValidMove(i)) moves[count++] = i;
    if (count == 0) return -1;
    return moves[rand() % count];
}

// ─────────────────────────────────────────────
//  Player input
// ─────────────────────────────────────────────
int getPlayerMove() {
    int input;
    printf("Your turn (X) — enter position (1-9): ");
    while (scanf("%d", &input) != 1 || !isValidMove(input)) {
        while (getchar() != '\n'); // flush buffer
        printf("Invalid! Enter a valid position (1-9): ");
    }
    return input;
}

// ─────────────────────────────────────────────
//  Game loop — PvP
// ─────────────────────────────────────────────
void playPvP() {
    char player = 'X';
    resetBoard();
    for (int turn = 0; turn < 9; turn++) {
        draw();
        int input;
        printf("Player %c — enter position (1-9): ", player);
        while (scanf("%d", &input) != 1 || !isValidMove(input)) {
            while (getchar() != '\n');
            printf("Invalid! Try again: ");
        }
        applyMove(input, player);
        if (checkWin(player)) {
            draw();
            printf("🎉 Player %c wins!\n", player);
            return;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    draw();
    printf("🤝 It's a draw!\n");
}

// ─────────────────────────────────────────────
//  Game loop — PvC
// ─────────────────────────────────────────────
void playPvC(int difficulty) {
    resetBoard();
    // Player is X, Computer is O
    for (int turn = 0; turn < 9; turn++) {
        draw();
        int move;
        if (turn % 2 == 0) {
            // Human's turn
            move = getPlayerMove();
            applyMove(move, 'X');
            if (checkWin('X')) {
                draw();
                printf("🎉 You win! Well played!\n");
                return;
            }
        } else {
            // Computer's turn
            printf("Computer is thinking...\n");
            move = (difficulty == 1) ? bestMoveEasy() : bestMoveHard();
            applyMove(move, 'O');
            printf("Computer played position %d\n", move);
            if (checkWin('O')) {
                draw();
                printf("🤖 Computer wins! Better luck next time.\n");
                return;
            }
        }
    }
    draw();
    printf("🤝 It's a draw!\n");
}

// ─────────────────────────────────────────────
//  Main menu
// ─────────────────────────────────────────────
int main() {
    srand((unsigned int)time(NULL));
    int choice;

    printf("╔══════════════════════════════╗\n");
    printf("║      TIC-TAC-TOE  in  C      ║\n");
    printf("╚══════════════════════════════╝\n\n");

    do {
        printf("═══ MAIN MENU ═══\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer (Easy)\n");
        printf("3. Player vs Computer (Hard - Minimax AI)\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playPvP();
                break;
            case 2:
                playPvC(1);
                break;
            case 3:
                playPvC(2);
                break;
            case 4:
                printf("Thanks for playing! Goodbye 👋\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n\n");
        }

        // Replay prompt
        if (choice >= 1 && choice <= 3) {
            printf("\nPlay again? (1 = Yes, 0 = Back to menu): ");
            int replay;
            scanf("%d", &replay);
            if (!replay) choice = 0; // go back to menu
        }
        printf("\n");

    } while (choice != 4);

    return 0;
}
