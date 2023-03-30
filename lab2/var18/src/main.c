/* Разработать и отладить программный проект
 * (2 или больше исходных файла, взаимосвязанных между собой) в среде Linux
 * (c использованием IDE NetBeans, компилятора gcc/g++, менеджера проектов make и отладчика gdb).
 * Програмный проект должен реализовывать набор взаимосвязанных модулей, использующих стандартный ввод-вывод.
 * Составить программу для нахождения значений выражений А и В по заданным значениям исходных данных x,y,z.
 * Функции для нахождения А и В должны быть описаны в различных файлах. Исходные данные:
 * Вариант № 18:
 * A = 5 * arctgx - 0.25 * arctgy;
 * B = (x + 3 * |x - y| + x^(2)) / (|x - y|^(z) + z^(2)). */

#include "header.h"

int main() {
    //Values of the variables x, y, z for 18-th Variant.
    double x = -17.2;
    double y = 6.33;
    double z = 3.25;

    //Calculate the values of functions A and B with the given values of x, y, z.
    double result_a = function_a(x, y);
    double result_b = function_b(x, y, z);

    //Console output of function calculation results.
    printf("Values of the variables x, y, z:\tx = %f;\ty = %f;\tz = %f.\n"
           "Calculation result of functions:\tA = %f;\tB = %f.\n", x, y, z, result_a, result_b);

    return 0;
}
