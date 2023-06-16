# Description
Lab work № 3 "Passing command line parameters to the program. Working with processes. Retrieving system information." of Basics of computer architecture and operating systems.

**Main task description:**

Розробити два додатки для Linux, перший з яких:
* при заданні ключа -w ім'я виконуваного-файлу - запускає заданий застосунок (з пошуком його в системному шляху, заданому змінною оточення PATH) - чекає завершення застосунку і виводить повідомлення про завершення на екран разом із кодом повернення 
* при заданні ключа -f ім'я-виконуваного-файлу - запускає заданий додаток (з пошуком його в системному шляху, заданому змінною оточення PATH) - негайно продовжує виконання (асинхронний запуск).

**Individual task description:**

Варіант №3.
Розробити дві програми. Перша приймає від користувача рядок, що зберігає знакове ціле число, і виводить на екран рядковий еквівалент цього числа прописом (наприклад, уведення "-1211" повинне приводити до виведення "мінус тисяча двісті одинадцять"). Друга програма запускає першу як новостворений процес.

# Commands to run
```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog1.c -o prog1
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog2.c -o prog2
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog3.c -o prog3
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic prog4.c -o prog4

./prog1 -f ./prog3 34
./prog1 -w ls ..

./prog2 test_arg
./prog2 ./prog1

./prog3 7
./prog3 12
./prog3 780
./prog3 1991

./prog4 ./prog3 15
```

# Examples of program results
```
./prog1 -f ./prog3 34
./prog1 -w ls ..
```
![prog1](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab3/var3/screens/prog1.png)

```
./prog2 test_arg
./prog2 ./prog1
```
![prog2](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab3/var3/screens/prog2.png)


```
./prog3 7
./prog3 12
./prog3 780
./prog3 1991
```
![prog3](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab3/var3/screens/prog3.png)

```
./prog4 ./prog3 15
```
![prog4](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab3/var3/screens/prog4.png)

© Inessa Repeshko. 2023
