
# Windows build logs

![](windows-exit-code.svg)

```
system        : Windows
version       : 10.0.22621
platform      : Windows-10-10.0.22621-SP0
processor     : AMD64 Family 23 Model 17 Stepping 0, AuthenticAMD
min frequency : 0.0 MHz
max frequency : 3500.0 MHz
cores         : 4
```

build ran for `55.53 s` and terminated with exit code `0`

---

```bash
> .shci/windows/prerequisites-output.txt (
    choco install -y mingw cmake
    mingw-get install gcc mingw32-make gdb
)
```

```bash
Chocolatey v2.0.0
Chocolatey detected you are not running from an elevated command shell
 (cmd/powershell).

 You may experience errors - many functions/packages
 require admin rights. Only advanced users should run choco w/out an
 elevated shell. When you open the command shell, you should ensure
 that you do so with "Run as Administrator" selected. If you are
 attempting to use Chocolatey in a non-administrator setting, you
 must select a different location other than the default install
 location. See
 https://docs.chocolatey.org/en-us/choco/setup#non-administrative-install
 for details.

For the question below, you have 20 seconds to make a selection.

 Do you want to continue?([Y]es/[N]o): 
Timeout or your choice of '' is not a valid selection.
Installing the following packages:
mingw;cmake
By installing, you accept licenses for the packages.
mingw v12.2.0.03042023 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
cmake v3.26.4 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Chocolatey installed 0/2 packages. 
 See the log for details (C:\ProgramData\chocolatey\logs\chocolatey.log).

Warnings:
 - cmake - cmake v3.26.4 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
 - mingw - mingw v12.2.0.03042023 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Did you know the proceeds of Pro (and some proceeds from other
 licensed editions) go into bettering the community infrastructure?
 Your support ensures an active community, keeps Chocolatey tip-top,
 plus it nets you some awesome features!
 https://chocolatey.org/compare

```

---
    
```bash
> .shci/windows/build-output.txt (
    cd externals/shengine
    python export-application.py name=gaia-universe-model target=EXECUTABLE path=../../gaia-universe-model
    cd ../../gaia-universe-model/windows/build
    cmake --build .
)

```

