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
    printf("[test_executable_function] ret val = %d\n", a);
    return a;
}

int main () {
    printf("Hello, world - Test Executable!\n");
    while (1) {
        int random_a = rand() % 100;
        int random_b = rand() % 100;
        test_function();
        sleep(1);
        test_return(random_a, random_b);
        test_executable_function(random_a + 20 , random_b+13);
        sleep(1);
    }
    return 0;
}