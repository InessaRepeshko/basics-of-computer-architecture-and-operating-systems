/* MAIN TASK: THE SECOND PROGRAM */
/*Второе приложение должно выводить на экран:
- значения аргументов командной строки;
- идентификаторы: процесса (pid), сессии (sid), группы процессов (pgid) и процесса-предка (ppid);
- имя пользователя, под которым процесс запущен и его группу (полученные из файлов /etc/passwd и /etc/group).*/

/* Commands for running:
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog2.c -o prog2
./prog2 test_arg
./prog2 ./prog1
Adding the following output: arguments + all described ID's*/

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    pid_t pid = getpid(); //Descendant process ID
    pid_t ppid = getppid(); //Ancestor process ID
    pid_t sid = getsid(pid); //Current session ID
    pid_t pgid = getpgid(pid); //Process group ID
    uid_t uid = getuid(); //UID - User ID running the process
    gid_t gid = getgid(); //GID - User group ID running the process
    struct passwd *passwd_info = getpwuid(uid); //Provides access to information for a given UID
    struct group *group_info = getgrgid(gid); //Provides access to information for a given GID

    printf("Command line arguments:\t\t");

    for (int i = 1; i < argc; i++) {
        printf("%s\t", argv[i]);
    }

    printf("\nDescendant process ID (pid):\t%d\n", pid);
    printf("Ancestor process ID (ppid):\t%d\n", ppid);
    printf("Current session ID (sid):\t%d\n", sid);
    printf("Process group ID (pgid):\t%d\n", pgid);
    printf("User ID (uid):\t\t\t%s\n", passwd_info->pw_name);
    printf("User group ID (gid):\t\t%s\n", group_info->gr_name);

    return 0;
}
