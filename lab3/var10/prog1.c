/* MAIN TASK: THE FIRST PROGRAM */
/*Разработать два приложения для Linux, первое из которых:
а) при задании ключа -w имя-исполняемого-файла - запускает заданное приложение
 (с поиском его в системном пути, заданном переменной окружения PATH) -
 ожидает завершения приложения и выводит сообщение о завершении на экран вместе с кодом возврата
б) при задании ключа -f имя-исполняемого-файла - запускает заданное приложение
 (с поиском его в системном пути, заданном переменной окружения PATH) -
 немедленно продолжает выполнение (асинхронный запуск).*/

/* Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog1.c -o prog1
./prog1 -f ./prog3 2 1 2 3 4
./prog1 -w ls ..
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    char *exec = NULL;
    int opt;
    int status;
    int sync = 1;

    //Parsing command line arguments using getopt().
    while ((opt = getopt(argc, argv, "w:f:")) != -1) {
        switch (opt) {
            case 'w':
                exec = optarg;
                sync = 1;
                break;
            case 'f':
                exec = optarg;
                sync = 0;
                break;
            default:
                printf("Usage: %s -w|-f exec\n", argv[0]);
                exit(1);
        }
    }

    if (exec == NULL) {
        printf("Usage: %s -w|-f exec\n", argv[0]);
        exit(1);
    }

    if (sync == 1) { //Running synchronous
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) { //Descendant process
            if (execvp(exec,  &argv[2]) == -1) {
                perror("Programme execution error");
                exit(1);
            }
        } else {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) { //Ancestor process //WIFEXITED(status) = true|false
                printf("Process exited with status %d\n", WEXITSTATUS(status)); //WEXITSTATUS(status) code є [0; 255]
            }
        }
    }
    else { //Running asynchronous
        pid_t pid, pid2;

        if ((pid = fork()) == -1) {
            perror("Fork error.");
            exit(1);
        }
        else if (pid == 0) { //Descendant process
            pid2 = fork();

            if (pid2 == -1) {
                perror("Fork error.");
                exit(1);
            }
            else if(pid2 == 0) { //Descendant process
                if (execvp(exec, &argv[2]) == -1) { //Default path search
                    perror("Programme execution error.");
                    exit(1);
                }
            }
            else { //Ancestor process
                printf("Attempt to run the descendant with pid=%d\n", pid2); //Descendant process
                exit(0);
            }
        }
        else { //Ancestor process
            waitpid(pid, NULL, 0);
        }
    }

    sleep(1);
    printf("Press <Enter> to exit:\n");
    getchar();

    return 0;
}
