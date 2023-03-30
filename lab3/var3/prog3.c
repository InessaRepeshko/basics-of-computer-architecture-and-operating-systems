/* INDIVIDUAL TASK: THE FIRST PROGRAM */
/* Вариант №3. Разработать две программы. Первая принимает от пользователя строку,
хранящую знаковое целое число, и выводит на экран строковый эквивалент этого числа прописью
(например, ввод «-1211» должен приводить к выводу «минус тысяча двести одиннадцать»).
 Вторая программа запускает первую в качестве вновь созданного процесса.*/

/*Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog3.c -o prog3
./prog3 7
./prog3 12
./prog3 780
./prog3 1991
Adding the following output: output with number in words */

/* C program to print a given number in words. The program handles numbers from 0 to 9999 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A function that prints given number in words */
int main(int argc, char *argv[]) {
    /* Checking the number of given arguments */
    if (argc < 2) {
        fprintf(stderr, "Too few arguments.\n"
               "Usage: %s <number_in_digits>\n", argv[0]);
        exit(1);
    }

    if (argc > 2) {
        fprintf(stderr, "Too many arguments.\n"
               "Usage: %s <number_in_digits>\n", argv[0]);
        exit(1);
    }

    /* Get the number from argument value and length of this number */
    char *num = argv[1];
    int length = strlen(argv[1]);

    /* Checking the length of number */
    if (length == 0) {
        fprintf(stderr, "Empty string.\n");
        exit(1);
    }

    if (length > 4) {
        fprintf(stderr, "Length more than 4 is not supported.\n");
        exit(1);
    }

    /* Checking the digits in number */
    for (int i = 0; i < length; i++) {
        if (num[i] >= '0'
            && num[i] <= '9') {
            continue;
        } else {
            fprintf(stderr, "Non-digital characters are not supported.\n");
            exit(1);
        }
    }

    /* Values of numbers in word equivalents.
    The first string is not used, it is to make array indexing simple */
    char* single_digits[] = { "zero", "one", "two",   "three", "four",
                              "five", "six", "seven", "eight", "nine" };

    /* The first string is not used, it is to make array indexing simple */
    char* two_digits[] = { "",          "ten",      "eleven",  "twelve",
                           "thirteen",  "fourteen", "fifteen", "sixteen",
                           "seventeen", "eighteen", "nineteen" };

    /* The first two string are not used, they are to make array indexing simple*/
    char* tens_multiple[] = { "",       "",        "twenty",
                              "thirty", "forty",   "fifty",
                              "sixty",  "seventy", "eighty",
                              "ninety" };

    char* tens_power[] = { "hundred", "thousand" };

    /* An output describing the result */
    printf("The string equivalent of the \"%s\" in words: ", num);

    /* Handling for single-digit number */
    if (length == 1) {
        printf("%s\n", single_digits[*num - '0']);
        return 0;
    }

    /* Handling for multi-digit number. Iterate while num is not '\0' */
    while (*num != '\0') {
        /* Code path for first 2 digits */
        if (length >= 3) {
            if (*num - '0' != 0) {
                printf("%s ", single_digits[*num - '0']);
                printf("%s ", tens_power[length - 3]); // here length can be 3 or 4
            }

            --length ;
        }
        /* Code path for last 2 digits */
        else {
            /* Need to explicitly handle 10-19. Sum of the two digits is used
             * as index of "two_digits" array of strings */
            if (*num == '1') {
                int sum = *num - '0' + *(num + 1) - '0';
                printf("%s\n", two_digits[sum]);
                return 0;
            }
            /* Need to explicitly handle 20 */
            else if (*num == '2' && *(num + 1) == '0') {
                printf("twenty\n");
                return 0;
            }
            /* Rest of the two-digit numbers i.e., 21 to 99*/
            else {
                int i = *num - '0';
                printf("%s ", i ? tens_multiple[i] : "");
                ++num;

                if (*num != '0') {
                    printf("%s ", single_digits[*num - '0']);
                }
            }
        }

        ++num;
    }

    return 0;
}
