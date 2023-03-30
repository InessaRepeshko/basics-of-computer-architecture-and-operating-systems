#include "header.h"

double functionB(double x, double y, double z) {
    double result = fabs(x - y) * (sin(pow(z, 2)) + tan(z));

    return result;
}
