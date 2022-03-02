cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

add_subdirectory(externals/Gaia_Archive_Tools)
add_subdirectory(externals/SH-Engine)

project(GaiaUniverseModel C)

add_library(gaia-universe-model
    GaiaUniverseModel/gaia-universe-model/src/gaiaUniverseModel.c
)
target_include_directories(gaia-universe-model PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/GaiaUniverseModel/gaia-universe-model/include
)
target_link_libraries(gaia-universe-model PUBLIC GaiaArchiveTools ShEngine)

add_executable(gaia-universe-model-simulation 
    GaiaUniverseModel/gaia-universe-model-simulation/src/main.c
)
target_link_libraries(gaia-universe-model-simulation PUBLIC gaia-universe-model)

set_target_properties(gaia-universe-model-simulation gaia-universe-model GaiaArchiveTools ShEngine ShVulkan PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)