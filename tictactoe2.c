#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

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
{
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

    // Horizontal
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2])
    {
        return 1;
    }
    else if (board[1][0] == board[1][1] && board[1][1] == board[1][2])
    {
        return 1;
    }
    else if (board[2][0] == board[2][1] && board[2][1] == board[2][2])
    {
        return 1;
    }

    // Verical

    else if (board[0][0] == board[1][0] && board[1][0] == board[2][0])
    {
        return 1;
    }
    else if (board[0][1] == board[1][1] && board[1][1] == board[2][1])
    {
        return 1;
    }
    else if (board[0][2] == board[1][2] && board[1][2] == board[2][2])
    {
        return 1;
    }

    // Cross
    else if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return 1;
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
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
        printf("Enter any number : ");
        scanf("%d", &input);
        move(input, player);

        isValidMove();

        player = !player;
    }

    return 0;
}
