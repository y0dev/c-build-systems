#include <stdio.h>
#include "file.h"
#include "arithmetic.h"

int main(int argc, char** argv)
{
    printf("Hello World!\n");
    testFun();
    printf("Static library says 3*3 is %d\n", multiply(3,3));

    return 0;
}
