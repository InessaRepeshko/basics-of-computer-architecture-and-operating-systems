/* TASK:
Разработать приложение для Linux, которое:
- запускается как демон (фоновый процесс);
- отключается от терминала, сообщает о себе в системном журнале и ждет сигналов;
- по сигналу SIGUSR1 записывает информацию о получении сигнала в системный журнал;
- по сигналу SIGINT завершает выполнение (тоже с записью в журнале).
Уметь смотреть состояние запущенного демона командой ps и объяснять содержимое различных полей вывода ps.*/

/* Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog1.c -o prog1
./prog1
kill –USR1 11111 (PID)
kill –INT 11111 (PID)
tail -f /var/log/system.log
ps -jx | grep 'PID\|prog'
ps –ux | grep ‘PID\|prog’
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>
#include <syslog.h>

void user_handler(int signum) {
    switch (signum) {
        case SIGUSR1:
            syslog(LOG_INFO, "Received SIGUSR1 signal");
            break;
        case SIGINT:
            syslog(LOG_INFO, "Received SIGINT signal. Terminating.");
            //Closing the log
            closelog();
            exit(0);
            break;
    }
}

int main(void) {
    //Initialising the system log in the programme
    openlog("Lab4-daemon", LOG_PID, LOG_LOCAL0);

    //Creating a descendant to disconnect from the control terminal
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork error.\n");

        exit(1);
    }

    if (pid != 0) { //ancestor
        printf ("Daemon started with pid=%d\n", pid);
        syslog(LOG_INFO, "Daemon started with pid=%d\n", pid);

        exit(1);
    }

    //Changing the current directory to the root directory
    if (chdir("/") < 0) {
        perror("Chdir error.\n");

        exit(1);
    }

    //Closing all opened files (file descriptors)
    struct rlimit flim; //This structure contains rlim_max
    getrlimit(RLIMIT_NOFILE, &flim); //getting the maximum number of file descriptors

    for (unsigned int fd = 0; fd < flim.rlim_max; fd++) {
        close(fd);
    }

    //Creating a new session
    //The process becomes the leader of the new session and leader of the process group
    pid_t sid = setsid();

    if (sid < 0 ) {
        perror("Setsid error.\n");

        exit(1);
    }

    struct sigaction sa;
    sa.sa_handler = user_handler;
    sa.sa_flags = 0; //no need to use additional flags for signal processing

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    // Waiting for signals
    for(; ;) {
        pause();
    }

    // Should never reach this point
    closelog();

    return 0;
}
