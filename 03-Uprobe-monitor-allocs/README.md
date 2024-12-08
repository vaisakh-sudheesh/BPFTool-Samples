# UProbe Example: 03-Uprobe-monitor-allocs

This sample program demonstrates how to monitor `malloc` and `free` call issued from the library(`libscudo_library.so` - build from the SCUDO allocator code present in `tests/llvm-project-llvmorg-19.1.5/scudo-standalone`) and a test code (`tests/test_alloc.c`).

## Source organization

```shell
.
├── bpf
│   └── uprobe-alloc-monitor.bpf.c     ## BPF code - to build and generate skeleton  (Ring Buffer produce)
|                                      ## Monitors malloc and free calls from `libscudo_library` library
|
├── CMakeLists.txt                     ## Build rules
├── includes
│   └── common.h                       ## Common structure across both userspace and BPF code
├── README.md
└── src
    └── main-alloc-monitor.cpp         ## Userspace code that uses skeleton and runs it - dumps the monitoring output
```


## Demo

Test command execution issuing allocation/deallocation calls to be monitored:
```shell
### FIRST TEST CODE EXECUTION ###

vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
$ ctest 
Test project /home/vaisakhps/developer/eBPF/BPFTool-Samples/build
    Start 1: scudo_tests
1/1 Test #1: scudo_tests ......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec


### SECOND TEST CODE EXECUTION ###
vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
$ ctest --verbose
UpdateCTestConfiguration  from :/home/vaisakhps/developer/eBPF/BPFTool-Samples/build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/vaisakhps/developer/eBPF/BPFTool-Samples/build/DartConfiguration.tcl
Test project /home/vaisakhps/developer/eBPF/BPFTool-Samples/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: scudo_tests

1: Test command: /home/vaisakhps/developer/eBPF/BPFTool-Samples/build/bin/allocation_test
1: Working Directory: /home/vaisakhps/developer/eBPF/BPFTool-Samples/build/tests
1: Environment variables: 
1:  LD_PRELOAD=/home/vaisakhps/developer/eBPF/BPFTool-Samples/build/lib/libscudo_library.so
1: Test timeout computed to be: 10000000
1: Allocation test!
1: Time taken for 100 allocations: 0.000597 seconds
1/1 Test #1: scudo_tests ......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

Meantime, the uprobe based monitor is started which observes the allocation using `lib/libscudo_library.so` library.

```shell
vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
(Prev Cmd Exit - 0) Mon Dec 09 01:45:13 $ sudo ./bin/03-UProbe-Monitor-Allocs-userspace 
UProbe-Userspace module
BPF object loaded
UProbe attached
Press Ctrl+C to stop

### MONITORING OUTPUT FROM MONITORING PROCESS: FIRST TEST CODE EXECUTION ###
PID: 143260 => Allocation of size: 73728
PID: 143260 => Allocation of size: 4096
PID: 143260 => Allocation of size: 359
PID: 143260 => Freeing memory
PID: 143260 => Allocation of size: 966
PID: 143260 => Freeing memory
PID: 143260 => Allocation of size: 105
PID: 143260 => Freeing memory
PID: 143260 => Allocation of size: 115
PID: 143260 => Freeing memory
PID: 143260 => Allocation of size: 81
PID: 143260 => Freeing memory
PID: 143260 => Allocation of size: 255
PID: 143260 => Freeing memory
### .....
### .....

### MONITORING OUTPUT FROM MONITORING PROCESS: SECOND TEST CODE EXECUTION ###

PID: 143325 => Allocation of size: 73728
PID: 143325 => Allocation of size: 4096
PID: 143325 => Allocation of size: 359
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 966
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 105
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 115
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 81
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 255
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 74
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 236
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 809
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 205
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 186
PID: 143325 => Freeing memory
PID: 143325 => Allocation of size: 939
PID: 143325 => Freeing memory
### .....
### .....

```