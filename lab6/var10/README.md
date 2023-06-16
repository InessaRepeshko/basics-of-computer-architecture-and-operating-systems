# Description
Lab work № 6 "Linux API - Introduction to interprocess communication. Channels." of Basics of computer architecture and operating systems.

**Main task description:**

Виконати індивідуальний варіант завдання, який має передбачати розробку двох програм (сервер і клієнт) і взаємодію між ними за допомогою поштових скриньок або конвеєрів. 
Розробити та налагодити сервер і клієнт відповідно до отриманого завдання.

**Individual task description:**

Варіант №10.
Розробити дві програми - сервер і клієнт. Клієнт відсилає серверу через іменований канал елементи введеної користувачем квадратної матриці. Сервер приймає матрицю з іменованого конвеєра, потім обчислює суму елементів, що лежать на головній і побічній діагоналях, і виводить на екран.

# Commands to run
```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./server
./client
```

# Examples of program results
```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic server.c -o server
./server
```
![server](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab6/var10/screens/server.png)

```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
2
1 2 3 4
2
-45 -39 45 38
```
![client](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab6/var10/screens/client.png)

© Inessa Repeshko. 2023
