cmake_minimum_required(VERSION 3.13)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)



function(build_sidera_docs)



if (NOT DEFINED SIDERA_BINARIES_DIR)
message(FATAL_ERROR "sidera cmake error: missing SIDERA_BINARIES_DIR")
endif()

if (NOT DEFINED SIDERA_REPO_ROOT_DIR)
message(FATAL_ERROR "sidera cmake error: missing SIDERA_REPO_ROOT_DIR")
endif()




find_package(Doxygen)


if (DOXYGEN_FOUND)

    set(SIDERA_DOXYFILESRC ${SIDERA_REPO_ROOT_DIR}/docs/Doxyfile.in)
    set(SIDERA_DOXYFILEDST ${SIDERA_REPO_ROOT_DIR}/docs/Doxyfile)

    message(STATUS "Configuring " ${SIDERA_DOXYFILEDST} " from " ${SIDERA_DOXYFILESRC})

    configure_file(
        ${SIDERA_DOXYFILESRC} 
        ${SIDERA_DOXYFILEDST}
    )

    message(STATUS "Creating custom docs command: " ${DOXYGEN_EXECUTABLE} " " ${SIDERA_DOXYFILEDST})

    add_custom_target(docs-sidera
        COMMAND ${DOXYGEN_EXECUTABLE} ${SIDERA_DOXYFILEDST}
        WORKING_DIRECTORY ${SIDERA_REPO_ROOT_DIR}
        COMMENT "Generating HTML documentation"
        VERBATIM
    )

endif(DOXYGEN_FOUND)

endfunction()