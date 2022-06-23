cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

	add_subdirectory(../external/gaia-archive-tools [EXCLUDE_FROM_ALL])


option(SH_SIMULATION_NAME CACHE emptytarget)
project(${SH_SIMULATION_NAME})

option(SH_SIMULATION_BINARY_TYPE CACHE "EXECUTABLE")
if("${SH_SIMULATION_BINARY_TYPE}" STREQUAL "STATIC")
    add_library(${SH_SIMULATION_NAME} STATIC 
    	C:/Users/sino3/Desktop/GitHub/Gaia_Universe_Model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-universe-model.c
C:/Users/sino3/Desktop/GitHub/Gaia_Universe_Model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-sim.c

)
elseif("${SH_SIMULATION_BINARY_TYPE}" STREQUAL "SHARED")
    add_library(${SH_SIMULATION_NAME} SHARED 
    	C:/Users/sino3/Desktop/GitHub/Gaia_Universe_Model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-universe-model.c
C:/Users/sino3/Desktop/GitHub/Gaia_Universe_Model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-sim.c

)
elseif("${SH_SIMULATION_BINARY_TYPE}" STREQUAL "EXECUTABLE")
    add_executable(${SH_SIMULATION_NAME}  
    	C:/Users/sino3/Desktop/GitHub/Gaia_Universe_Model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-universe-model.c
C:/Users/sino3/Desktop/GitHub/Gaia_Universe_Model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-sim.c

)
endif()
target_include_directories(${SH_SIMULATION_NAME} PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/${SH_SIMULATION_NAME}/include
)
target_link_libraries(${SH_SIMULATION_NAME} PUBLIC shengine 	gaia-archive-tools )
set_target_properties(${SH_SIMULATION_NAME} PROPERTIES 
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin  
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
