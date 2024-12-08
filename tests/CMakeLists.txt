### Compile test module
add_library(test_library SHARED "${CMAKE_CURRENT_LIST_DIR}/test_module.c")
add_executable(test_executable "${CMAKE_CURRENT_LIST_DIR}/test_executable.c")
target_link_libraries(test_executable test_library)
