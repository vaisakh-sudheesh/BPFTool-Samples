#define __TARGET_ARCH_x86
#include "vmlinux.h"
#include "common.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "build_info.h"

struct {
	__uint(type, BPF_MAP_TYPE_RINGBUF);
	__uint(max_entries, 1 << 24);
} events SEC(".maps");

SEC("uprobe/"BUILD_DIR"/lib/libtest_library.so:test_return")
int BPF_UPROBE(printargs, const int arg1, const int arg2)
{
	struct event *e;
	u32 pid = bpf_get_current_pid_tgid() >> 32;

	e = bpf_ringbuf_reserve(&events, sizeof(*e), 0);
	if (!e)
		return 0;
	e->type = EVENT_TYPE_ENTER;
	e->pid = pid;
	e->arg1 = arg1;
	e->arg2 = arg2;

	bpf_ringbuf_submit(e, 0);
	return 0;
}

SEC("uretprobe/"BUILD_DIR"/lib/libtest_library.so:test_return")
int BPF_URETPROBE(printret, const int ret)
{
	struct event *e;
	u32 pid = bpf_get_current_pid_tgid() >> 32;

	e = bpf_ringbuf_reserve(&events, sizeof(*e), 0);
	if (!e)
		return 0;

	e->pid = pid;
	e->type = EVENT_TYPE_EXIT;
	e->ret = ret;
	__builtin_memcpy(e->func_name, "test_return", sizeof("test_return"));

	bpf_ringbuf_submit(e, 0);
	return 0;
}

char LICENSE[] SEC("license") = "GPL";