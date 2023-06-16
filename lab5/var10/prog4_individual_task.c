/* Індивідуальне завдання.
 * Вариант № 10.
 * У перукарні розташоване єдине крісло, на якому спить перукар, і кілька стільців для клієнтів.
 * Коли клієнт приходить у перукарню, він будить перукаря, сідає в крісло.
 * Стрижка проводиться протягом заданого часу. Якщо ж крісло зайняте іншим клієнтом,
 * то новоприбулий клієнт займає будь-який вільний стілець і чекає своєї черги
 * (клієнти обслуговуються в порядку черговості, наприклад, часу прибуття).
 * Якщо всі стільці зайняті, то клієнт повертається і йде.
 * Коли обслужені всі клієнти, перукар сідає в крісло і знову засинає.
 * Описаний процес відбувається нескінченно.
 * Скористатися об'єктами синхронізації типу "мьютекс". */

/* Commands to run:
gcc prog4_individual_task.c -o prog4_individual_task -lpthread
./prog4_individual_task
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CLIENTS 7
#define MAX_CHAIRS 3

pthread_mutex_t barberChair;
pthread_mutex_t chairs[MAX_CHAIRS];
pthread_mutex_t finishedMutex; 
int numOccupiedChairs = 0;
int numFinishedClients = 0; 

void* client(void* arg) {
    int i = (*(int*)arg) + 1;
    // looking at the barber shop
    printf("Client %d arrived at the barber shop\n", i);

    while (1) {
        if (pthread_mutex_trylock(&barberChair) == 0) {
            // wake up barber and take the chair
            printf("Client %d woke up the barber and took the chair %d\n", i, numOccupiedChairs);

            // wait for haircut
            printf("Client %d is getting a haircut\n", i);
            sleep(2);

            // release the barber chair
            pthread_mutex_unlock(&barberChair);
            printf("Client %d finished the haircut and left the barber shop\n", i);

            pthread_mutex_lock(&finishedMutex); // grabbing the mutex
            numFinishedClients++; 
            pthread_mutex_unlock(&finishedMutex); // releasing the mutex

            pthread_exit(NULL); 
        } else {
            if (numOccupiedChairs < MAX_CHAIRS) {
                // take a waiting chair
                pthread_mutex_lock(&chairs[numOccupiedChairs]);
                numOccupiedChairs++;
                printf("Client %d took a waiting chair, number of occupied chairs = %d\n", i, numOccupiedChairs);

                // release the waiting chair 
                pthread_mutex_unlock(&chairs[numOccupiedChairs - 1]); 

                // wait for the barber chair
                pthread_mutex_lock(&barberChair);
                numOccupiedChairs--;
                printf("Client %d is getting a haircut, number of occupied chairs = %d\n", i, numOccupiedChairs);


                // release the barber chair 
                pthread_mutex_unlock(&barberChair); 
                printf("Client %d finished the haircut and left the barber shop\n", i);

                pthread_mutex_lock(&finishedMutex); // grabbing the mutex
                numFinishedClients++;
                pthread_mutex_unlock(&finishedMutex); // releasing the mutex

                pthread_exit(NULL);
            } else {
                // all waiting chairs are occupied, leave the barber shop
                printf("Client %d found no waiting chairs and left the barber shop\n", i);
                pthread_exit(NULL); 
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    printf("Press any key to start the program...\n");
    getchar();
    pthread_t threads[NUM_CLIENTS];
    int args[NUM_CLIENTS];

    // initialize mutexes
    pthread_mutex_init(&barberChair, NULL);
    for (int i = 0; i < MAX_CHAIRS; i++) {
        pthread_mutex_init(&chairs[i], NULL);
    }

    pthread_mutex_init(&finishedMutex, NULL); //инициализация нового мьютекса 

    // create client threads
    int index;
    for (index = 0; index < NUM_CLIENTS; index++) {
        args[index] = index;
        pthread_create(&threads[index], NULL, client, (void*)&args[index]);
    }

    while (1) { // infinite check loop
        if (pthread_mutex_trylock(&barberChair) == 0) {
            // If the barber is free, the client wakes him up and takes the chair
            printf("Client %d woke up the barber and took the chair %d\n", index, numOccupiedChairs);

            // Start the haircut process
            printf("Client %d is getting a haircut\n", index);
            sleep(2);

            // Freeing up the barber's chair
            pthread_mutex_unlock(&barberChair);
            printf("Client %d finished the haircut and left the barber shop\n", index);
            numFinishedClients++;

            // Check that all customers have been served
            if (numFinishedClients == NUM_CLIENTS && numOccupiedChairs == 0) {
                // If all customers have been served and there are no customers on the waiting chairs, exit the program
                printf("All clients finished\n");
                exit(0);
            }

            pthread_exit(NULL);
        } else {
            // If the barber is occupied, check if there are free waiting chairs
            if (numOccupiedChairs < MAX_CHAIRS) {
                // Taking the waiting chair
                pthread_mutex_lock(&chairs[numOccupiedChairs]);
                numOccupiedChairs++;
                printf("Client %d took a waiting chair, number of occupied chairs = %d\n", index, numOccupiedChairs);

                // Freeing up the waiting chair
                pthread_mutex_unlock(&chairs[numOccupiedChairs - 1]);

                // Waiting for the barber's chair to free up
                pthread_mutex_lock(&barberChair);
                numOccupiedChairs--;
                printf("Client %d is getting a haircut, number of occupied chairs = %d\n", index, numOccupiedChairs);

                // Freeing up the barber's chair
                pthread_mutex_unlock(&barberChair);
                printf("Client %d finished the haircut and left the barber shop\n", index);
                numFinishedClients++;

                // Check that all customers have been served
                if (numFinishedClients == NUM_CLIENTS && numOccupiedChairs == 0) {
                    // If all customers have been served and there are no customers on the waiting chairs, exit the program
                    printf("All clients finished\n");
                    exit(0);
                }

                pthread_exit(NULL);
            } else {
                // If all waiting chairs are occupied, the customer leaves
                printf("Client %d found no waiting chairs and left the barber shop\n", index);
                numFinishedClients++;

                // Check that all customers have been served
                if (numFinishedClients == NUM_CLIENTS && numOccupiedChairs == 0) {
                    // If all customers have been served and there are no customers on the waiting chairs, exit the program
                    printf("All clients finished\n");
                    exit(0);
                }

                pthread_exit(NULL);
            }
        }
    }

    pthread_exit(NULL);

    // destroy mutexes
    pthread_mutex_destroy(&barberChair);
    for (int i = 0; i < MAX_CHAIRS; i++) {
        pthread_mutex_destroy(&chairs[i]);
    }

    return 0;
}
