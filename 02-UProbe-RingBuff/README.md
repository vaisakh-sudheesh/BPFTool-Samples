# UProbe Example: 02-UProbe-RingBuff

This example module focuses on demonstrating usage of `uprobe` to monitor functions entry/exit calls within the test code (`tests/test_executable.c` and `tests/test_module.c`). Unlike `01-UProbe-Print`, this implementation makes use of eBPF's perf ring buffer feature rather than `bpfprintk`, wherein the user-space program can be consumer of the data pumped by the BPF code which will be tbe producer


## Source organization

```shell
.
├── bpf
│   └── uprobe-sample-ringbuff.bpf.c   ## BPF code - to build and generate skeleton  (Ring Buffer produce)
├── CMakeLists.txt                     ## Build rules
├── includes
│   └── common.h                       ## Common structure across both userspace and BPF code
├── README.md
└── src
    └── main-ringbuff.cpp              ## Userspace code that uses skeleton and runs it (RingBuffer Consumer)
```

## Demo

The user-space monitoring executable is started with `sudo` permission , which is listed later on, while the test-code is executed.

Test-code execution:
```shell
vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
$ ./bin/test_executable 
Hello, world - Test Executable!
[test_function] Hello, world!
[test_return] a: 83, b: 86 ==> ret = 169 
[test_executable_function] Hello, world - Test Executable!
[test_executable_function] a = 103, b = 99
[test_executable_function] random = 77
[test_executable_function] ret val = 7726
[test_function] Hello, world!
[test_return] a: 15, b: 93 ==> ret = 108 
[test_executable_function] Hello, world - Test Executable!
[test_executable_function] a = 35, b = 106
[test_executable_function] random = 35
[test_executable_function] ret val = 3745
[test_function] Hello, world!
[test_return] a: 86, b: 92 ==> ret = 178 
[test_executable_function] Hello, world - Test Executable!
[test_executable_function] a = 106, b = 105
[test_executable_function] random = 49
[test_executable_function] ret val = 5251
[test_function] Hello, world!
[test_return] a: 21, b: 62 ==> ret = 83 
[test_executable_function] Hello, world - Test Executable!
[test_executable_function] a = 41, b = 75
[test_executable_function] random = 27
[test_executable_function] ret val = 2066
^C


vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
$ ./bin/test_executable 
Hello, world - Test Executable!
[test_function] Hello, world!
[test_return] a: 83, b: 86 ==> ret = 169 
[test_executable_function] Hello, world - Test Executable!
[test_executable_function] a = 103, b = 99
[test_executable_function] random = 77
[test_executable_function] ret val = 7726
[test_function] Hello, world!
[test_return] a: 15, b: 93 ==> ret = 108 
[test_executable_function] Hello, world - Test Executable!
[test_executable_function] a = 35, b = 106
[test_executable_function] random = 35
[test_executable_function] ret val = 3745
[test_function] Hello, world!
```

User-space monitor execution :
```shell
$ sudo ./bin/02-UProbe-RingBuff-userspace 
UProbe-Userspace module
BPF object loaded
UProbe attached
Press Ctrl+C to stop
PID: 143027 =>  invoked with args: 83, 86
PID: 143027 => test_return returned: 169
PID: 143027 =>  invoked with args: 15, 93
PID: 143027 => test_return returned: 108
PID: 143027 =>  invoked with args: 86, 92
PID: 143027 => test_return returned: 178
PID: 143027 =>  invoked with args: 21, 62
PID: 143027 => test_return returned: 83

       ### The monitored test program was terminated and restarted here 
PID: 143083 =>  invoked with args: 83, 86
PID: 143083 => test_return returned: 169
PID: 143083 =>  invoked with args: 15, 93
PID: 143083 => test_return returned: 108

```
