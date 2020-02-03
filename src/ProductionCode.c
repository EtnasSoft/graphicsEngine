#include "ProductionCode.h"

int Counter = 10;

int FunctionWhichReturnsLocalVariable(void) {
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 80;
    int z = a + b + c + d;

    return z;
}
