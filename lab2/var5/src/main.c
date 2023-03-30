/* Разработать и отладить программный проект
 * (2 или больше исходных файла, взаимосвязанных между собой) в среде Linux
 * (c использованием IDE NetBeans, компилятора gcc/g++, менеджера проектов make и отладчика gdb).
 * Програмный проект должен реализовывать набор взаимосвязанных модулей, использующих стандартный ввод-вывод.
 * Составить программу для нахождения значений выражений А и В по заданным значениям исходных данных x,y,z.
 * Функции для нахождения А и В должны быть описаны в различных файлах. Исходные данные:
 * Вариант № 5:
 * A = (y + (x - 1)^(1/3))^(1/2);
 * * B = |x - y| * (sin(z^(2)) + tgz). */

#include "header.h"

int main() {
//  Input data of variables x, y, z for variant № 5.
    double x = 17.4;
    double y = 10.3;
    double z = 0.82;

//    Calculate the values of functions A and B with the given values of x, y, z.
    double resultA = functionA(x, y);
    double resultB = functionB(x, y, z);

//    Output to the console the results of function calculations.
    printf("Input data of variables x, y, z for variant № 5:\n\tx = %f;\n\ty = %f;\n\tz = %f.\n"
           "Calculation result of functions:\n\tA = %f;\n\tB = %f.\n", x, y, z, resultA, resultB);

    return 0;
}
