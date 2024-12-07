set(TARGET_NAME "01-UProbe")

## Build the BPF module - sample 
bpf_module(uprobe_print-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample-print.bpf.c" "uprobe-print-bpf.o" "uprobe-print-bpf.skel.h")
bpf_userspace_module(uprobe_print-userspace "${CMAKE_CURRENT_LIST_DIR}/src/main-print.cpp" uprobe_print-bpf)


### Compile test module
add_library(test_library SHARED "${CMAKE_CURRENT_LIST_DIR}/test/test_module.c")
add_executable(test_executable "${CMAKE_CURRENT_LIST_DIR}/test/test_executable.c")
target_link_libraries(test_executable test_library)

