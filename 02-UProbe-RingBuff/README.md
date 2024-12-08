# UProbe Example



```shell
$ sudo ./bin/uprobe_ringbuff-userspace 
UProbe-Userspace module
BPF object loaded
UProbe attached
Press Ctrl+C to stop
PID: 125608 =>  invoked with args: 83, 86
PID: 125608 => test_return returned: 169
PID: 125608 =>  invoked with args: 15, 93
PID: 125608 => test_return returned: 108
PID: 125608 =>  invoked with args: 86, 92
PID: 125608 => test_return returned: 178
PID: 125608 =>  invoked with args: 21, 62
PID: 125608 => test_return returned: 83

       ### The monitored test program was terminated and restarted here 
PID: 125677 =>  invoked with args: 83, 86
PID: 125677 => test_return returned: 169
PID: 125677 =>  invoked with args: 15, 93
PID: 125677 => test_return returned: 108
PID: 125677 =>  invoked with args: 86, 92
PID: 125677 => test_return returned: 178
PID: 125677 =>  invoked with args: 21, 62
PID: 125677 => test_return returned: 83
PID: 125677 =>  invoked with args: 90, 59
PID: 125677 => test_return returned: 149
PID: 125677 =>  invoked with args: 26, 40
PID: 125677 => test_return returned: 66
       ### The monitored test program was terminated and restarted here 
PID: 125729 =>  invoked with args: 83, 86
PID: 125729 => test_return returned: 169
PID: 125729 =>  invoked with args: 15, 93
PID: 125729 => test_return returned: 108

```