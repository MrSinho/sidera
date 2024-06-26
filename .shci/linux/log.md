
# Linux build logs

![](linux-exit-code.svg)

```
system        : Linux
version       : #1 SMP Fri Jan 27 02:56:13 UTC 2023
platform      : Linux-5.15.90.1-microsoft-standard-WSL2-x86_64-with-glibc2.31
processor     : 
min frequency : 0.0 MHz
max frequency : 0.0 MHz
cores         : 4
```

build ran for `195.10 s` and terminated with exit code `0`

---

```bash
function PREREQUISITES {
    sudo apt -y update
    sudo apt install -y libvulkan-dev libvulkan1
    sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev
    sudo apt install -y libwayland-dev
    sudo apt install -y python3.9 python3-pip
    sudo apt install -y gcc cmake make libc6-dev
}

PREREQUISITES > .shci/linux/prerequisites-output.txt

```

```bash
Get:1 http://security.debian.org/debian-security bullseye-security InRelease [48.4 kB]
Hit:2 http://ftp.debian.org/debian bullseye-backports InRelease
Hit:3 http://deb.debian.org/debian bullseye InRelease
Hit:4 http://deb.debian.org/debian bullseye-updates InRelease
Fetched 48.4 kB in 0s (112 kB/s)
Reading package lists...
Building dependency tree...
Reading state information...
6 packages can be upgraded. Run 'apt list --upgradable' to see them.
Reading package lists...
Building dependency tree...
Reading state information...
libvulkan-dev is already the newest version (1.2.162.0-1).
libvulkan1 is already the newest version (1.2.162.0-1).
0 upgraded, 0 newly installed, 0 to remove and 6 not upgraded.
Reading package lists...
Building dependency tree...
Reading state information...
libxcursor-dev is already the newest version (1:1.2.0-2).
libxinerama-dev is already the newest version (2:1.1.4-2).
libxrandr-dev is already the newest version (2:1.5.1-1).
libx11-dev is already the newest version (2:1.7.2-1+deb11u1).
0 upgraded, 0 newly installed, 0 to remove and 6 not upgraded.
Reading package lists...
Building dependency tree...
Reading state information...
libwayland-dev is already the newest version (1.18.0-2~exp1.1).
0 upgraded, 0 newly installed, 0 to remove and 6 not upgraded.
Reading package lists...
Building dependency tree...
Reading state information...
python3-pip is already the newest version (20.3.4-4+deb11u1).
python3.9 is already the newest version (3.9.2-1).
0 upgraded, 0 newly installed, 0 to remove and 6 not upgraded.
Reading package lists...
Building dependency tree...
Reading state information...
cmake is already the newest version (3.18.4-2+deb11u1).
gcc is already the newest version (4:10.2.1-1).
libc6-dev is already the newest version (2.31-13+deb11u6).
make is already the newest version (4.3-4.1).
0 upgraded, 0 newly installed, 0 to remove and 6 not upgraded.

```

---
    
```bash
function BUILD {
	cd externals/shengine
    python3.9 export-application.py name=gaia-universe-model target=EXECUTABLE path=../../gaia-universe-model
    cd ../../gaia-universe-model/linux/build
    cmake --build .
}

BUILD > .shci/linux/build-output.txt

```

