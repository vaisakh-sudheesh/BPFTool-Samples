find_program(BPFTOOL_EXECUTABLE NAMES bpftool)
if(NOT BPFTOOL_EXECUTABLE)
    message(FATAL_ERROR "bpftool executable not found in PATH")
endif()


add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/vmlinux.h
    COMMAND ${BPFTOOL_EXECUTABLE} btf dump file /sys/kernel/btf/vmlinux format c > ${CMAKE_BINARY_DIR}/vmlinux.h
    DEPENDS ${BPFTOOL_EXECUTABLE}
    COMMENT "Generating vmlinux.h for BPF code compilation"
)

add_custom_target(generate_vmlinux_h ALL
    DEPENDS ${CMAKE_BINARY_DIR}/vmlinux.h
)