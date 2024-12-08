set(TARGET_NAME "03-UProbe-Monitor-Allocs")

## Build the BPF module - sample 
bpf_module(uprobe_alloc-monitor-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-alloc-monitor.bpf.c" "uprobe-alloc-monitor-bpf.o" "uprobe-alloc-monitor-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(uprobe_alloc-monitor-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-alloc-monitor.cpp" uprobe_alloc-monitor-bpf)
target_include_directories(uprobe_alloc-monitor-userspace PRIVATE ${CMAKE_CURRENT_LIST_DIR}/includes)
