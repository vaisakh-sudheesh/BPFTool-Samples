#include <iostream> 
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "uprobe-print-bpf.skel.h"

#include <unistd.h>

int main (int argc, char *argv[]) {
    std::cout << "UProbe-Userspace module" << std::endl;
    auto obj = uprobe_print_bpf();
    auto status = obj.open_and_load();
    if (status == nullptr) {
        std::cerr << "Failed to load BPF object: " << status << std::endl;
        return 1;
    }
    std::cout << "BPF object loaded" << std::endl;
    auto link_status = obj.attach(status);
    if (link_status != 0) {
        std::cerr << "Failed to attach UProbe: " << link_status << std::endl;
        return link_status;
    }
    std::cout << "UProbe attached" << std::endl;
    std::cout << "Press Ctrl+C to stop" << std::endl;
    while (1) {
        sleep(1);
    }

    return 0;
}