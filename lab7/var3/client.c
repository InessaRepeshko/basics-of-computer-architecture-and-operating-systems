/* Індивідуальне завдання:
 * Варіант № 3
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через датаграмний сокет введений користувачем рядок, що зберігає знакове ціле число.
 * Сервер приймає з поштової скриньки рядок, що зберігає знакове ціле число,
 * і  виводить на екран рядковий еквівалент цього числа прописом
 * (наприклад, введення "-1211" має призводити до виведення "мінус тисяча двісті одинадцять"). */

/* Commands to run:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
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
#define MAX_NUM_LEN 4

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
        printf("Enter the number: \n");
        fgets(buf, sizeof(buf), stdin); //Read user input from the console

        //Send the user input to the server
        if (sendto(sock, buf, strlen(buf) - 1, 0, (struct sockaddr*)&srvr_addr, sizeof(srvr_addr)) < 0) {
            perror("sendto failed");
            close(sock);
            return EXIT_FAILURE;
        }

        if (buf[0] == 'q') {
            printf("Exiting client...\n");
            break;
        }
    }

    close(sock); //Close the socket
    return 0;
}
