### Compile test module
add_library(test_library SHARED "${CMAKE_CURRENT_LIST_DIR}/test_module.c")
add_executable(test_executable "${CMAKE_CURRENT_LIST_DIR}/test_executable.c")
target_link_libraries(test_executable test_library)


### Build reference: https://llvm.org/docs/ScudoHardenedAllocator.html#id9
# Add all cpp files in the subdirectory llvm-project-llvmorg-19.1.5/scudo-standalone
file(GLOB SCUDO_SOURCES "${CMAKE_CURRENT_LIST_DIR}/llvm-project-llvmorg-19.1.5/scudo-standalone/*.cpp")

# Create a library from the collected source files
add_library(scudo_library SHARED ${SCUDO_SOURCES})
target_include_directories(scudo_library PRIVATE "${CMAKE_CURRENT_LIST_DIR}/llvm-project-llvmorg-19.1.5/scudo-standalone/include")

if (CMAKE_TOOLCHAIN_FILE)
    # Install the library to the target directory - Android's case
    install_target_library(scudo_library)
endif(CMAKE_TOOLCHAIN_FILE)

# Add the executable
add_executable(allocation_test "${CMAKE_CURRENT_LIST_DIR}/test_alloc.c")
add_dependencies(allocation_test scudo_library)

enable_testing()
add_test(
    NAME scudo_tests
    COMMAND allocation_test
)
set_property(TEST scudo_tests PROPERTY ENVIRONMENT "LD_PRELOAD=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libscudo_library.so")