/* INDIVIDUAL TASK: THE SECOND PROGRAM */
/*Вариант №10. Разработать две программы. Первая принимает от пользователя квадратную матрицу,
вычисляет сумму элементов, лежащих на главной и побочной диагоналях, и выводит на экран.
 Вторая программа запускает первую в качестве вновь созданного процесса.*/

/*Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog4.c -o prog4
./prog4 ./prog3 15
Adding the following line: Process exited with 0/1 status.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("There are too few arguments.\n"
               "Usage: <exec_file_current_prog> <exec_file_called_prog>\n");
        exit(1);
    }

    int status;
    pid_t pid = fork();
    char *exec = argv[1];

    if (exec == NULL) {
        printf("There is no data for exec file.\n");
        exit(1);
    }

    if (pid == -1) {
        perror("Fork error.");
        exit(1);
    }
    else if (pid == 0) { //Descendant process
        if (execv(exec, &argv[1]) == -1) { //Given path search
            perror("Execv error.");
            exit(1);
        }
    }
    else { //Ancestor process
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) { //Ancestor process
            printf("Process exited with %d status.\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
