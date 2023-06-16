/* Індивідуальне завдання:
 * Вариант № 10
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через датаграмний сокет елементи введеної користувачем квадратної матриці.
 * Сервер приймає матрицю з іменованого конвеєра, потім обчислює суму елементів,
 * що лежать на головній і побічній діагоналях, і виводить на екран. */

/* Commands to run:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
 "2 1 2 3 4" - size 2x2, elems = 1 2 3 4
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
#define MAX_SIZE 10

int main(void) {
    struct sockaddr_in srvr_addr; // Server address structure
    char buf[BUF_SIZE]; // Buffer to store user input

    int sock; //Socket descriptor

    printf("Try to connect to socket...\n");
    sock = socket(AF_INET, SOCK_DGRAM, 0); //Create a datagram socket

    if (sock < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    //Set address family to IPv4
    srvr_addr.sin_family = AF_INET;
    srvr_addr.sin_port = htons(12345); //Set port number to 12345
    //Convert the string IP address to binary form and store it in srvr_addr.sin_addr
    if (inet_aton("127.0.0.1", &srvr_addr.sin_addr) == 0) {
        fprintf(stderr, "inet_aton failed\n");
        close(sock);
        return EXIT_FAILURE;
    }

    while (1) {

        printf("Enter the size of the square matrix and elements of matrix: ");
        fgets(buf, sizeof(buf) - 1, stdin); //Read user input from the console

        //Send the user input to the server
        if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&srvr_addr, sizeof(srvr_addr)) < 0) {
            perror("sendto failed");
            close(sock);
            break;
        }

        if (buf[0] == 'q') {
            printf("Exiting client...\n");
            break;
        }
    }

    close(sock); //Close the socket
    return 0;
}
