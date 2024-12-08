set(TARGET_NAME "02-UProbe-RingBuff")

## Build the BPF module - sample 
bpf_module(${TARGET_NAME}-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-ringbuff.bpf.c" "uprobe-ringbuff-bpf.o" "uprobe-ringbuff-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(${TARGET_NAME}-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-ringbuff.cpp" ${TARGET_NAME}-bpf)
target_include_directories(${TARGET_NAME}-userspace PRIVATE ${CMAKE_CURRENT_LIST_DIR}/includes)
