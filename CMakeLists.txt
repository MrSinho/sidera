cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

add_subdirectory(externals/Gaia_Archive_Tools)
add_subdirectory(externals/glfw)
add_subdirectory(externals/cglm)
add_subdirectory(externals/ShVulkan)

project(Gaia_Universe_Model C)

add_executable(GaiaUniverseModel GaiaUniverseModel/src/main.c)
target_link_libraries(GaiaUniverseModel PUBLIC ShVulkan glfw GaiaArchiveTools cglm)

set_target_properties(GaiaUniverseModel ShVulkan glfw PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)