#include <iostream>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "uprobe-ringbuff-bpf.skel.h"
#include "common.h"

#include <unistd.h>

int handle_event(void *ctx, void *data, size_t size) {
    auto event = static_cast<struct event *>(data);
    if (event->type == EVENT_TYPE_EXIT) {
        std::cout << "PID: " << event->pid << " => " << event->func_name << " returned: " << event->ret << std::endl;
    } else {
        std::cout << "PID: " << event->pid << " => " << event->func_name << " invoked with args: " << event->arg1 << ", " << event->arg2 << std::endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    std::cout << "UProbe-Userspace module" << std::endl;
    auto obj = uprobe_ringbuff_bpf__open();
    if (!obj) {
        std::cerr << "Failed to open BPF object" << std::endl;
        return 1;
    }
    auto status = uprobe_ringbuff_bpf__load(obj);
    if (status) {
        std::cerr << "Failed to load BPF object: " << status << std::endl;
        return 1;
    }
    std::cout << "BPF object loaded" << std::endl;
    auto link_status = uprobe_ringbuff_bpf__attach(obj);
    if (link_status != 0) {
        std::cerr << "Failed to attach UProbe" << std::endl;
        return 1;
    }
    std::cout << "UProbe attached" << std::endl;

    int ringbuf_fd = bpf_map__fd(obj->maps.events);
    struct ring_buffer *rb = ring_buffer__new(ringbuf_fd, handle_event, nullptr, nullptr);
    if (!rb) {
        std::cerr << "Failed to create ring buffer" << std::endl;
        return 1;
    }

    std::cout << "Press Ctrl+C to stop" << std::endl;
    while (true) {
        int err = ring_buffer__poll(rb, 100 /* timeout, ms */);
        if (err < 0) {
            std::cerr << "Error polling ring buffer: " << err << std::endl;
            break;
        }
    }

    ring_buffer__free(rb);
    uprobe_ringbuff_bpf__destroy(obj);

    return 0;
}