```bash
-- The C compiler identification is GNU 10.2.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found Vulkan: /usr/lib/x86_64-linux-gnu/libvulkan.so  
-- shvulkan message: found Vulkan
-- shvulkan message: Vulkan_INCLUDE_DIR: /usr/include
-- shvulkan message: Vulkan_LIBRARY:     /usr/lib/x86_64-linux-gnu/libvulkan.so
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE) 
-- Including X11 support
-- Found X11: /usr/include   
-- Looking for XOpenDisplay in /usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXext.so
-- Looking for XOpenDisplay in /usr/lib/x86_64-linux-gnu/libX11.so;/usr/lib/x86_64-linux-gnu/libXext.so - found
-- Looking for gethostbyname
-- Looking for gethostbyname - found
-- Looking for connect
-- Looking for connect - found
-- Looking for remove
-- Looking for remove - found
-- Looking for shmat
-- Looking for shmat - found
-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/d/home/desktop/GitHub/gaia-universe-model/gaia-universe-model/linux/build
--------------------------------------------------------------------------------
EXAMPLE CALL: python export-application.py name=noise target=SHARED
EXAMPLE CALL: python export-application.py name=noise target=STATIC path=applications/noise
EXAMPLE CALL: python export-application.py name=noise target=SHARED path=applications/noise generator=MinGW-Makefiles
EXAMPLE CALL: python export-application.py name=noise target=EXECUTABLE path=applications/noise generator=MinGW-Makefiles CLEAN-CACHE
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
platform:       linux
python_src_dir: /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine
name:           gaia-universe-model
path:           /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model
target_type:    EXECUTABLE
generator:      
clean-cache:    
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
loading /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/source-files.txt
src files:
	/src/gaia-universe-model.c
/src/gaia-sim.c

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
loading /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/libs.txt
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
        	/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-universe-model.c
/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-sim.c

    )
    
elseif("${SH_APPLICATION_BINARY_TYPE}" STREQUAL "SHARED")
    add_library(${SH_APPLICATION_NAME} SHARED 
        	/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-universe-model.c
/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-sim.c

    )
    target_compile_definitions(shengine PUBLIC SH_APPLICATION_TARGET_TYPE_SHARED=1)
    set_target_properties(${SH_APPLICATION_NAME} sheditor PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/bin/ 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/bin/
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/bin/
    )
elseif("${SH_APPLICATION_BINARY_TYPE}" STREQUAL "EXECUTABLE")
    add_executable(${SH_APPLICATION_NAME}  
        	/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-universe-model.c
/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model//src/gaia-sim.c

        /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/collection/sheditor/src/shEditor.c
    )
    target_include_directories(${SH_APPLICATION_NAME} PUBLIC /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/collection/sheditor/include)
    target_compile_definitions(${SH_APPLICATION_NAME} PUBLIC SH_APPLICATION_TARGET_TYPE_EXECUTABLE=1)
    set_target_properties(${SH_APPLICATION_NAME} PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/bin/ 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/bin/
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/bin/
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
writing to CMake file: /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/CMakeLists.txt
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
Os path: /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/linux
Build path: /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/linux/build

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
creating build directory: /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/linux/build
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
running command:
	cd /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model/linux/build && cmake /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine -DSH_ENGINE_BUILD_EDITOR=ON -DSH_APPLICATION_PATH=/mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/../../gaia-universe-model -DSH_APPLICATION_NAME=gaia-universe-model -DSH_APPLICATION_BINARY_TYPE=EXECUTABLE 
--------------------------------------------------------------------------------

[  2%] Built target smd
[  4%] Built target shvulkan
[  7%] Built target shenvironment
[  9%] Built target shthreads
[ 11%] Built target shapplicationhost
[ 13%] Built target shserial
[ 36%] Built target glfw
Scanning dependencies of target cglm
[ 36%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/euler.c.o
[ 37%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/affine.c.o
[ 38%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/io.c.o
[ 39%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/quat.c.o
[ 40%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/cam.c.o
[ 41%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/vec2.c.o
[ 42%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/ivec2.c.o
[ 43%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/vec3.c.o
[ 44%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/ivec3.c.o
[ 45%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/vec4.c.o
[ 46%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/ivec4.c.o
[ 47%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat2.c.o
[ 48%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat2x3.c.o
[ 49%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat2x4.c.o
[ 50%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat3.c.o
[ 51%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat3x2.c.o
[ 52%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat3x4.c.o
[ 52%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat4.c.o
[ 53%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat4x2.c.o
[ 54%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/mat4x3.c.o
[ 55%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/plane.c.o
[ 56%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/frustum.c.o
[ 57%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/box.c.o
[ 58%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/project.c.o
[ 59%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/sphere.c.o
[ 60%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/ease.c.o
[ 61%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/curve.c.o
[ 62%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/bezier.c.o
[ 63%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/ray.c.o
[ 64%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/affine2d.c.o
[ 65%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/ortho_lh_no.c.o
[ 66%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/ortho_lh_zo.c.o
[ 67%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/ortho_rh_no.c.o
[ 68%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/ortho_rh_zo.c.o
[ 69%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/persp_lh_no.c.o
[ 69%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/persp_lh_zo.c.o
[ 70%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/persp_rh_no.c.o
[ 71%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/persp_rh_zo.c.o
[ 72%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/view_lh_no.c.o
[ 73%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/view_lh_zo.c.o
[ 74%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/view_rh_no.c.o
[ 75%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/view_rh_zo.c.o
[ 76%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/project_no.c.o
[ 77%] Building C object collection/externals/cglm/CMakeFiles/cglm.dir/src/clipspace/project_zo.c.o
[ 78%] Linking C shared library libcglm.so
[ 78%] Built target cglm
Scanning dependencies of target shengine
[ 79%] Building C object collection/CMakeFiles/shengine.dir/shengine/src/shProfiling.c.o
[ 80%] Linking C static library /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/bin/libshengine.a
[ 85%] Built target shengine
[ 86%] Linking C executable /mnt/d/home/desktop/GitHub/gaia-universe-model/externals/shengine/bin/sheditor
[ 87%] Built target sheditor
[ 89%] Built target plyimporter
[ 92%] Built target gaia-archive-tools
Scanning dependencies of target gaia-universe-model
[ 93%] Building C object [EXCLUDE_FROM_ALL]/CMakeFiles/gaia-universe-model.dir/src/gaia-universe-model.c.o
[ 94%] Linking C executable ../../bin/gaia-universe-model
[ 95%] Built target gaia-universe-model
[ 97%] Built target gaia-split
[100%] Built target gaia-exp

```

---
    
build ran for `195.10 s` and terminated with exit code `0`

---

