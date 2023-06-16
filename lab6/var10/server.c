/* Індивідуальне завдання:
 * Розробити дві програми (сервер і клієнт) і взаємодію між ними за допомогою поштових скриньок або конвеєрів.
 * Розробити та налагодити сервер і клієнт відповідно до отриманого завдання.
 * Індивідуальне завдання:
 * Варіант № 10:
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через іменований канал елементи введеної користувачем квадратної матриці.
 * Сервер приймає матрицю з іменованого конвеєра, потім обчислює суму елементів,
 * що лежать на головній і побічній діагоналях, і виводить на екран. */

/* Commands to run:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
./server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "./matrix_fifo" // ім'я FIFO файлу
#define MAX_SIZE 10 // максимальний розмір матриці

int main(void) {
    int matrix[MAX_SIZE][MAX_SIZE];
    int sizeOfMatrix; // розмір матриці
    int sumOfElementsOnDiagonals = 0;

//    mkfifo(FIFO_NAME, 0600); // створюємо FIFO з правами доступу 0600

    // створюємо FIFO з правами доступу 0600, якщо він ще не існує виводимо помилку
    if (mkfifo(FIFO_NAME, 0600) != 0) {
        perror("Error creating a named pipe.");
        exit(-1);
    }

    int fd;
    fd = open(FIFO_NAME, O_RDONLY); // відкриваємо FIFO для читання

    if (fd == -1) {
        perror("Error open file."); // виводимо помилку, якщо не вдається відкрити файл
        exit(-1);
    }

    read(fd, &sizeOfMatrix, sizeof(int)); // читаємо розмір матриці

    // Перевірка введеного розміру матриці
    if (sizeOfMatrix < 1) {
        fprintf(stderr, "Too small the matrix size.\n");
        exit(-1);
    } else if (sizeOfMatrix > 10) {
        fprintf(stderr, "Too large the matrix size.\n");
        exit(-1);
    }

    for (int i = 0; i < sizeOfMatrix; i++) {
        read(fd, matrix[i], sizeOfMatrix * sizeof(int)); // читаємо елементи матриці
    }

    // Перевірка, що введені елементи належать допустимому диапазону
    for (int i = 0; i < sizeOfMatrix; i++) {
        for (int j = 0; j < sizeOfMatrix; j++) {
            if (matrix[i][j] < -999
                || matrix[i][j] > 999) {
                fprintf(stderr, "For elements only numbers in range [-999; 999] are allowed.\n");
                exit(-1);
            }
        }
    }

    // Підрахунок суми елементів на діагоналях матриці
    for (int i = 0; i < sizeOfMatrix; i++) {
        for (int j = 0; j < sizeOfMatrix ; j++) {
            if (i == j || i + j == sizeOfMatrix - 1) { // якщо елемент належить головній або бічній діагоналі
                sumOfElementsOnDiagonals += matrix[i][j]; // додаємо його до суми
            }
        }
    }

    // Вивід одержаної матриці у консоль
    printf("Entered matrix [%dx%d]:\n", sizeOfMatrix, sizeOfMatrix);

    for (int i = 0; i < sizeOfMatrix; i++) {
        printf("[ ");

        for (int j = 0; j < sizeOfMatrix; j++) {
            printf("%d ", matrix[i][j]);
        }

        printf("]\n");
    }

    printf("Sum of elements on the main and minor diagonals: %d.\n", sumOfElementsOnDiagonals);

    close(fd); // закриваємо файл
    unlink(FIFO_NAME); // видаляємо FIFO

    return 0;
}
