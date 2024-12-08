set(TARGET_NAME "01-UProbe")

## Build the BPF module - sample 
bpf_module(uprobe_print-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-print.bpf.c" "uprobe-print-bpf.o" "uprobe-print-bpf.skel.h"${CMAKE_CURRENT_LIST_DIR}/includes)
bpf_userspace_module(uprobe_print-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-print.cpp" uprobe_print-bpf)

bpf_module(uprobe_ringbuff-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-ringbuff.bpf.c" "uprobe-ringbuff-bpf.o" "uprobe-ringbuff-bpf.skel.h" ${CMAKE_CURRENT_LIST_DIR}/includes)

bpf_userspace_module(uprobe_ringbuff-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-ringbuff.cpp" uprobe_ringbuff-bpf)
target_include_directories(uprobe_ringbuff-userspace PRIVATE ${CMAKE_CURRENT_LIST_DIR}/includes)


### Compile test module
add_library(test_library SHARED "${CMAKE_CURRENT_LIST_DIR}/test/test_module.c")
add_executable(test_executable "${CMAKE_CURRENT_LIST_DIR}/test/test_executable.c")
target_link_libraries(test_executable test_library)

