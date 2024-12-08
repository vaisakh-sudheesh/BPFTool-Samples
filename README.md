# eBPF/BPFTool Samples

## Concept

## Checking if the current platform supports eBPF

## Sample code

Sample test code with a shared library `test_module.c` (refer `test` directory for the source files):

```c
#include <stdio.h>

void test_function(void)
{
    printf("Hello, world!\n");
}

int test_return (int a, int b) {
    printf("a: %d, b: %d\n", a, b);
    return a + b;
}
```

Sample test code executable `test_executable.c` which loads also the above mentioned module :

```c
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
```

Now, BPF can be utilized to monitor invocation of functions such as `test_executable_function`. This can be demonstrated with `bpftrace`, while the test program is executing:

```shell
$ sudo bpftrace -e 'uprobe:/home/vaisakhps/developer/eBPF/BPFTool-Samples/build/bin/test_executable:test_executable_function { printf("test_executable_function called by PID %d\n", pid); }'
Attaching 1 probe...
test_executable_function called by PID 9854
test_executable_function called by PID 9854
test_executable_function called by PID 9854
```

As you can see it is able to print the instances where in the said function is executed.

Now, lets see if the same works for functions within a shared library, which with appropriate modifications it is working:

```shell
$ sudo bpftrace -e 'uprobe:/home/vaisakhps/developer/eBPF/BPFTool-Samples/build/lib/libtest_library.so:test_function { printf("test_function called by PID %d\n", pid); }'
Attaching 1 probe...
test_function called by PID 11505
test_function called by PID 11505
test_function called by PID 11505
^C

```

Bpftrace proves whether indeed a uprobe is working.

## Uprobe with BPFTool

In order for it to be more flexible and programmer friendly, `bpftool` lets us compile wrapper functions in to a header file which can be included in to test/monitoring program.


## References

[1] https://docs.ebpf.io/linux/concepts/

[2] https://manpages.ubuntu.com/manpages/jammy/man8/bpftool-prog.8.html

[3] https://qmonnet.github.io/whirl-offload/2021/09/23/bpftool-features-thread/

[4] https://nakryiko.com/categories/bpf/

[5] https://eunomia.dev/en/tutorials/0-introduce/

[6] https://github.com/eunomia-bpf/bpf-developer-tutorial/tree/main







