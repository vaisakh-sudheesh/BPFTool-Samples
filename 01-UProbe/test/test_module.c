#include <stdio.h>

void test_function(void)
{
    printf("Hello, world!\n");
}

int test_return (int a, int b) {
    printf("a: %d, b: %d\n", a, b);
    return a + b;
}
