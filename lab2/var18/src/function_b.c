#include "header.h"

double function_b(double x, double y, double z) {
    return (x + (3 * fabs(x - y)) + pow(x, 2))/(pow(fabs(x - y), z) + pow(z, 2));
}
