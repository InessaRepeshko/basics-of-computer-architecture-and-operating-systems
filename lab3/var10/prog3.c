/* INDIVIDUAL TASK: THE FIRST PROGRAM */
/*Вариант №10. Разработать две программы. Первая принимает от пользователя квадратную матрицу,
вычисляет сумму элементов, лежащих на главной и побочной диагоналях, и выводит на экран.
 Вторая программа запускает первую в качестве вновь созданного процесса.*/

/* C program to print the sum of the elements on the main and side diagonals.
The program works with singed numbers from -999 to 9999.*/

/*Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog3.c -o prog3
./prog3 1 1
./prog3 2 1 2 3 4
./prog3 3 1 2 3 4 5 6 7 8 9
Adding the following output: output with matrix data + results of calculating.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //Determining the size of the matrix.
    int size, sum = 0;
    size = atoi(argv[1]);
    int matrix[size][size];

    //Checking the count of passed arguments.
    if (argc < 3
        || argc - 2 < size * size
        || (argc != 3
            && size != 1)) {
        fprintf(stderr, "There are too few arguments.\n"
               "Usage: %s <size_of_square_matrix> <element_of_matrix> ...\n", argv[0]);
        exit(1);
    }

    if (argc - 2 > size * size) {
        fprintf(stderr, "There are too many arguments.\n"
               "Usage: %s <size_of_square_matrix> <element_of_matrix> ...\n", argv[0]);
        exit(1);
    }

    //Checking that the arguments passed are numbers.
    for (int i = 1; i < argc; i++) {
        int argv_length = strlen(argv[i]);

        if (argv_length < 1
            || argv_length > 4 ) {
            fprintf(stderr, "Only numbers in the range [-999; +999] or [0; 9999] four chars long are allowed.\n"
                   "Usage: %s <size_of_square_matrix> <element_of_matrix> ...\n", argv[0]);
            exit(1);
        }

        for (int j = 0; j < argv_length; j++) {
            char *string = NULL;
            string = argv[i];

            if ((string[j] >= '0'
                && string[j] <= '9')
                || string[j] == '-'
                || string[j] == '+') {
                continue;
            } else {
                fprintf(stderr, "Only numerical values of the size and elements for the matrix are allowed.\n"
                       "Usage: %s <size_of_square_matrix> <element_of_matrix> ...\n", argv[0]);
                exit(1);
            }
        }
    }

    //Filling the matrix and calculating the sum of the elements along the diagonals.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = atoi(argv[i * size + j + 2]);

            if (i == j || i + j == size - 1) {
                sum += matrix[i][j];
            }
        }
    }

    //Output the matrix and the sum of the elements along the diagonals.
    printf("Entered matrix [%dx%d]:\n", size, size);

    for (int i = 0; i < size; i++) {
        printf("[ ");

        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }

        printf("]\n");
    }

    printf("Sum of elements along the major and minor diagonals: %d.\n", sum);

    return 0;
}
