set (AOSP_ROOT "/home/vaisakhps/developer/Android" CACHE STRING "Path to the AOSP root directory")

add_custom_target(build_aosp_libs
        WORKING_DIRECTORY ${AOSP_ROOT}
        COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/deps/bpftool-android/android-bpftool-build.sh ${AOSP_ROOT} ${CMAKE_CURRENT_SOURCE_DIR}/deps/bpftool-android/
    )