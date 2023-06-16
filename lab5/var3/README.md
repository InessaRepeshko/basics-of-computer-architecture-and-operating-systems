# Description
Lab work № 5 "Using streams" of Basics of computer architecture and operating systems.

**Main task description:**

1. Розробити три багатопотокові програми з використанням мінімум двох потоків і різних засобів синхронізації. Наприклад: два потоки записують і читають інформацію з одного файлу; два потоки збільшують значення спільної змінної; два потоки з різною частотою зчитують і записують дані в загальний буфер пам'яті.
2. Необхідно забезпечити синхронізовану роботу потоків у критичній секції з використанням:
* м'ютексів;
* семафорів;
* умовних змінних.
3. Переконатися в результативності застосування засобів синхронізації потоків, порівнявши результати роботи програм з використанням і без використання засобів синхронізації.

**Individual task description:**

Варіант №3.
У пансіоні відпочивають і вдаються до роздумів 5 філософів, пронумеровані від 1 до 5. У їдальні розташований круглий стіл, навколо якого розставлено 5 стільців, також пронумеровані від 1 до 5. На столі знаходиться одна велика тарілка зі спагеті, яка поповнюється нескінченно, також там розставлено 5 тарілок, у які накладають спагеті, і 5 виделок, призначення яких очевидне. Для того щоб пообідати, філософ входить до їдальні і сідає на стілець зі своїм номером. При цьому їсти філософ зможе тільки в тому разі, якщо вільні дві виделки - праворуч і ліворуч від його тарілки. При виконанні цієї умови філософ піднімає одночасно обидві виделки і може поглинати їжу протягом якогось заданого часу. В іншому випадку, філософу доводиться чекати звільнення обох виделок. Пообідавши, філософ кладе обидві виделки на стіл одночасно і йде. Описаний процес відбувається нескінченно. Скористатися об'єктами синхронізації типу "семафор".

# Commands to run
```
gcc prog1_mutex.c -o prog1_mutex -lpthread
./prog1_mutex
enter "end" to end the program

gcc prog2_semaphore.c -o prog2_semaphore -lpthread
./prog2_semaphore
enter ^C to end the program

gcc prog2_without_sync.c -o prog2_without_sync -lpthread
./prog2_without_sync
enter "end" to end the program

gcc prog3_conditional_variables.c -o prog3_conditional_variables -lpthread
./prog3_conditional_variables
enter "end" to end the program

gcc prog4_individual_task.c -o prog4_individual_task -lpthread
./prog4_individual_task
```

# Examples of program results
```
gcc prog1_mutex.c -o prog1 -lpthread
./prog1
```
![prog1_mutex](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab5/var3/screens/prog1_mutex.png)
![test_txt](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab5/var3/screens/test_txt.png)

```
gcc prog2_semaphore.c -o prog2 -lpthread
./prog2
```
![prog2_semaphore](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab5/var3/screens/prog2_semaphore.png)

```
gcc prog3_conditional_variables.c -o prog3 -lpthread
./prog3
```
![prog3_conditional_variables](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab5/var3/screens/prog3_conditional_variables.png)

```
gcc prog4_individual_task.c -o prog4 -lpthread
./prog4
```
![prog4_individual_task](https://github.com/InessaRepeshko/basics-of-computer-architecture-and-operating-systems/blob/main/lab5/var3/screens/prog4_individual_task.png)

© Inessa Repeshko. 2023
