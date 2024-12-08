set(TARGET_NAME "03-UProbe-Monitor-Allocs")

## Build the BPF module - sample 
bpf_module(${TARGET_NAME}-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-alloc-monitor.bpf.c" "uprobe-alloc-monitor-bpf.o" "uprobe-alloc-monitor-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(${TARGET_NAME}-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-alloc-monitor.cpp" ${TARGET_NAME}-bpf)
target_include_directories(${TARGET_NAME}-userspace PRIVATE ${CMAKE_CURRENT_LIST_DIR}/includes)
