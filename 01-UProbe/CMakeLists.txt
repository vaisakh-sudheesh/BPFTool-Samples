set(TARGET_NAME "01-UProbe")

bpf_module(uprobe-bpf "${CMAKE_CURRENT_LIST_DIR}/bpf/uprobe-sample.bpf.c" "uprobe-bpf.o" "uprobe-bpf.skel.h")