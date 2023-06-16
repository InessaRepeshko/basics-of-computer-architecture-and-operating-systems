/* Основне завдання.
 * Розробити багатопоточну програму з викоританням мінімум двох потоків:
 * два потоки збільшують значення спільної змінної.
 * Необхідно забезпечити роботу програми без синхронізації (без використання семафорів). */

/* Commands to run:
gcc prog2_without_sync.c -o prog2_without_sync -lpthread
./prog2_without_sync
^C to end the programm
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define NUM_THREADS 2

int variable = 0;
char buffer[BUFFER_SIZE];
bool end_flag = false;

// Функція, яка буде виконуватися у потоках
void* thread_func(void* arg) {
    int id = *(int*)arg; // Ідентифікатор потока
    printf("Thread %d is running\n",id);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); // Встановлення режиму скасування для потока

    while(!end_flag){
        variable++;
        printf("Thread %d increased variable to %d\n", id, variable);
        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Створення потоків
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_ids[i]);
        sleep(1);
    }

    sleep(1);
    printf("Enter + to increase value of variable (enter 'end' to finish):\n");

    while(!end_flag) { // Зчитування даних з консолі
        fgets(buffer, BUFFER_SIZE, stdin);

        if (strncmp(buffer, "end", 3) == 0) {
            end_flag = true;

            for (int i = 0; i < NUM_THREADS; i++) {
                thread_ids[i] = i;
                pthread_cancel(threads[i]); // Скасування потоків
            }
        }
    }

    printf("Final value of variable: %d\n", variable);
    return 0;
}
