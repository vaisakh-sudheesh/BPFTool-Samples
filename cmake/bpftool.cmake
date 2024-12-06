find_program(BPFTOOL_EXECUTABLE NAMES bpftool)
if(NOT BPFTOOL_EXECUTABLE)
    message(FATAL_ERROR "bpftool executable not found in PATH")
endif()

###############################################################################
### Generate vmlinux.h for BPF code compilation
###############################################################################
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/vmlinux.h
    COMMAND ${BPFTOOL_EXECUTABLE} btf dump file /sys/kernel/btf/vmlinux format c > ${CMAKE_BINARY_DIR}/vmlinux.h
    DEPENDS ${BPFTOOL_EXECUTABLE}
    COMMENT "Generating vmlinux.h for BPF code compilation"
)

add_custom_target(generate_vmlinux_h ALL
    DEPENDS ${CMAKE_BINARY_DIR}/vmlinux.h
)

###############################################################################
### Compile BPF code into object files
###############################################################################

function(build_bpf TARGET_NAME BPF_SOURCE BPF_OBJECT)
    add_custom_command(
        OUTPUT ${BPF_OBJECT}
        COMMAND ${CMAKE_C_COMPILER} -O2 -target bpf 
                                      -c ${BPF_SOURCE}
                                      -o ${BPF_OBJECT}
                                      -I${CMAKE_BINARY_DIR}
                                      -I/usr/src/linux-headers-6.8.0-48-generic/tools/bpf/resolve_btfids/libbpf/include/
        DEPENDS ${BPF_SOURCE} generate_vmlinux_h
        COMMENT "Compiling BPF code ${BPF_SOURCE} into ${BPF_OBJECT}"
    )

    add_custom_target(${TARGET_NAME} ALL
        DEPENDS ${BPF_OBJECT}
    )

endfunction(build_bpf)


###############################################################################
### Generate skeleton for BPF code
###############################################################################
function(generate_bpf_skeleton TARGET_NAME BPF_OBJECT BPF_SKELETON_HEADER)
    add_custom_target(bpf_skeleton_${TARGET_NAME} ALL
        COMMAND ${BPFTOOL_EXECUTABLE} gen skeleton ${BPF_OBJECT} > ${CMAKE_BINARY_DIR}/${BPF_SKELETON_HEADER}
        DEPENDS ${BPF_OBJECT}
        COMMENT "Generating skeleton for BPF code ${BPF_SOURCE}"
    )

endfunction(generate_bpf_skeleton)


###############################################################################
### Utility function to wrap up all the necessary bpf module tooling operations.
###############################################################################
function(bpf_module TARGET_NAME BPF_SOURCE BPF_OBJECT BPF_SKELETON)
    build_bpf(${TARGET_NAME} ${BPF_SOURCE} ${BPF_OBJECT})
    generate_bpf_skeleton(${TARGET_NAME} ${BPF_OBJECT} ${BPF_SKELETON})
endfunction(bpf_module)
