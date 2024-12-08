#include "build_info.h"
#include "vmlinux.h"
#include "common.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>


struct {
	__uint(type, BPF_MAP_TYPE_RINGBUF);
	__uint(max_entries, 1 << 24);
} events SEC(".maps");

SEC("uprobe/"BUILD_DIR"/lib/libscudo_library.so:malloc")
int BPF_UPROBE(malloccall, const int arg1)
{
	struct event *e;
	u32 pid = bpf_get_current_pid_tgid() >> 32;

	e = bpf_ringbuf_reserve(&events, sizeof(*e), 0);
	if (!e)
		return 0;
	e->type = EVENT_TYPE_ALLOCATION;
	e->pid = pid;
	e->size = arg1;

	bpf_ringbuf_submit(e, 0);
	return 0;
}

SEC("uprobe/"BUILD_DIR"/lib/libscudo_library.so:free")
int BPF_UPROBE(freecall)
{
	struct event *e;
	u32 pid = bpf_get_current_pid_tgid() >> 32;

	e = bpf_ringbuf_reserve(&events, sizeof(*e), 0);
	if (!e)
		return 0;
	e->type = EVENT_TYPE_FREE;
	e->pid = pid;

	bpf_ringbuf_submit(e, 0);
	return 0;
}



char LICENSE[] SEC("license") = "GPL";