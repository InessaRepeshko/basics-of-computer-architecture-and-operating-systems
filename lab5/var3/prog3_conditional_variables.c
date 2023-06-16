/* Основне завдання.
 * Розробити багатопоточну програму з викоританням мінімум двох потоків:
 * два потоки з різною частотою зчитують і записують дані у спільний буфер памʼяті.
 * Необхідно забезпечити синхнонізовано роботу потоків у критичній секції з використанням умовних змінних. */

/* Commands to run:
gcc prog3_conditional_variables.c -o prog3_conditional_variables -lpthread
./prog3_conditional_variables
enter "end" to end the programm
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];
bool end_flag = false; // Прапор, що вказує на завершення введення даних
bool write_flag = false; // Прапор, що вказує на те, чи було записано дані до буферу
bool read_flag = false; // Прапорець, що вказує на те, чи були прочитані дані з буферу
pthread_mutex_t mutex; // Об'єкт м'ютекса використовується для синхронізації потоків
pthread_cond_t write_cond, read_cond; // Умовні змінні для синхронізації

void* write_thread(void* arg) {
    printf("Write thread is running\n");

    while (!end_flag) {
        pthread_mutex_lock(&mutex); // Блокування мʼютекса

        printf("Enter message to write to buffer (enter 'end' to finish):\n");
        fgets(buffer, BUFFER_SIZE, stdin); // Зчитування введеної строки з консолі

        if (strncmp(buffer, "end", 3) == 0) {
            end_flag = true;
            pthread_mutex_unlock(&mutex); // Звільнення мʼютекса
            pthread_exit(NULL);
        } else {
            write_flag = true;
            read_flag = false;
        }

        pthread_cond_signal(&read_cond); // Сигналізація потоку читання, що дані було записано
        pthread_cond_wait(&write_cond, &mutex); // Очікування потоку читання на сигнал, що дані були отримані
        pthread_mutex_unlock(&mutex); // Звільнення мʼютекса
        sleep(2);
    }

    pthread_exit(NULL); // Завершення потоку
}

void* read_thread(void* arg) {
    printf("Read thread is running\n");

    while (!end_flag) {
        pthread_mutex_lock(&mutex); // Блокування мʼютекса

        while (!write_flag && !end_flag) {
            pthread_cond_wait(&read_cond, &mutex);
            // Очікування потоку читання сигналу, що дані були записані
        }

        if (!end_flag) {
            printf("Buffer contents: %s", buffer); // Вивід вмісту файлу у консоль
            buffer[0] = '\0'; // Звільнення буферу
            read_flag = true;
            write_flag = false;
            pthread_cond_signal(&write_cond); // Сигналізація потоку запису, що дані було прочитано
        }

        pthread_mutex_unlock(&mutex); // Звільнення мʼютексу
        sleep(3);
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

    // Ініціалізція умовних змінних
    if (pthread_cond_init(&write_cond, NULL) != 0 || pthread_cond_init(&read_cond, NULL) != 0) {
        perror("Condition variable initialization failed");
        exit(EXIT_FAILURE);
    }

    // Створення потоку записку
    if (pthread_create(&write_t, NULL, write_thread, NULL) != 0) {
        perror("Write thread creation failed");
        exit(EXIT_FAILURE);
    }

    sleep(3);

    // Створення потоку читання
    if (pthread_create(&read_t, NULL, read_thread, NULL) != 0) {
        perror("Read thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Очікування завершення роботи потоків
    if (pthread_join(write_t, NULL)) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(read_t, NULL)) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Threads joined\n");

    // Знищення мʼютексу
    pthread_mutex_destroy(&mutex);
    return 0;
}
