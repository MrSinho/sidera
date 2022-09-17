
# gaia-universe-model

![windows-badge](windows-status.svg)

## [windows build logs:](https://github.com/mrsinho/shci)

        
```bash
choco install -y mingw cmake
mingw-get install gcc mingw32-make gdb
```

```bash
Chocolatey v0.11.2
Installing the following packages:
mingw;cmake
By installing, you accept licenses for the packages.
mingw v11.2.0.07112021 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
cmake v3.22.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Chocolatey installed 0/2 packages. 
 See the log for details (C:\ProgramData\chocolatey\logs\chocolatey.log).

Warnings:
 - cmake - cmake v3.22.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
 - mingw - mingw v11.2.0.07112021 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Did you know the proceeds of Pro (and some proceeds from other
 licensed editions) go into bettering the community infrastructure?
 Your support ensures an active community, keeps Chocolatey tip-top,
 plus it nets you some awesome features!
 https://chocolatey.org/compare

```

---

    
```bash
cd gaia-universe-model/external/shengine && python export-simulation.py gaia-universe-model SHARED ../../gaia-universe-model
```

```bash
-- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.21996.
-- Found Doxygen: C:/ProgramData/chocolatey/bin/doxygen.exe (found version "1.9.1") found components: doxygen 
-- Including Win32 support
-- Wrote C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/json-c/config.h
-- Wrote C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/json-c/json_config.h
-- Found Doxygen: C:/ProgramData/chocolatey/bin/doxygen.exe (found version "1.9.1") found components: doxygen missing components: dot
-- Wrote C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/json-c/doc/Doxyfile
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build
loading C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model/source-files.txt
/src/gaia-universe-model.c
/src/gaia-sim.c
loading C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model/libs.txt
gaia-archive-tools ../external/gaia-archive-tools
subdirectories:
		if (NOT TARGET ../external/gaia-archive-tools)
add_subdirectory(../external/gaia-archive-tools [EXCLUDE_FROM_ALL])
endif()


cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

	if (NOT TARGET ../external/gaia-archive-tools)
add_subdirectory(../external/gaia-archive-tools [EXCLUDE_FROM_ALL])
endif()


option(SH_SIMULATION_NAME CACHE emptytarget)
project(${SH_SIMULATION_NAME})

option(SH_SIMULATION_BINARY_TYPE CACHE "EXECUTABLE")
if("${SH_SIMULATION_BINARY_TYPE}" STREQUAL "STATIC")
    add_library(${SH_SIMULATION_NAME} STATIC 
    	C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-universe-model.c
C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-sim.c

)
elseif("${SH_SIMULATION_BINARY_TYPE}" STREQUAL "SHARED")
    add_library(${SH_SIMULATION_NAME} SHARED 
    	C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-universe-model.c
C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-sim.c

)
elseif("${SH_SIMULATION_BINARY_TYPE}" STREQUAL "EXECUTABLE")
    add_executable(${SH_SIMULATION_NAME}  
    	C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-universe-model.c
C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model//src/gaia-sim.c

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

running command cd C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build && cmake .. -DSH_ENGINE_BUILD_EDITOR=ON -DSIMULATION_PATH=C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model -DSH_EDITOR_ASSETS_PATH=C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/../../gaia-universe-model/gaia-universe-model/assets/ -DSH_SIMULATION_NAME=gaia-universe-model -DSH_SIMULATION_BINARY_TYPE=SHARED 

```

---

    