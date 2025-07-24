/*
This program randomly generates a three digit number. The 
user has eight tries to guess the code. After each guess, 
the program gives feedback on if the number is too high/low, 
how many digits are correct and in the correct position, and 
how many are correct but in the wrong position. The user can 
quit by entering q. Three function prototypes will be above 
the main function and their full bodies will be on the bottom
of the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TRIES 8
#define DIGITS 3
#define RANGE 9
 
void split_digits(int number, int digits[]);
int count_correct_positions(int guess[], int code[]); 
int count_wrong_positions(int guess[], int code[]);

int main() {
    srand(time(0));
 
    int code_digits[DIGITS];
    int code_value = 0;
    for (int i = 0; i < DIGITS; i++) {
        code_digits[i] = rand() % (RANGE + 1);
        code_value = code_value * 10 + code_digits[i];
    }

    int tries = TRIES;
    char input[100];
 
    printf("You have 8 tries to guess the 3-digit code.\n");
    printf("Each digit ranges from 0 to 9 (q = quit)\n\n");
 
    while (tries > 0) {
        printf("%d tries remaining. Enter your guess: ", tries);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  
 
        if (strlen(input) == 1 && (input[0] == 'q' || input[0] == 'Q')) {
            printf("You quit :(\nThe correct code was: %d\n", code_value);  
            break;
        }
 
        if (strlen(input) != DIGITS) {
            printf("INVALID: Please enter exactly 3 digits.\n\n");
            continue;
        }
 
        int valid = 1;
        for (int i = 0; i < DIGITS; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }
 
        if (!valid) {
            printf("INVALID: Use digits only.\n\n");
            continue;
        }
 
        int guess_value = atoi(input);
        int guess_digits[DIGITS];
        for (int i = 0; i < DIGITS; i++) {
            guess_digits[i] = input[i] - '0';
        }
 
        if (guess_value == code_value) {
            printf("You guessed the code correctly! You win!\n");
            break;
        }
  
        printf("%s\n", guess_value > code_value ? "Too high." : "Too low.");  
        int correct_pos = count_correct_positions(guess_digits, code_digits);
        int wrong_pos = count_wrong_positions(guess_digits, code_digits); 
        printf("%d digit(s) are correct and in the correct position.\n", correct_pos);
        printf("%d digit(s) are correct but in the wrong position.\n\n", wrong_pos); 
 
        tries--;  
 
        if (tries == 0) {
            printf("Out of tries! The correct code was: %d\n", code_value);
        }
    }

    return 0;
}  

void split_digits(int number, int digits[]) {
    for (int i = DIGITS - 1; i >= 0; i--) {
        digits[i] = number % 10;
        number /= 10;
    }
}

int count_correct_positions(int guess[], int code[]) {
    int correct = 0;
    for (int i = 0; i < DIGITS; i++) {
        if (guess[i] == code[i]) {
            correct++;
        }
    }

    return correct;
}
 
int count_wrong_positions(int guess[], int code[]) {
    int guess_count[10] = {0}, code_count[10] = {0}; 
    for (int i = 0; i < DIGITS; i++) {
        if (guess[i] != code[i]) {
            guess_count[guess[i]]++;
            code_count[code[i]]++;
        }
    }

    int wrong_pos = 0;
    for (int i = 0; i <= RANGE; i++) {
        wrong_pos += guess_count[i] < code_count[i] ? guess_count[i] : code_count[i];
    }

    return wrong_pos;
}