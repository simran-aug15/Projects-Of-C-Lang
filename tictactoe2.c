#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Draw board
void draw()
{
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

// Check win
int checkWin()
{
    for (int i = 0; i < 3; i++)
    {
        // rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;

        // columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    // diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

// Check valid move
int isValidMove(int input)
{
    if (input < 1 || input > 9)
    {
        printf("Invalid input! Choose 1-9\n");
        return 0;
    }

    int row = (input - 1) / 3;
    int col = (input - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O')
    {
        printf("Spot already taken!\n");
        return 0;
    }

    return 1;
}

// Make move
void move(int input, int player)
{
    char ch = (player == 1) ? 'X' : 'O';

    int row = (input - 1) / 3;
    int col = (input - 1) % 3;

    board[row][col] = ch;
}

// Check draw
int isDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
        }
    }
    return 1;
}

int main()
{
    int input;
    int player = 1;
    int gameOver = 0;

    printf("TIC TAC TOE GAME\n");
    printf("Player 1 = X, Player 2 = O\n");

    getch();
    system("cls");

    while (!gameOver)
    {
        system("cls");
        draw();

        printf("\nPlayer %d enter move (1-9): ", player);
        scanf("%d", &input);

        if (isValidMove(input))
        {
            move(input, player);

            if (checkWin())
            {
                system("cls");
                draw();
                printf("\n🎉 Player %d wins!\n", player);
                gameOver = 1;
            }
            else if (isDraw())
            {
                system("cls");
                draw();
                printf("\n😐 Game Draw!\n");
                gameOver = 1;
            }
            else
            {
                player = (player == 1) ? 2 : 1;
            }
        }
        else
        {
            printf("Try again...\n");
            getch();
        }
    }

    return 0;
}
