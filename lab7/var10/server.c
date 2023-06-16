/* Індивідуальне завдання:
 * Вариант № 10
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через датаграмний сокет елементи введеної користувачем квадратної матриці.
 * Сервер приймає матрицю з іменованого конвеєра, потім обчислює суму елементів,
 * що лежать на головній і побічній діагоналях, і виводить на екран. */

/* Commands to run:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
./server
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCK_NAME "socket.soc"
#define BUF_SIZE 256
#define MAX_SIZE 10 //Max size of matrix

//Function to calculate the number of digits in number
int count_digits(int num) {
    if (num == 0) {
        return 1;  //If number is equal 0, there is one digit
    }

    int count = 0;

    while (num != 0) {
        count++;
        num /= 10;
    }

    return count;
}

int main(void) {
    struct sockaddr_in srvr_addr, client_addr; //Server and client address structures
    char buf[BUF_SIZE]; //Buffer to store received data
    int sock; //Socket descriptor
    int bytes;
    socklen_t client_len; //Length of the client address

    //Create a datagram socket
    printf("Create socket...\n");
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    memset(&srvr_addr, 0, sizeof(srvr_addr)); //Initialize server address structure
    srvr_addr.sin_family = AF_INET; //Set address family to IPv4
    srvr_addr.sin_addr.s_addr = htonl(INADDR_ANY); //Bind to any available network interface
    srvr_addr.sin_port = htons(12345); //Set port number to 12345

    //Bind the socket to the server address
    printf("Binding to socket...\n");

    if (bind(sock, (struct sockaddr*)&srvr_addr, sizeof(srvr_addr)) < 0) {
        perror("bind failed");
        close(sock);
        return EXIT_FAILURE;
    }

    while (1) {
        //Receive data from the client.
        printf("Waiting for data...\n");
        bytes = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *) &client_addr, &client_len);

        if (bytes < 0) {
            perror("recvfrom failed");
            close(sock);
            return EXIT_FAILURE;
        }

        buf[bytes] = '\0'; //Null-terminate the received data.

        if (buf[0] == 'q') {
            printf("Exiting server...\n");
            exit(-1);
        }

        printf("Reading matrix...\n");
        int sizeOfMatrix; //Size of matrix.

        //Get size of matrix from buffer.
        if (sscanf(&buf[0], "%d", &sizeOfMatrix) != 1) {
            printf("Invalid data format: %s\n", buf);
            break;
        }

        //Check the size of matrix
        if (sizeOfMatrix < 1) {
            fprintf(stderr, "Too small the matrix size.\n");
            continue;
        } else if (sizeOfMatrix >= MAX_SIZE) {
            fprintf(stderr, "Too large the matrix size.\n");
            continue;
        }

        //Read elements of matrix from buffer.
        int matrix[MAX_SIZE][MAX_SIZE];
        int k = 2; //Index for elements of buffer.

        for (int i = 0; i < sizeOfMatrix; i++) {
            for (int j = 0; j < sizeOfMatrix; j++) {
                matrix[i][j] = atoi(&buf[k]);
                k += count_digits(matrix[i][j]) + 1;
            }
        }

        //Calculate the sum of elements of matrix on the major and minor diagonals.
        int sumOfElementsOnDiagonals = 0;

        for (int i = 0; i < sizeOfMatrix; i++) {
            for (int j = 0; j < sizeOfMatrix; j++) {
                if (i == j || i + j == sizeOfMatrix - 1) { //If element belong the major or minor diagonals.
                    sumOfElementsOnDiagonals += matrix[i][j]; //Add it to sum.
                }
            }
        }

        //Matrix output to console.
        printf("Entered matrix [%dx%d]:\n", sizeOfMatrix, sizeOfMatrix);

        for (int i = 0; i < sizeOfMatrix; i++) {
            printf("[ ");

            for (int j = 0; j < sizeOfMatrix; j++) {
                printf("%d ", matrix[i][j]);
            }

            printf("]\n");
        }

        printf("Sum of elements on the main and minor diagonals: %d.\n", sumOfElementsOnDiagonals);
    }

    close(sock); //Close the socket.
    return 0;
}
