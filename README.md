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

The development workflow involving bpftool is demonstrated in the diagram below:
![BPFTool development workflow](/docs/BPFTool.drawio.png)

- The developed BPF code is compiled using `clang` compiler using in to an object file.
- The `bpftool` can consume the BPF object file generated above, to obtain a skeleton header file using `bpftool gen skeleton` command(refer `cmake\bpftools.cmake` for more information)
   - This skeleton header file contains all necessary functions and structure to perform key BPF operations such as load, attach, detach, destory etc.
   - In case of this project build configuration, these headers will be available in the build-directory.
- The user-space program which intends to perform the observability operation, may include this skeleton header file to load and manage the BPF code.
- The compiled executable of above mentioned user-space program can be executed with `sudo` permission to perform the intended observability operation.

The sub-directories contain examples of various observability implementations for your reference.

## Pre-requisites (for PC based development)

Install clang:

```shell 
$ cd ~/Downloads
$ wget https://apt.llvm.org/llvm.sh
$ chmod +x llvm.sh
$ sudo ./llvm.sh 19
```

Install misc & BPF related dependencies:

```shell
$ sudo apt install linux-tools-common linux-tools-generic linux-tools-$(uname -r) bpftrace cmake
```

## Pre-requisites (for Android based development)

- Install following  Android NDK version `27.x` or above
- Install android platform tools (for ADB). You may do so by downloading it from Google Android website or via apt (`sudo apt install android-platform-tools-base`)
- Misc. dependencies: `sudo apt install cmake`

## Build commands

### Linux Target: Commandline build

Build commands for PC:

```shell
$ git clone https://github.com/vaisakh-sudheesh/BPFTool-Samples.git
$ cd BPFTool-Samples
$ mkdir build-dir && cd build-dir
$ cmake -S .. -DCMAKE_C_COMPILER=clang-19 -DCMAKE_CXX_COMPILER=clang++-19
$ cmake --build .
```

### Android  Target: Commandline build
In case of Android, 
- the configuration step need to be changed w.r.t to the above command listing.
- Make sure ADB is running in root mode - this is required as `BPFTool` need to be pushed to device in `/data/local/tmp` path to generate skeleton.

To build for an Android device:
```shell
$ adb root
$ cmake -S .. -DCMAKE_TOOLCHAIN_FILE=$NDK_PATH/build/cmake/android.toolchain.cmake  -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-34
$ cmake --build . 

## Additional command to push the result files to device
$ cmake --build . --target install_files
```

Once this is done, the output files will be available in `build-dir/bin` and `build-dir/lib` directories as listed below:

```shell
$ ls -lah bin/ lib/
bin/:
total 5.0M
drwxrwxr-x 2 vaisakhps vaisakhps 4.0K Dec  9 02:20 .
drwxrwxr-x 9 vaisakhps vaisakhps 4.0K Dec  9 02:20 ..
-rwxrwxr-x 1 vaisakhps vaisakhps 1.7M Dec  9 02:20 01-UProbe-Print-userspace
-rwxrwxr-x 1 vaisakhps vaisakhps 1.7M Dec  9 02:20 02-UProbe-RingBuff-userspace
-rwxrwxr-x 1 vaisakhps vaisakhps 1.7M Dec  9 02:20 03-UProbe-Monitor-Allocs-userspace
-rwxrwxr-x 1 vaisakhps vaisakhps  16K Dec  9 02:20 allocation_test
-rwxrwxr-x 1 vaisakhps vaisakhps  16K Dec  9 02:20 test_executable

lib/:
total 336K
drwxrwxr-x 2 vaisakhps vaisakhps 4.0K Dec  9 02:20 .
drwxrwxr-x 9 vaisakhps vaisakhps 4.0K Dec  9 02:20 ..
-rwxrwxr-x 1 vaisakhps vaisakhps 309K Dec  9 02:20 libscudo_library.so
-rwxrwxr-x 1 vaisakhps vaisakhps  16K Dec  9 02:20 libtest_library.so

```

Details about each of the examples are provided in respective README.md in the directories.

In case of VS Code based build, a preset file `CMakePresets.json` is provided to switch between Android and PC/Clang.
You select/switch using the "CMake: Select Configure Preset" option.
![VS Code - Cmake preset](/docs/vscode-presets.png)

You can choose the appropriate preset followed by `CMake: Configure` and `CMake: Build` actions to build the targets.
![VS Code - Cmake preset](/docs/vscode-preset-listing.png)

## References

[1] https://docs.ebpf.io/linux/concepts/

[2] https://manpages.ubuntu.com/manpages/jammy/man8/bpftool-prog.8.html

[3] https://qmonnet.github.io/whirl-offload/2021/09/23/bpftool-features-thread/

[4] https://nakryiko.com/categories/bpf/

[5] https://eunomia.dev/en/tutorials/0-introduce/

[6] https://github.com/eunomia-bpf/bpf-developer-tutorial/tree/main







