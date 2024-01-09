#include <stdio.h>

int foo1();

int foo2();

int main()
{
    int result = foo1() + foo2();
    printf("hello world %d\n", result);
    return 0;
}