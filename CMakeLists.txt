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

# Find the bpftool executable & setup the relevant build rules
include(bpftool)

enable_testing()

# Add the subdirectories for each sample
add_subdirectory(01-UProbe-Print)
add_subdirectory(02-UProbe-RingBuff)
add_subdirectory(03-Uprobe-monitor-allocs)
add_subdirectory(tests)


