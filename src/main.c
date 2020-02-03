#include <stdio.h>
#include "ProductionCode.h"
//#include "ProductionCode2.h"

int main(void) {
    int a = 10,
        b = 20;

    int result = sum(a, b);

    printf("My var is %i: ", result);

    return 0;
}