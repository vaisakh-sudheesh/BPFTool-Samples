set(TARGET_NAME "01-UProbe-Print")

## Build the BPF module - sample 
bpf_module(uprobe_print-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-print.bpf.c" "uprobe-print-bpf.o" "uprobe-print-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(uprobe_print-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-print.cpp" uprobe_print-bpf)