```bash
-- Building for: Visual Studio 17 2022
-- Selecting Windows SDK version 10.0.22000.0 to target Windows 10.0.22621.
-- The C compiler identification is MSVC 19.36.32532.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: D:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found Vulkan: D:/lib/VulkanSDK/1.3.250.0/Lib/vulkan-1.lib (found version "1.3.250") found components: glslc glslangValidator 
-- shvulkan message: found Vulkan
-- shvulkan message: Vulkan_INCLUDE_DIR: D:/lib/VulkanSDK/1.3.250.0/Include
-- shvulkan message: Vulkan_LIBRARY:     D:/lib/VulkanSDK/1.3.250.0/Lib/vulkan-1.lib
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - not found
-- Found Threads: TRUE  
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE) 
-- Including Win32 support
-- Configuring done (13.6s)
-- Generating done (1.8s)
-- Build files have been written to: D:/home/desktop/GitHub/gaia-universe-model/gaia-universe-model/windows/build
--------------------------------------------------------------------------------
EXAMPLE CALL: python export-application.py name=noise target=SHARED
EXAMPLE CALL: python export-application.py name=noise target=STATIC path=applications/noise
EXAMPLE CALL: python export-application.py name=noise target=SHARED path=applications/noise generator=MinGW-Makefiles
EXAMPLE CALL: python export-application.py name=noise target=EXECUTABLE path=applications/noise generator=MinGW-Makefiles CLEAN-CACHE
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
platform:       windows
python_src_dir: D:/home/desktop/GitHub/gaia-universe-model/externals/shengine
name:           gaia-universe-model
path:           D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model
target_type:    EXECUTABLE
generator:      
clean-cache:    
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
loading D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/source-files.txt
src files:
	/src/gaia-universe-model.c
/src/gaia-sim.c

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
loading D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/libs.txt
additional libraries:
	gaia-archive-tools ../externals/gaia-archive-tools
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
CMake subdirectories:
		if (NOT TARGET ../externals/gaia-archive-tools)
add_subdirectory(../externals/gaia-archive-tools [EXCLUDE_FROM_ALL])
endif()


--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
CMake file:
cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

	if (NOT TARGET ../externals/gaia-archive-tools)
add_subdirectory(../externals/gaia-archive-tools [EXCLUDE_FROM_ALL])
endif()


project(gaia-universe-model C)

option(SH_APPLICATION_BINARY_TYPE CACHE "EXECUTABLE")
if("${SH_APPLICATION_BINARY_TYPE}" STREQUAL "STATIC")
    add_library(${SH_APPLICATION_NAME} STATIC 
        	D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-universe-model.c
D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-sim.c

    )
    
elseif("${SH_APPLICATION_BINARY_TYPE}" STREQUAL "SHARED")
    add_library(${SH_APPLICATION_NAME} SHARED 
        	D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-universe-model.c
D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-sim.c

    )
    target_compile_definitions(shengine PUBLIC SH_APPLICATION_TARGET_TYPE_SHARED=1)
    set_target_properties(${SH_APPLICATION_NAME} sheditor PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/bin/ 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/bin/
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/bin/
    )
elseif("${SH_APPLICATION_BINARY_TYPE}" STREQUAL "EXECUTABLE")
    add_executable(${SH_APPLICATION_NAME}  
        	D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-universe-model.c
D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-sim.c

        D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/collection/sheditor/src/shEditor.c
    )
    target_include_directories(${SH_APPLICATION_NAME} PUBLIC D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/collection/sheditor/include)
    target_compile_definitions(${SH_APPLICATION_NAME} PUBLIC SH_APPLICATION_TARGET_TYPE_EXECUTABLE=1)
    set_target_properties(${SH_APPLICATION_NAME} PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/bin/ 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/bin/
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/bin/
    )
endif()

target_include_directories(${SH_APPLICATION_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    ${SH_APPLICATION_NAME} PUBLIC shengine 	gaia-archive-tools 
)

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
writing to CMake file: D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/CMakeLists.txt
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
Os path: D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/windows
Build path: D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/windows/build

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
creating build directory: D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/windows/build
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
running command:
	cd D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/windows/build && cmake D:/home/desktop/GitHub/gaia-universe-model/externals/shengine -DSH_ENGINE_BUILD_EDITOR=ON -DSH_APPLICATION_PATH=D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model -DSH_APPLICATION_NAME=gaia-universe-model -DSH_APPLICATION_BINARY_TYPE=EXECUTABLE 
--------------------------------------------------------------------------------

MSBuild version 17.6.3+07e294721 for .NET Framework

  Checking Build System
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
  mat2x3.c
  mat2x4.c
  mat3.c
  mat3x2.c
  mat3x4.c
  mat4.c
  mat4x2.c
  mat4x3.c
  Generazione del codice in corso...
  Compilazione in corso...
  plane.c
  frustum.c
  box.c
  project.c
  sphere.c
  ease.c
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
  Generazione del codice in corso...
  Compilazione in corso...
  view_rh_no.c
  view_rh_zo.c
  project_no.c
  project_zo.c
  Generazione del codice in corso...
     Creazione della libreria D:/home/desktop/GitHub/gaia-universe-model/gaia-universe-model/windows/build/collection/externals/cglm/Debug/cglm.lib e dell'oggetto D:/home/desktop/GitHub/gaia-universe-model/gaia-universe-model/windows/build/collection/externals/cglm/Debug/cglm.exp
  cglm.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\gaia-universe-model\windows\build\collection\externals\cglm\Debug\cglm-0.dll
  gaia-archive-tools.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\gaia-archive-tools.lib
  gaia-exp.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\gaia-exp.exe
  gaia-split.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\gaia-split.exe
  glfw.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\gaia-universe-model\windows\build\collection\externals\glfw\src\Debug\glfw3.lib
  shvulkan.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\shvulkan.lib
  smd.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\smd.lib
  shenvironment.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\shenvironment.lib
  shthreads.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\shthreads.lib
  shapplicationhost.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\gaia-universe-model\windows\build\collection\Debug\shapplicationhost.lib
  shserial.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\collection\externals\shserial\bin\Debug\shserial.lib
  shengine.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\shengine.lib
  gaia-universe-model.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\gaia-universe-model\windows\bin\Debug\gaia-universe-model.exe
  plyimporter.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\plyimporter.lib
  sheditor.vcxproj -> D:\home\desktop\GitHub\gaia-universe-model\externals\shengine\bin\Debug\sheditor.exe
  Building Custom Rule D:/home/desktop/GitHub/gaia-universe-model/externals/shengine/CMakeLists.txt

```

---
    
build ran for `55.53 s` and terminated with exit code `0`

---

