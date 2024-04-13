cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

add_subdirectory(external/gaia-archive-tools)
add_subdirectory(external/shengine)

project(gaia-universe-model C)



function(build_universe_model)
add_library(gaia-universe-model
    gaia-universe-model/gaia-universe-model/src/gaiaUniverseModel.c
)
target_include_directories(gaia-universe-model PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/gaia-universe-model/gaia-universe-model/include
)
target_link_libraries(gaia-universe-model PUBLIC gaia-archive-tools shengine)

add_executable(gaia-universe-model-simulation 
    gaia-universe-model/gaia-universe-model-simulation/src/main.c
)
target_link_libraries(gaia-universe-model-simulation PUBLIC gaia-universe-model)

set_target_properties(gaia-universe-model-simulation 
    gaia-universe-model 
    gaia-archive-tools 
    shengine 
    shvulkan 
    
    PROPERTIES
    
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
endfunction()


function(main)
build_universe_model()
endfunction()



main()