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
void removeNumber()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Board
void draw()
{   printf(CYAN);
printf("\n\n\t\t TIC TAC TOE GAME\n\n");
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

// Logic
int check()
{
    for(int i = 0; i < 3; i++)
    {
        // Horizontal
        if(board[i][0] == board[i][1] &&
           board[i][1] == board[i][2] &&
           board[i][0] != ' ')
        {
            return 1;
        }

        // Vertical
        if(board[0][i] == board[1][i] &&
           board[1][i] == board[2][i] &&
           board[0][i] != ' ')
        {
            return 1;
        }
    }

    // Diagonal
    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2] &&
       board[0][0] != ' ')
    {
        return 1;
    }

    // Reverse diagonal
    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0] &&
       board[0][2] != ' ')
    {
        return 1;
    }

    return 0;
}

void move(int input, int player)
{

    char ch = ' ';
    if (player == 1)
    {
        ch = 'X';
    }
    else
    {
        ch = 'O';
    }

    if (input == 1)
    {
        board[0][0] = ch;
    }
    else if (input == 2)
    {
        board[0][1] = ch;
    }
    else if (input == 3)
    {
        board[0][2] = ch;
    }
    else if (input == 4)
    {
        board[1][0] = ch;
    }
    else if (input == 5)
    {
        board[1][1] = ch;
    }
    else if (input == 6)
    {
        board[1][2] = ch;
    }
    else if (input == 7)
    {
        board[2][0] = ch;
    }
    else if (input == 8)
    {
        board[2][1] = ch;
    }
    else if (input == 9)
    {
        board[2][2] = ch;
    }
}
int isValidMove(int input)
{
    if(input < 1 || input > 9)
    {
        return 0;
    }

    int row = (input - 1) / 3;
    int col = (input - 1) % 3;

    if(board[row][col] != ' ')
    {
        return 0;
    }

    return 1;
}

int main()
{
    int input;
    int player = 1;

    draw();

    printf("Press Any Key To Start !!");
    getch();
    system("cls");
    removeNumber();

    for (int i = 0; i < 9; i++)
    {
        system("cls");
        draw();
        if(player == 1)
{
    printf(GREEN "Player X Turn -> Enter position (1-9): " RESET);
}
else
{
    printf(YELLOW "Player O Turn -> Enter position (1-9): " RESET);
}
        scanf("%d", &input);

while(!isValidMove(input))
{
    printf(RED "\nInvalid Move! Try Again: " RESET);
    scanf("%d", &input);
}

move(input, player);
if(check())
{
    system("cls");
    draw();

    if(player == 1)
    {
        xWins++;
        printf(GREEN "\nPlayer X Wins!\n" RESET);
    }
    else
    {
        oWins++;
        printf(YELLOW "\nPlayer O Wins!\n" RESET);
    }

    printf("\n===== SCOREBOARD =====\n");
    printf("Player X Wins : %d\n", xWins);
    printf("Player O Wins : %d\n", oWins);
    printf("Draws          : %d\n", draws);

    return 0;
}

        if(player == 1)
{
    player = 2;
}
else
{
    player = 1;
}
    }
    draws++;

printf(CYAN "\nIt's a Draw!\n" RESET);

printf("\n===== SCOREBOARD =====\n");
printf("Player X Wins : %d\n", xWins);
printf("Player O Wins : %d\n", oWins);
printf("Draws          : %d\n", draws);
    return 0;
}
