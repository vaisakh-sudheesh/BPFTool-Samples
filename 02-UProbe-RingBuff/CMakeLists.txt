set(TARGET_NAME "02-UProbe-RingBuff")

## Build the BPF module - sample 
bpf_module(uprobe_ringbuff-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-ringbuff.bpf.c" "uprobe-ringbuff-bpf.o" "uprobe-ringbuff-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(uprobe_ringbuff-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-ringbuff.cpp" uprobe_ringbuff-bpf)
target_include_directories(uprobe_ringbuff-userspace PRIVATE ${CMAKE_CURRENT_LIST_DIR}/includes)
