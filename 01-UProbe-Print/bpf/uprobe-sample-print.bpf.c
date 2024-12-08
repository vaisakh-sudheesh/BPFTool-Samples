#define __TARGET_ARCH_x86
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include "build_info.h"


SEC("uprobe/"BUILD_DIR"/lib/libtest_library.so:test_return")
int BPF_UPROBE(printargs, const int arg1, const  int arg2 )
{
	u32 pid;
	pid = bpf_get_current_pid_tgid() >> 32;
	bpf_printk("PID %d => test_return invoked with args: %d, %d\n", pid, arg1 , arg2);
	return 0;
}

SEC("uretprobe/"BUILD_DIR"/lib/libtest_library.so:test_return")
int BPF_URETPROBE(printret, const int ret)
{
	u32 pid;
	pid = bpf_get_current_pid_tgid() >> 32;
	bpf_printk("PID %d => test_return returned with %d\n", pid, ret);
	return 0;
}

char LICENSE[] SEC("license") = "GPL";