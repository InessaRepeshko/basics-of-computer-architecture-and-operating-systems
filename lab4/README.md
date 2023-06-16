# Description
Lab work № 4 "Background processes and signals" of Basics of computer architecture and operating systems.

**Main task description:**

Розробити додаток для Linux, який:
* запускається як демон (фоновий процес)
* відключається від термінала, повідомляє про себе в системному журналі та чекає сигналів;
* за сигналом SIGUSR1 записує інформацію про отримання сигналу в системний журнал;
* за сигналом SIGINT завершує виконання (теж із записом у журналі).
Уміти дивитися стан запущеного демона командою ps і пояснювати вміст
різних полів виведення ps.


# Commands to run
```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog1.c -o prog1
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog2.c -o prog2

./prog1
kill –USR1 11111 (PID)
kill –INT 11111 (PID)

./prog2 11111 (PID)

tail -f /var/log/system.log

ps -jx | grep 'PID\|prog'
ps –ux | grep ‘PID\|prog’
```

# Examples of program results
```
./prog1
kill –USR1 30441
tail -f /var/log/system.log
ps -jx | grep 'PID\|prog'
```
![prog1_1]()

```
./prog1
kill –INT 30490
tail -f /var/log/system.log
ps -jx | grep 'PID\|prog'
```
![prog1_2]()

```
./prog1
./prog2 30518
1
tail -f /var/log/system.log
ps -jx | grep 'PID\|prog'
```
![prog2_1]()

```
./prog1
./prog2 30518
2
tail -f /var/log/system.log
ps -jx | grep 'PID\|prog'
```
![prog2_2]()

© Inessa Repeshko. 2023
