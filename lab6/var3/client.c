/* Основне завдання:
 * Розробити дві програми (сервер і клієнт) і взаємодію між ними за допомогою поштових скриньок або конвеєрів.
 * Розробити та налагодити сервер і клієнт відповідно до отриманого завдання.
 *
 * Індивідуальне завдання:
 * Варіант № 3:
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через неіменований канал введений користувачем рядок, що зберігає знакове ціле число.
 * Сервер приймає з поштової скриньки рядок, що зберігає знакове ціле число,
 * і виводить на екран рядковий еквівалент цього числа прописом
 * (наприклад, уведення "-1211" повинне призводити до виведення "мінус тисяча двісті одинадцять"). */

/* Commands to run:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "./number_fifo" // ім'я FIFO файлу
#define MAX_NUM_SIZE 100

int main(void) {
    char buf[MAX_NUM_SIZE]; // число цифрами

    printf("Enter the number: \n");
    fgets(buf, MAX_NUM_SIZE, stdin);

    // Змінити тип змінної num на масив char
    int lengthOfNumber = strlen(buf); // довжина числа
    char num[lengthOfNumber];
    strcpy(num, buf);
    lengthOfNumber = strlen(num);
    num[lengthOfNumber - 1] = '\0';

    int fd = open(FIFO_NAME, O_WRONLY); // відкриття FIFO файлу для запису

    if (fd == -1) {
        perror("Error open file."); // вивід помилки, якщо не вдалось відкрити файл
        exit(-1);
    }

    // Запис числа в FIFO
    write(fd, &num, lengthOfNumber + 1);

    close(fd); // закриття файлу FIFO
    unlink(FIFO_NAME); // видалення файлу FIFO

    return 0;
}
