#include "arithmetic.h"
#include "debug.h"

int add(int a, int b) 
{
    print_debug("Adding numbers");
    return a + b;
}

int subtract(int a, int b) 
{
    return a - b;
}

int multiply(int a, int b) 
{
    return a * b;
}

int divide(int a, int b) 

{
    if (b != 0)
        return a / b;
    else
        return 0; // Return 0 for divide by zero
}