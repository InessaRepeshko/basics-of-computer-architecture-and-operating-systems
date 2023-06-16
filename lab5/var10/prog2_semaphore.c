/* Основне завдання.
 * Розробити багатопоточну програму з викоританням мінімум двох потоків:
 * два потоки збільшують значення спільної змінної.
 * Необхідно забезпечити синхнонізовано роботу потоків у критичній секції з використанням семафорів. */

/* Commands to run:
gcc prog2_semaphore.c -o prog2_semaphore -lpthread
./prog2_semaphore
enter ^C to end the program
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>
#include <dispatch/dispatch.h>

#define BUFFER_SIZE 256
#define NUM_THREADS 2

int variable = 0;
char buffer[BUFFER_SIZE];
bool end_flag = false;
dispatch_semaphore_t semaphore;

// Функція, яка буде виконуватися у потоках
void* thread_func(void* arg) {
    int id = *(int*)arg; // Ідентифікатор потока
    printf("Thread %d is running\n",id);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); // Встановлення режиму скасування для потока

    while(!end_flag){
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER); // Очікування сигналу від семафору
        variable++; // Збільшення значення глобальної змінної
        printf("Thread %d increased variable to %d\n", id, variable);
    }

    pthread_exit(NULL); // Завершення потоку
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    semaphore = dispatch_semaphore_create(0); // Ініціалізація семафора

    // Створення потоків
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_ids[i]);
        sleep(1);
    }

    sleep(1);
    printf("Enter + to increase value of variable (Enter 'end' to finish):\n");

    while(!end_flag) { // Зчитування даних з консолі
        fgets(buffer, BUFFER_SIZE, stdin);

        if (strncmp(buffer, "end", 3) == 0) {
            end_flag = true;

            for (int i = 0; i < NUM_THREADS; i++) {
                thread_ids[i] = i;
                pthread_cancel(threads[i]); // Скасування потоків
            }
        }
        else if (strncmp(buffer, "+", 1) == 0) {
            dispatch_semaphore_signal(semaphore);
            // Збільшення значення семафору для розблокування потоку, що очікує семафор
        }
    }

    dispatch_release(semaphore); // Звільнення семафору
    printf("Final value of variable: %d\n", variable);
    return 0;
}
