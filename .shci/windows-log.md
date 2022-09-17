
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

```

---

    
```bash
cd gaia-universe-model/external/shengine && python export-simulation.py gaia-universe-model SHARED ../../gaia-universe-model
```

```bash
-- Building for: Visual Studio 17 2022
-- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.21996.
-- The C compiler identification is MSVC 19.32.31332.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.32.31326/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found Vulkan: C:/VulkanSDK/1.2.198.1/Lib/vulkan-1.lib  
-- Looking for pthread.h
-- Looking for pthread.h - not found
-- Found Threads: TRUE  
-- Found Doxygen: C:/ProgramData/chocolatey/bin/doxygen.exe (found version "1.9.1") found components: doxygen 
-- Including Win32 support
-- Looking for fcntl.h
-- Looking for fcntl.h - found
-- Looking for inttypes.h
-- Looking for inttypes.h - found
-- Looking for stdarg.h
-- Looking for stdarg.h - found
-- Looking for strings.h
-- Looking for strings.h - not found
-- Looking for string.h
-- Looking for string.h - found
-- Looking for syslog.h
-- Looking for syslog.h - not found
-- Looking for 4 include files stdlib.h, ..., float.h
-- Looking for 4 include files stdlib.h, ..., float.h - found
-- Looking for unistd.h
-- Looking for unistd.h - not found
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Looking for sys/resource.h
-- Looking for sys/resource.h - not found
-- Looking for dlfcn.h
-- Looking for dlfcn.h - not found
-- Looking for endian.h
-- Looking for endian.h - not found
-- Looking for limits.h
-- Looking for limits.h - found
-- Looking for locale.h
-- Looking for locale.h - found
-- Looking for memory.h
-- Looking for memory.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stdlib.h
-- Looking for stdlib.h - found
-- Looking for sys/cdefs.h
-- Looking for sys/cdefs.h - not found
-- Looking for sys/param.h
-- Looking for sys/param.h - not found
-- Looking for sys/random.h
-- Looking for sys/random.h - not found
-- Looking for sys/stat.h
-- Looking for sys/stat.h - found
-- Looking for xlocale.h
-- Looking for xlocale.h - not found
-- Looking for _isnan
-- Looking for _isnan - found
-- Looking for _finite
-- Looking for _finite - found
-- Looking for INFINITY
-- Looking for INFINITY - found
-- Looking for isinf
-- Looking for isinf - found
-- Looking for isnan
-- Looking for isnan - found
-- Looking for nan
-- Looking for nan - found
-- Looking for _doprnt
-- Looking for _doprnt - not found
-- Looking for vasprintf
-- Looking for vasprintf - not found
-- Looking for vsnprintf
-- Looking for vsnprintf - found
-- Looking for vprintf
-- Looking for vprintf - found
-- Looking for arc4random
-- Looking for arc4random - not found
-- Looking for bsd/stdlib.h
-- Looking for bsd/stdlib.h - not found
-- Looking for open
-- Looking for open - not found
-- Looking for realloc
-- Looking for realloc - found
-- Looking for setlocale
-- Looking for setlocale - found
-- Looking for uselocale
-- Looking for uselocale - not found
-- Looking for strdup
-- Looking for strdup - found
-- Looking for strerror
-- Looking for strerror - found
-- Looking for strtoll
-- Looking for strtoll - found
-- Looking for strtoull
-- Looking for strtoull - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Check size of int
-- Check size of int - done
-- Check size of int64_t
-- Check size of int64_t - done
-- Check size of long
-- Check size of long - done
-- Check size of long long
-- Check size of long long - done
-- Check size of size_t
-- Check size of size_t - done
-- Check size of SSIZE_T
-- Check size of SSIZE_T - done
-- Performing Test HAS_GNU_WARNING_LONG
-- Performing Test HAS_GNU_WARNING_LONG - Failed
-- Performing Test HAVE_ATOMIC_BUILTINS
-- Performing Test HAVE_ATOMIC_BUILTINS - Failed
-- Performing Test HAVE___THREAD
-- Performing Test HAVE___THREAD - Failed
-- Wrote C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/json-c/config.h
-- Wrote C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/json-c/json_config.h
-- Found Doxygen: C:/ProgramData/chocolatey/bin/doxygen.exe (found version "1.9.1") found components: doxygen missing components: dot
-- Wrote C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/json-c/doc/Doxyfile
-- The CXX compiler identification is MSVC 19.32.31332.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.32.31326/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
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

    