
# gaia-universe-model

![windows-badge](windows-exit_code.svg)

## [windows build logs:](https://github.com/mrsinho/shci)

        

Build ran for `143.50s`

---

```bash
choco install -y curl mingw cmake
mingw-get install gcc mingw32-make gdb
```

```bash
Chocolatey v0.11.2
Installing the following packages:
curl;mingw;cmake
By installing, you accept licenses for the packages.
curl v7.80.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
mingw v11.2.0.07112021 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
cmake v3.22.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Chocolatey installed 0/3 packages. 
 See the log for details (C:\ProgramData\chocolatey\logs\chocolatey.log).

Warnings:
 - cmake - cmake v3.22.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
 - curl - curl v7.80.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
 - mingw - mingw v11.2.0.07112021 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

```

---

    
```bash
cd gaia-universe-model/external/shengine 
python export-simulation.py gaia-universe-model SHARED ../../gaia-universe-model
cd build
cmake --build .
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
Microsoft (R) Build Engine version 17.2.1+52cd2da31 for .NET Framework
Copyright (C) Microsoft Corporation. All rights reserved.

  Checking Build System
  Generating HTML documentation
CUSTOMBUILD : warning : ignoring unsupported tag 'CREATE_SUBDIRS_LEVEL' at line 93, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'SHOW_HEADERFILE' at line 633, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'WARN_IF_INCOMPLETE_DOC' at line 851, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'WARN_LINE_FORMAT' at line 891, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'INPUT_FILE_ENCODING' at line 948, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'FORTRAN_COMMENT_AFTER' at line 1106, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'HTML_COLORSTYLE' at line 1317, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'DOCSET_FEEDURL' at line 1418, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'FULL_SIDEBAR' at line 1629, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'OBFUSCATE_EMAILS' at line 1660, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'MATHJAX_VERSION' at line 1708, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'DOT_COMMON_ATTR' at line 2418, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'DOT_EDGE_ATTR' at line 2427, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'DOT_NODE_ATTR' at line 2435, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : ignoring unsupported tag 'DIR_GRAPH_MAX_DEPTH' at line 2585, file Doxyfile [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
CUSTOMBUILD : warning : argument 'SYSTEM' for option CASE_SENSE_NAMES is not a valid boolean value [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\docs\docs.vcxproj]
  Using the default: NO!
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/glfw/docs/CMakeLists.txt
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/cglm/CMakeLists.txt
  euler.c
  affine.c
  io.c
  quat.c
  cam.c
  vec2.c
  ivec2.c
  vec3.c
  ivec3.c
  vec4.c
  ivec4.c
  mat2.c
  mat3.c
  mat4.c
  plane.c
  frustum.c
  box.c
  project.c
  sphere.c
  ease.c
  Generating Code...
  Compiling...
  curve.c
  bezier.c
  ray.c
  affine2d.c
  ortho_lh_no.c
  ortho_lh_zo.c
  ortho_rh_no.c
  ortho_rh_zo.c
  persp_lh_no.c
  persp_lh_zo.c
  persp_rh_no.c
  persp_rh_zo.c
  view_lh_no.c
  view_lh_zo.c
  view_rh_no.c
  view_rh_zo.c
  project_no.c
  project_zo.c
  Generating Code...
     Creating library C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/cglm/Debug/cglm.lib and object C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/build/shengine/externals/cglm/Debug/cglm.exp
  cglm.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\cglm\Debug\cglm-0.dll
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shgui/externals/native-export/c/CMakeLists.txt
  native-export.c
  native-export.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\native-export.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shgui/CMakeLists.txt
  export-shaders.c
  export-shaders.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\shgui\Debug\export-shaders.exe
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/gaia-archive-tools/CMakeLists.txt
  gaia-archive-tools.c
  csv.c
  Generating Code...
  gaia-archive-tools.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\gaia-archive-tools.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/gaia-archive-tools/CMakeLists.txt
  gaia-exp.c
  gaia-archive-tools.c
  csv.c
  Generating Code...
  gaia-exp.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\gaia-exp.exe
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/gaia-archive-tools/CMakeLists.txt
  gaia-split.c
  gaia-archive-tools.c
  csv.c
  Generating Code...
  gaia-split.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\gaia-split.exe
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/glfw/src/CMakeLists.txt
  context.c
  init.c
  input.c
  monitor.c
  platform.c
  vulkan.c
  window.c
  egl_context.c
  osmesa_context.c
  null_init.c
  null_monitor.c
  null_window.c
  null_joystick.c
  win32_module.c
  win32_time.c
  win32_thread.c
  win32_init.c
  win32_joystick.c
  win32_monitor.c
  win32_window.c
  Generating Code...
  Compiling...
  wgl_context.c
  Generating Code...
  glfw.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\glfw\src\Debug\glfw3.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/json-c/CMakeLists.txt
  arraylist.c
  debug.c
  json_c_version.c
  json_object.c
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\json-c\json_object.c(204,52): warning C4267: 'function': conversion from 'size_t' to 'int', possible loss of data [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\json-c.vcxproj]
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\json-c\json_object.c(231,29): warning C4267: 'function': conversion from 'size_t' to 'int', possible loss of data [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\json-c.vcxproj]
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\json-c\json_object.c(242,50): warning C4267: 'function': conversion from 'size_t' to 'int', possible loss of data [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\json-c.vcxproj]
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\json-c\json_object.c(682,38): warning C4267: 'function': conversion from 'size_t' to 'int', possible loss of data [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\json-c.vcxproj]
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\json-c\json_object.c(1136,21): warning C4267: 'initializing': conversion from 'size_t' to 'int', possible loss of data [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\json-c.vcxproj]
  json_object_iterator.c
  json_tokener.c
  json_util.c
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\json-c\json_util.c(212,47): warning C4267: 'function': conversion from 'size_t' to 'unsigned int', possible loss of data [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\json-c.vcxproj]
  json_visit.c
  linkhash.c
  printbuf.c
  random_seed.c
  strerror_override.c
  json_pointer.c
  Generating Code...
  json-c.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\externals\json-c\Debug\json-c.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/plyimporter/CMakeLists.txt
  plyImporter.c
  plyimporter.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\plyimporter.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shvulkan/CMakeLists.txt
  shVkCore.c
  shVkMemoryInfo.c
  shVkPipelineData.c
  shVkCheck.c
  shVkDrawLoop.c
  Generating Code...
  shvulkan.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\shvulkan.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/CMakeLists.txt
  shFile.c
  shfd.c
  Generating Code...
  shfd.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\shfd.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shgui/CMakeLists.txt
  shgui.c
  shgui.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\shgui.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shserial/CMakeLists.txt
  shSerial.c
  shserial.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\shserial\bin\Debug\shserial.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/CMakeLists.txt
  shSharedHost.c
  shsharedhost.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\Debug\shsharedhost.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shthreads/CMakeLists.txt
  shthreads.c
  shthreads.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\shthreads.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/CMakeLists.txt
  shEngine.c
  shInput.c
  shTime.c
  shWindow.c
C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared\minwindef.h(130,1): warning C4005: 'APIENTRY': macro redefinition [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\shengine.vcxproj]
C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\shengine\externals\glfw\include\GLFW/glfw3.h(123): message : see previous definition of 'APIENTRY' [C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\build\shengine\shengine.vcxproj]
  shProjection.c
  shView.c
  shScene.c
  shMaterialHost.c
  shEgui.c
  Generating Code...
  shengine.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\shengine.lib
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/gaia-universe-model/CMakeLists.txt
  gaia-universe-model.c
  gaia-sim.c
  Generating Code...
     Creating library C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/bin/Debug/gaia-universe-model.lib and object C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/bin/Debug/gaia-universe-model.exp
  gaia-universe-model.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\gaia-universe-model.dll
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/externals/shecs/CMakeLists.txt
  shecs-example.c
  shecs-example.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\shecs-example.exe
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/shengine/CMakeLists.txt
  shEditor.c
  sheditor.vcxproj -> C:\Users\sino3\Desktop\shci-test\gaia-universe-model\gaia-universe-model\external\shengine\bin\Debug\sheditor.exe
  Building Custom Rule C:/Users/sino3/Desktop/shci-test/gaia-universe-model/gaia-universe-model/external/shengine/CMakeLists.txt

```

---

    

Build terminated with exit code 0

---

