/* Основне завдання:
 * Розробити дві програми (сервер і клієнт) і взаємодію між ними за допомогою поштових скриньок або конвеєрів.
 * Розробити та налагодити сервер і клієнт відповідно до отриманого завдання.
 *
 * Індивідуальне завдання:
 * Варіант № 10:
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через іменований канал елементи введеної користувачем квадратної матриці.
 * Сервер приймає матрицю з іменованого конвеєра, потім обчислює суму елементів,
 * що лежать на головній і побічній діагоналях, і виводить на екран. */

/* Commands to run:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
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

    printf("Enter the size of the square matrix: ");
    scanf("%d", &sizeOfMatrix); // ввід розміру матриці від користувача

    printf("Enter the elements of the matrix: \n");

    for (int i = 0; i < sizeOfMatrix; i++) {
        for (int j = 0; j < sizeOfMatrix; j++) {
            scanf("%d", &matrix[i][j]); // ввід елементів матриці від користувача
        }
    }

    int fd;
    fd = open(FIFO_NAME, O_WRONLY); // відкриття FIFO файлу для запису

    if (fd == -1) {
        perror("Error open file."); // вивід помилки, якщо не вдалось відкрити файл
        exit(-1);
    }

    // Запис розміру матриці в FIFO
    write(fd, &sizeOfMatrix, sizeof(int));

    // Запис матриці в FIFO
    for (int i = 0; i < sizeOfMatrix; i++) {
        write(fd, matrix[i], sizeOfMatrix * sizeof(int));
    }

    close(fd); // закриття файлу FIFO
    unlink(FIFO_NAME); // видалення файлу FIFO

    return 0;
}
