# Description
Lab work № 3 "Passing command line parameters to the program. Working with processes. Retrieving system information." of Basics of computer architecture and operating systems.

**Main task description:**

Разработать два приложения для Linux, первое из которых:
* при задании ключа -w имя-исполняемого-файла - запускает заданное приложение (с поиском его в системном пути, заданном переменной окружения PATH) - ожидает завершения приложения и выводит сообщение о завершении на экран вместе с кодом возврата 
* при задании ключа -f имя-исполняемого-файла - запускает заданное приложение (с поиском его в системном пути, заданном переменной окружения PATH) - немедленно продолжает выполнение (асинхронный запуск).

**Individual task description:**

Вариант №10.
Разработать две программы. Первая принимает от пользователя строку, хранящую знаковое целое число, и выводит на экран строковый эквивалент этого числа прописью (например, ввод «-1211» должен приводить к выводу «минус тысяча двести одиннадцать»). Вторая программа запускает первую в качестве вновь созданного процесса.

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
