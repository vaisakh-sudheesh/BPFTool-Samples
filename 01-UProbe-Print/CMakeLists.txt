set(TARGET_NAME "01-UProbe-Print")

## Build the BPF module - sample 
bpf_module(${TARGET_NAME}-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-print.bpf.c" "uprobe-print-bpf.o" "uprobe-print-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(${TARGET_NAME}-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-print.cpp" ${TARGET_NAME}-bpf)


