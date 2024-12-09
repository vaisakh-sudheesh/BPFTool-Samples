cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project (BPFTool-Samples)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable all warnings and colorized output
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fdiagnostics-color=always")

# Set the build directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

include(utils)


# Find the bpftool executable & setup the relevant build rules
if (NOT CMAKE_TOOLCHAIN_FILE)
    generate_build_dir_header(${CMAKE_BINARY_DIR}/build_info.h)
    ## Building for the host
    message(STATUS "Building for the host")
    include(bpftool)
else()
    generate_build_dir_header_android(${CMAKE_BINARY_DIR}/build_info.h)
    ## Trying to build for Android
    message(STATUS "Cross-compiling for Android")
    include (install)
    include (aosp)
    include(android-bpftools)    
endif(NOT CMAKE_TOOLCHAIN_FILE)

enable_testing()

# Add the subdirectories for each sample
add_subdirectory(01-UProbe-Print)
add_subdirectory(02-UProbe-RingBuff)
add_subdirectory(03-Uprobe-monitor-allocs)
add_subdirectory(tests)


