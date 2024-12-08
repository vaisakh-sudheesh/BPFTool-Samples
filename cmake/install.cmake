add_custom_target(install_files)

function(install_target tgtname)
    add_custom_target(install_${tgtname}
        COMMAND adb push ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${tgtname} /data/local/tmp/${tgtname}
        COMMAND adb shell chmod +x /data/local/tmp/${tgtname}
        DEPENDS ${tgtname}
        COMMENT "Installing ${tgtname}"
    )
    add_dependencies(install_files install_${tgtname})
endfunction(install_target)

function(install_target_library tgtname)
    add_custom_target(install_${tgtname}
        COMMAND adb push ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${tgtname}.so /data/local/tmp/lib${tgtname}.so
        COMMAND adb shell chmod +x /data/local/tmp/lib${tgtname}.so
        DEPENDS ${tgtname}
        COMMENT "Installing library ${tgtname}"
    )
    add_dependencies(install_files install_${tgtname})
endfunction(install_target_library)