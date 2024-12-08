# UProbe Example: 01-UProbe-Print

This example module focuses on demonstrating usage of `uprobe` to monitor functions entry/exit calls within the test code (`tests/test_executable.c` and `tests/test_module.c`).

Since the output of the program utilizes `bpf_printk` function on obtaining the uprobe function's entry/exit events, the output will be shown in `/sys/kernel/debug/tracing/trace_pipe` file.

## Source organization

```shell
.
├── bpf
│   └── uprobe-sample-print.bpf.c    ## BPF code - to build and generate skeleton 
├── CMakeLists.txt                   ## Build rules
├── README.md
└── src
    └── main-print.cpp               ## Userspace code that uses skeleton and runs it
```

## Demo

Executing the user-space process that loads the BPF module:
```shell
vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
$ sudo ./bin/01-UProbe-Print-userspace 
UProbe-Userspace module
BPF object loaded
UProbe attached
Press Ctrl+C to stop
```

Run the test code:
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
```

Observe the logs in `/sys/kernel/debug/tracing/trace_pipe`:
```shell
root@vaisakh-ps-ROG-Strix-SCAR-16-G634JYR:/sys/kernel/debug/tracing# cat trace_pipe 
 test_executable-142857  [031] ...11 129059.708182: bpf_trace_printk: PID 142857 => test_return invoked with args: 83, 86

 test_executable-142857  [031] ...11 129059.708236: bpf_trace_printk: PID 142857 => test_return returned with 169

 test_executable-142857  [031] ...11 129061.708966: bpf_trace_printk: PID 142857 => test_return invoked with args: 15, 93

 test_executable-142857  [031] ...11 129061.709026: bpf_trace_printk: PID 142857 => test_return returned with 108

```