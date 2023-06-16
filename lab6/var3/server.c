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
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
./server
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
    char num[MAX_NUM_SIZE]; // число цифрами
    int lengthOfNumber; // довжина числа

    mkfifo(FIFO_NAME, 0600); // створюємо FIFO з правами доступу 0600

    int fd = open(FIFO_NAME, O_RDONLY); // відкриваємо FIFO для читання

    if (fd == -1) {
        perror("Error open file."); // виводимо помилку, якщо не вдається відкрити файл
        exit(EXIT_FAILURE);
    }

    read(fd, &num, MAX_NUM_SIZE*sizeof(char)); // читаємо число
    num[MAX_NUM_SIZE - 1] = '\0'; // додаємо завершуючий символ '\0'
    lengthOfNumber = strlen(num);

    // Перевірка довжини числа
    if (lengthOfNumber == 0) {
        fprintf(stderr, "Empty string.\n");
        exit(-1);
    }

    if (lengthOfNumber > 6) {
        fprintf(stderr, "Length more than 4 is not supported.\n");
        exit(-1);
    }

    // Перевірка цифр числа
    for (int i = 0; i < lengthOfNumber; i++) {
        if (num[i] >= '0'
            && num[i] <= '9') {
            continue;
        } else {
            fprintf(stderr, "Non-digital characters are not supported.\n");
            exit(-1);
        }
    }

    // Значення чисел у словесному еквіваленті.
    // Перший рядок не використовується, лише робить індексацію простішою.
    char* single_digits[] = { "zero", "one", "two",   "three", "four",
                              "five", "six", "seven", "eight", "nine" };

    // Перший рядок не використовується, лише робить індексацію простішою.
    char* two_digits[] = { "",          "ten",      "eleven",  "twelve",
                           "thirteen",  "fourteen", "fifteen", "sixteen",
                           "seventeen", "eighteen", "nineteen" };

    // Перші два рядки не використовуються, лише роблять індексацію простішою.
    char* tens_multiple[] = { "",       "",        "twenty",
                              "thirty", "forty",   "fifty",
                              "sixty",  "seventy", "eighty",
                              "ninety" };

    char* tens_power[] = { "hundred", "thousand" };

    // Вивід описуючий результат
    printf("The string equivalent of the %s in words: ", num);

    // Обробка однозначного числа
    if (lengthOfNumber == 1) {
        printf("%s\n", single_digits[*num - '0']);
        return 0;
    }

    // Обробка багатозначного числа. Ітеруємо поки число не дорівнює "\0"
    int index = 0;
    while (num[index] != '\0') {
        // Опис для перших двух цифр числа
        if (lengthOfNumber >= 3) {
            if (num[index] - '0' != 0) {
                printf("%s ", single_digits[num[index] - '0']);
                printf("%s ", tens_power[lengthOfNumber - 3]); // here length can be 3 or 4
            }

            --lengthOfNumber;
        }
            // Опис для останніх двух цифр числа
        else {
            // Опис для перших двух цифр числа
            // Потрібно явно опрацювати числа 10-19. Використовується сума двох чисел як індекс у "two_digits" масиві
            if (num[index] == '1') {
                int sum = num[index] - '0' + num[index + 1] - '0';
                printf("%s\n", two_digits[sum]);
                return 0;
            }
                // Потрібно явно опрацювати число 20
            else if (num[index] == '2' && num[index + 1] == '0') {
                printf("twenty\n");
                return 0;
            }
                // Інші двозначні числа, наприклад, 21-99
            else {
                int i = num[index] - '0';
                printf("%s ", i ? tens_multiple[i] : "");
                ++index;

                if (num[index] != '0') {
                    printf("%s ", single_digits[num[index] - '0']);
                }
            }
        }
        ++index;
        
    }

    close(fd); // закриваємо файл
    unlink(FIFO_NAME); // видаляємо FIFO

    return 0;
}
