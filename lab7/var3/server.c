/* Індивідуальне завдання:
 * Варіант № 3
 * Розробити дві програми - сервер і клієнт.
 * Клієнт відсилає серверу через датаграмний сокет введений користувачем рядок, що зберігає знакове ціле число.
 * Сервер приймає з поштової скриньки рядок, що зберігає знакове ціле число,
 * і  виводить на екран рядковий еквівалент цього числа прописом
 * (наприклад, введення "-1211" має призводити до виведення "мінус тисяча двісті одинадцять"). */

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
#define MAX_NUM_LEN 4

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
        bytes = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&client_addr, &client_len);

        if (bytes < 0) {
            perror("recvfrom failed");
            close(sock);
            return EXIT_FAILURE;
        }

        buf[bytes] = '\0'; //Null-terminate the received data

        if (buf[0] == 'q') {
            printf("Exiting server...\n");
            break;
        }

        // Change the type of variable num to an array char
        int lengthOfNumber = strlen(buf); // довжина числа
        char num[lengthOfNumber];
        strcpy(num, buf);

        // Checking the length of a number
        if (lengthOfNumber == 0) {
            fprintf(stderr, "Empty string.\n");
            continue;
        }

        if (lengthOfNumber > MAX_NUM_LEN) {
            fprintf(stderr, "Length more than 4 is not supported.\n");
            continue;
        }

        // Check the digits of a number
        for (int i = 0; i < lengthOfNumber; i++) {
            if (num[i] >= '0'
                && num[i] <= '9') {
                continue;
            } else {
                fprintf(stderr, "Non-digital characters are not supported.\n");
                exit(-1);
            }
        }

        // The value of the numbers in the verbal equivalent.
        // The first line is not used, it only makes indexing easier.
        char* single_digits[] = { "zero", "one", "two",   "three", "four",
                                  "five", "six", "seven", "eight", "nine" };

        // The first line is not used, it only makes indexing easier.
        char* two_digits[] = { "",          "ten",      "eleven",  "twelve",
                               "thirteen",  "fourteen", "fifteen", "sixteen",
                               "seventeen", "eighteen", "nineteen" };

        // The first two lines are not used, they only make indexing easier.
        char* tens_multiple[] = { "",       "",        "twenty",
                                  "thirty", "forty",   "fifty",
                                  "sixty",  "seventy", "eighty",
                                  "ninety" };

        char* tens_power[] = { "hundred", "thousand" };

        // Output describing the result
        printf("The string equivalent of the %s in words: ", num);

        // Single digit number handling
        if (lengthOfNumber == 1) {
            printf("%s\n", single_digits[*num - '0']);
            continue;
        }

        // Handling a multi-digit number. Iterate until the number is equal to "\0"
        int index = 0;
        while (num[index] != '\0') {
            // Description for the first two digits of the number
            if (lengthOfNumber >= 3) {
                if (num[index] - '0' != 0) {
                    printf("%s ", single_digits[num[index] - '0']);
                    printf("%s ", tens_power[lengthOfNumber - 3]); // here length can be 3 or 4
                }

                --lengthOfNumber;
            }
            // Description for the last two digits of the number
            else {
                // Description for the first two digits of the number
                // Need to explicitly process the numbers 10-19.
                // The sum of two numbers is used as an index in the "two_digits" array
                if (num[index] == '1') {
                    int sum = num[index] - '0' + num[index + 1] - '0';
                    printf("%s\n", two_digits[sum]);
                    break;
                }
                // Need to explicitly process the number 20
                else if (num[index] == '2' && num[index + 1] == '0') {
                    printf("twenty\n");
                    break;
                }
                // Other two-digit numbers, for example, 21-99
                else {
                    int i = num[index] - '0';
                    printf("%s ", i ? tens_multiple[i] : "");
                    ++index;

                    if (num[index] != '0') {
                        printf("%s \n", single_digits[num[index] - '0']);
                    }
                }
            }
            ++index;

        }
    }

    close(sock); //Close the socket
    return 0;
}
