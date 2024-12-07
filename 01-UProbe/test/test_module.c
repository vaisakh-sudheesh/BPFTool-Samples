#include <stdio.h>

void test_function(void)
{
    printf("[test_function] Hello, world!\n");
}

int test_return (int a, int b) {
    printf("[test_return] a: %d, b: %d ==> ret = %d \n", a, b , a + b);
    return a + b;
}
