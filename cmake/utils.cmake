# utils.cmake

# Function to generate a header file with the build directory
function(generate_build_dir_header output_file)
    file(WRITE ${output_file} "#ifndef BUILD_DIR_H\n")
    file(APPEND ${output_file} "#define BUILD_DIR_H\n\n")
    file(APPEND ${output_file} "#define BUILD_DIR \"${CMAKE_BINARY_DIR}\"\n\n")
    file(APPEND ${output_file} "#endif // BUILD_DIR_H\n")
endfunction()


function(generate_build_dir_header_android output_file)
    file(WRITE ${output_file} "#ifndef BUILD_DIR_H\n")
    file(APPEND ${output_file} "#define BUILD_DIR_H\n\n")
    file(APPEND ${output_file} "#define BUILD_DIR \"${CMAKE_BINARY_DIR}\"\n\n")
    file(APPEND ${output_file} "#define __TARGET_ARCH_arm64\n\n")
    file(APPEND ${output_file} "#endif // BUILD_DIR_H\n")
endfunction()
