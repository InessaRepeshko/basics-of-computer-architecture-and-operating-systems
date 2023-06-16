# Description
Lab work № 7 "Linux API - Introduction to interprocess communication. Sockets." of Basics of computer architecture and operating systems.

**Main task description:**

Виконати індивідуальний варіант завдання, який має передбачати розробку двох програм (сервер і клієнт) і взаємодію між ними за допомогою сокетів.
Розробити та налагодити сервер і клієнт відповідно до отриманого завдання.

**Individual task description:**

Варіант №10.
Розробити дві програми - сервер і клієнт. Клієнт відсилає серверу через датаграмний сокет елементи введеної користувачем квадратної матриці. Сервер приймає матрицю з іменованого конвеєра, потім обчислює суму елементів, що лежать на головній і побічній діагоналях, і виводить на екран.

# Commands to run
```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./server
./client
 "2 1 2 3 4" - size 2x2, elems = 1 2 3 4
 enter "q" to end the program
```

# Examples of program results
```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
./server
```
![server](serverhttps://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab7/var10/screens/server.png)

```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
2 1 20 67 456
3 -900 +900 2345 234 123 11 23
3 1 1 1 999 -999 +999
q
```
![client](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab7/var10/screens/client.png)

© Inessa Repeshko. 2023
