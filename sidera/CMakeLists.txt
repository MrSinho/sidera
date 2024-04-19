cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)



project(sidera C)



# YOU CAN MODIFY
set(SIDERA_VERSION pre-release)
add_compile_definitions(SIDERA_VERSION="${SIDERA_VERSION}")

set(SIDERA_ROOT_DIR      ${CMAKE_CURRENT_SOURCE_DIR})
set(SIDERA_REPO_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(SIDERA_BINARIES_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/bin)



# YOU CAN MODIFY
option(SIDERA_BINARY_TYPE     CACHE EXECUTABLE)
option(SH_ENGINE_ROOT_DIR     CACHE OFF)
option(SH_ENGINE_BINARIES_DIR CACHE OFF)



# YOU CAN MODIFY 
if (NOT SIDERA_BINARY_TYPE)
set(SIDERA_BINARY_TYPE "EXECUTABLE")
endif()

# DO NOT MODIFY!
if (NOT SH_ENGINE_ROOT_DIR)
message(FATAL_ERROR "sidera: missing SH_ENGINE_ROOT_DIR")
endif()

# DO NOT MODIFY!
if (NOT SH_ENGINE_BINARIES_DIR)
set(SH_ENGINE_BINARIES_DIR ${SH_ENGINE_ROOT_DIR}/bin)
endif()


message(STATUS "SIDERA_ROOT_DIR        : ${SIDERA_ROOT_DIR}")
message(STATUS "SIDERA_BINARIES_DIR    : ${SIDERA_BINARIES_DIR}")
message(STATUS "SIDERA_BINARY_TYPE     : ${SIDERA_BINARY_TYPE}")

message(STATUS "SH_ENGINE_ROOT_DIR     : ${SH_ENGINE_ROOT_DIR}")
message(STATUS "SH_ENGINE_BINARIES_DIR : ${SH_ENGINE_BINARIES_DIR}")



include(${SH_ENGINE_ROOT_DIR}/collection/collection.cmake)
include(${SH_ENGINE_ROOT_DIR}/docs/shengine-docs.cmake)

include(${SIDERA_REPO_ROOT_DIR}/docs/sidera-docs.cmake)
add_subdirectory(${SIDERA_REPO_ROOT_DIR}/externals/gaia-archive-tools _EXCLUDE_FROM_ALL_)



function(build_sidera)

build_shengine_collection()
build_shengine_docs()


if(${SIDERA_BINARY_TYPE} STREQUAL "STATIC")
add_library(sidera STATIC 
    ${SIDERA_ROOT_DIR}/src/sidera.c
    ${SIDERA_ROOT_DIR}/src/gaia-sim.c
    #src_files
)


elseif(${SIDERA_BINARY_TYPE} STREQUAL "SHARED")
add_library(sidera SHARED 
    ${SIDERA_ROOT_DIR}/src/sidera.c
    ${SIDERA_ROOT_DIR}/src/gaia-sim.c
    #src_files
)
target_compile_definitions(shengine PUBLIC 
    SH_APPLICATION_TARGET_TYPE_SHARED=1
)


elseif(${SIDERA_BINARY_TYPE} STREQUAL "EXECUTABLE")
add_executable(sidera  
    ${SIDERA_ROOT_DIR}/src/sidera.c
    ${SIDERA_ROOT_DIR}/src/gaia-sim.c
    #src_files
    ${SH_ENGINE_ROOT_DIR}/collection/sheditor/src/shEditor.c
)
target_include_directories(sidera PUBLIC 
    ${SH_ENGINE_ROOT_DIR}/collection/sheditor/include
)
target_compile_definitions(sidera PUBLIC 
    SH_APPLICATION_TARGET_TYPE_EXECUTABLE=1
)
endif()


target_include_directories(sidera PUBLIC 
    ${SIDERA_ROOT_DIR}/include
)

target_link_libraries(sidera PUBLIC
    shengine
    gaia-archive-tools
)

if (WIN32)
set_target_properties(sidera sheditor PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY      ${SIDERA_BINARIES_DIR}/windows
    RUNTIME_OUTPUT_DIRECTORY      ${SIDERA_BINARIES_DIR}/windows
    VS_DEBUGGER_WORKING_DIRECTORY ${SIDERA_BINARIES_DIR}/windows
)
else()
set_target_properties(sidera sheditor PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY      ${SIDERA_BINARIES_DIR}/linux 
    RUNTIME_OUTPUT_DIRECTORY      ${SIDERA_BINARIES_DIR}/linux
    VS_DEBUGGER_WORKING_DIRECTORY ${SIDERA_BINARIES_DIR}/linux
)
endif(WIN32)

set_shengine_collection_binaries()

endfunction()


function(sidera_main)
build_sidera()
build_sidera_docs()
endfunction()



sidera_main()
