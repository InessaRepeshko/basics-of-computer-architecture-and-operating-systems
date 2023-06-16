/* TASK:
Разработать приложение для Linux, которое:
- запускается как демон (фоновый процесс);
- отключается от терминала, сообщает о себе в системном журнале и ждет сигналов;
- по сигналу SIGUSR1 записывает информацию о получении сигнала в системный журнал;
- по сигналу SIGINT завершает выполнение (тоже с записью в журнале).
Уметь смотреть состояние запущенного демона командой ps и объяснять содержимое различных полей вывода ps.*/

/* Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog2.c -o prog2
./prog1
./prog2 11111 (PID)
tail -f /var/log/system.log
ps -jx | grep 'PID\|prog'
ps –ux | grep ‘PID\|prog’
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    //Checking for pid in command line arguments
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);

        exit(0);
    }

    pid_t pid = atoi(argv[1]);

    //Displaying a message about the possibility of selecting a signal
    printf("Choose a signal to send to process %d:\n1 - SIGINT\n2 - SIGUSR1\n", pid);

    //User selection of the signal
    int choice;
    scanf("%d", &choice);

    if (choice != 1
        && choice != 2) {
        printf("Invalid choice.\n");

        exit(0);
    }

    //Sending a process signal
    int signal;

    if (choice == 1) {
        signal = SIGINT;
    } else {
        signal = SIGUSR1;
    }

    if (kill(pid, signal) == -1) {
        perror("Kill error.");

        exit(0);
    }

    return 0;
}
