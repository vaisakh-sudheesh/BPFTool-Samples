#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern void test_function(void);
extern int test_return(int a, int b);

int test_executable_function(int a, int b) {
    printf("[test_executable_function] Hello, world - Test Executable!\n");
    printf("[test_executable_function] a = %d, b = %d\n", a, b);
    int random = rand() % 100;
    printf("[test_executable_function] random = %d\n", random);
    a += b * random;
    printf("[test_executable_function] a = %d\n", a);
    return a;
}

int main () {
    printf("Hello, world - Test Executable!\n");
    while (1) {
        test_function();
        sleep(1);
        test_return(1, 2);
        test_executable_function(1, 2);
        sleep(1);
    }
    return 0;
}