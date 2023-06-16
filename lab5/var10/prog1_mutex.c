/* Основне завдання.
 * Розробити багатопоточну програму з використанням мінімум двох потоків:
 * два потоки записують і читають інформацію з одного файлу.
 * Необхідно забезпечити синхронізовано роботу потоків у критичній секції з використанням мʼютексів. */

/* Commands to run:
gcc prog1_mutex.c -o prog1_mutex -lpthread
./prog1_mutex
enter "end" to end the program
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define _REENTRANT // Підключення багатопотоковості
#define FILENAME "test.txt"
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];
pthread_mutex_t mutex; // Ініціалізація мʼютекса для синхронізації потоків
bool end_flag = false; // Прапор, що вказує на завершення введення даних

void* write_thread(void* arg) {
    printf("Write_thread is running\n");
    FILE* fp;

    while (!end_flag) {
        pthread_mutex_lock(&mutex); // Блокування мʼютекса
        printf("Enter message to write to file (Enter 'end' to finish):\n");
        fgets(buffer, BUFFER_SIZE, stdin); // Зчитування та зберігання введених даних у буфер

        if (strncmp(buffer, "end", 3) == 0) {
            end_flag = true; // Встановлення прапору, якщо введено "end"
        }

        fp = fopen(FILENAME, "a+"); // Відкриття файлу в режимі post

        if (fp != NULL && !end_flag) {
            fprintf(fp, "%s", buffer);
            fclose(fp);
        }

        pthread_mutex_unlock(&mutex); // Розблокування мʼютекса
        sleep(2);
    }

    pthread_exit(NULL); // Завершення потоку
}

void* read_thread(void* arg) {
    printf("Read_thread is running\n");
    FILE* fp;

    while (!end_flag) {
        pthread_mutex_lock(&mutex); // Блокування мʼютекса

        if(!end_flag) {
            printf("test.txt:\n");
            fp = fopen(FILENAME, "r"); // Відкриття файл у режимі read-only ("r").

            if (fp != NULL) {
                while (fgets(buffer, BUFFER_SIZE, fp)) { // Зчитування даних з файлу
                    printf("%s", buffer); // Вивід вмісту файлу у консоль
                    buffer[0] = '\0'; // Звільнення буферу
                }

                fclose(fp);
            }

            pthread_mutex_unlock(&mutex); // Розблокування мʼютекса
            sleep(3);
        }
    }

    pthread_exit(NULL); // Завершення потоку
}

int main() {
    pthread_t write_t, read_t;

    // Ініціалізація мʼютекса
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    // Створення потоку запису
    if (pthread_create(&write_t, NULL, write_thread, NULL) != 0) {
        perror("Write thread creation failed");
        exit(EXIT_FAILURE);
    }

    sleep(3);

    // Створення потоку зчитування
    if (pthread_create(&read_t, NULL, read_thread, NULL) != 0) {
        perror("Read thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Очікуання завершення роботи потоків
    if(pthread_join(write_t, NULL)) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    if(pthread_join(read_t, NULL)) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Threads joined\n");

    // Знищення мʼютексу
    pthread_mutex_destroy(&mutex);
    return 0;
}
