#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret_number, guess, attempts = 0;
    
    // Seed random number generator
    srand(time(0));
    secret_number = rand() % 100 + 1; // Generates a number between 1 and 100

    printf("=== Welcome to the Number Guessing Game! ===\n");
    printf("I have chosen a number between 1 and 100.\n");
    printf("Can you guess what it is?\n\n");

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > secret_number) {
            printf("Too high! Try a lower number.\n\n");
        } else if (guess < secret_number) {
            printf("Too low! Try a higher number.\n\n");
        } else {
            printf("\nCongratulations! You guessed the number in %d attempts.\n", attempts);
        }
    } while (guess != secret_number);

    return 0;
}