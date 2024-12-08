# UProbe Example

Test command execution issuing allocation/deallocation calls to be monitored:
```shell
vaisakhps @ vaisakh-ps-ROG-Strix-SCAR-16-G634JYR - [~/developer/eBPF/BPFTool-Samples/build]
(Prev Cmd Exit - 0) Mon Dec 09 01:19:15 $ ctest --verbose
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
1: Time taken for 100 allocations: 0.000843 seconds
1/1 Test #1: scudo_tests ......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec

```

Meantime, the uprobe based monitor is started which observes the allocation using `lib/libscudo_library.so` library.

```shell
$ sudo ./bin/uprobe_alloc-monitor-userspace 
UProbe-Userspace module
BPF object loaded
UProbe attached
Press Ctrl+C to stop
PID: 139254 => Allocation of size: 73728
PID: 139254 => Allocation of size: 4096
PID: 139254 => Allocation of size: 359
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 966
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 105
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 115
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 81
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 255
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 74
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 236
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 809
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 205
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 186
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 939
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 498
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 763
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 483
PID: 139254 => Freeing memory
PID: 139254 => Allocation of size: 326
PID: 139254 => Freeing memory
```