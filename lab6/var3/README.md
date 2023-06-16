# Description
Lab work № 6 "Linux API - Introduction to interprocess communication. Channels." of Basics of computer architecture and operating systems.

**Main task description:**

Виконати індивідуальний варіант завдання, який має передбачати розробку двох програм (сервер і клієнт) і взаємодію між ними за допомогою поштових скриньок або конвеєрів. 
Розробити та налагодити сервер і клієнт відповідно до отриманого завдання.

**Individual task description:**

Варіант №3.
Розробити дві програми - сервер і клієнт. Клієнт відсилає серверу через неіменований канал введений користувачем рядок, що зберігає знакове ціле число. Сервер приймає з поштової скриньки рядок, що зберігає знакове ціле число, і виводить на екран рядковий еквівалент цього числа прописом (наприклад, введення "-1211" має приводити до виведення "мінус тисяча двісті одинадцять").

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
![server](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab6/var3/screens/server.png)

```
gcc -std=c11 -Wall -Wextra -Werror -Wpedantic client.c -o client
./client
1234
./client
26
./client
-234
```
![client](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab6/var3/screens/client.png)

© Inessa Repeshko. 2023
