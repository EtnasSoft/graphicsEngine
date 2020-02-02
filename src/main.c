#include <stdio.h>
#include "ProductionCode.h"
//#include "ProductionCode2.h"

int main(void) {
    int result = FunctionWhichReturnsLocalVariable();

    printf("My var is %i: ", result);

    return 0;
}