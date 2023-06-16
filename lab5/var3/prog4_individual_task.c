/* Індивідуальне завдання.
 * Варіант №3
 * У пансіоні відпочивають і вдаються до роздумів 5 філософів, пронумеровані від 1 до 5.
 * У їдальні розташований круглий стіл, навколо якого розставлено 5 стільців, також пронумеровані від 1 до 5.
 * На столі знаходиться одна велика тарілка зі спагеті, яка поповнюється нескінченно,
 * також там розставлено 5 тарілок, у які накладають спагеті, і 5 виделок, призначення яких очевидне.
 * Для того щоб пообідати, філософ входить до їдальні і сідає на стілець зі своїм номером.
 * При цьому їсти філософ зможе тільки в тому разі, якщо вільні дві виделки - праворуч і ліворуч від його тарілки.
 * При виконанні цієї умови філософ піднімає одночасно обидві виделки і може поглинати їжу протягом якогось заданого часу.
 * В іншому випадку, філософу доводиться чекати звільнення обох виделок.
 * Пообідавши, філософ кладе обидві виделки на стіл одночасно і йде. Описаний процес відбувається нескінченно.
 * Скористатися об'єктами синхронізації типу "семафор". */

/* Commands to run:
gcc prog4_individual_task.c -o prog4_individual_task -lpthread
./prog4_individual_task
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <dispatch/dispatch.h>

#define NUM_PHILOSOPHERS 5
#define LEFT_FORK ((i-1) + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT_FORK ((i-1) + 1) % NUM_PHILOSOPHERS

dispatch_semaphore_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int i = (*(int*)arg) + 1;
    printf("Philosopher %d is looking at the table\n", i);

    while (1) {
        // Спроба взяти обидві виделки
        // Спочатку спроба взяти виделку, що ліворуч
        if (dispatch_semaphore_wait(forks[LEFT_FORK], DISPATCH_TIME_NOW) == 0) {
            printf("Philosopher %d took left fork %d\n", i, LEFT_FORK + 1);

            // Потім спроба взяти виделку, що праворуч
            if (dispatch_semaphore_wait(forks[RIGHT_FORK], DISPATCH_TIME_NOW) == 0) {
                printf("Philosopher %d took right fork %d\n", i, RIGHT_FORK + 1);

                printf("Philosopher %d is eating spaghetti\n", i);
                sleep(1); // час поглинання їжі

                // Звільнення виделки, що праворуч
                dispatch_semaphore_signal(forks[RIGHT_FORK]);
                printf("Philosopher %d put back right fork %d\n", i, RIGHT_FORK + 1);

                // Звільнення виделки, що ліворуч
                dispatch_semaphore_signal(forks[LEFT_FORK]);
                printf("Philosopher %d put back left fork %d\n", i, LEFT_FORK + 1);

                break; // завершення прийому їжі
            } else {
                // Звільнення виделки, що ліворуч, коли не вдалось взяти виделку, що праворуч
                dispatch_semaphore_signal(forks[LEFT_FORK]);
                printf("Philosopher %d put back left fork %d\n", i, LEFT_FORK + 1);
            }
        }

        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    printf("Press any key to start the program\n");
    getchar();
    pthread_t threads[NUM_PHILOSOPHERS];
    int args[NUM_PHILOSOPHERS];

    // Ініціалізація семафорів
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        forks[i] = dispatch_semaphore_create(1);
    }

    // Створення потоку для кожного філософа
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        args[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &args[i]);
    }

    // Очікування завершення роботи всіх потоків
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Threads joined\n");

    // Звільнення семафорів
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        dispatch_release(forks[i]);
    }

    return 0;
}
