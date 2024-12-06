#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

pid_t my_pid = 0;
int test1_result = 0;

SEC("uprobe/./liburandom_read.so:urandlib_api_sameoffset")
int BPF_UPROBE(test1)
{
	pid_t pid = bpf_get_current_pid_tgid() >> 32;

	if (pid != my_pid)
		return 0;

	test1_result = 1;
	return 0;
}