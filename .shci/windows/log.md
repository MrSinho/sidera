
# gaia-universe-model

![windows-badge](exit_code.svg)

## [windows build logs:](https://github.com/mrsinho/shci)

```
system        : Windows
version       : 10.0.22621
platform      : Windows-10-10.0.22621-SP0
processor     : AMD64 Family 23 Model 17 Stepping 0, AuthenticAMD
min frequency : 0.0 MHz
max frequency : 3500.0 MHz
cores         : 4
```

build ran for `9.45 s` and terminated with exit code `0`

---

```bash
> .shci/windows/prerequisites-output.txt (
    choco install -y mingw cmake
    mingw-get install gcc mingw32-make gdb
)
```

```bash
Chocolatey v2.0.0
2 validations performed. 1 success(es), 1 warning(s), and 0 error(s).

Validation Warnings:
 - A pending system reboot request has been detected, however, this is
   being ignored due to the current Chocolatey configuration.  If you
   want to halt when this occurs, then either set the global feature
   using:
     choco feature enable -name=exitOnRebootDetected
   or pass the option --exit-when-reboot-detected.

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

```

---
    
```bash
> .shci/windows/build-output.txt (
    mkdir windows-build
    cd windows-build
    cmake .. -DGAIA_ARCHIVE_TOOLS_BUILD_EXAMPLES=ON
    cmake --build .
)

```

```bash
-- Selecting Windows SDK version 10.0.22000.0 to target Windows 10.0.22621.
-- Configuring done (0.0s)
-- Generating done (0.1s)
-- Build files have been written to: D:/home/desktop/GitHub/gaia-archive-tools/windows-build
MSBuild version 17.6.3+07e294721 for .NET Framework

  Checking Build System
  Building Custom Rule D:/home/desktop/GitHub/gaia-archive-tools/CMakeLists.txt
  gaia-archive-tools.vcxproj -> D:\home\desktop\GitHub\gaia-archive-tools\bin\Debug\gaia-archive-tools.lib
  Building Custom Rule D:/home/desktop/GitHub/gaia-archive-tools/CMakeLists.txt
  gaia-convert.c
  gaia-convert-sample.vcxproj -> D:\home\desktop\GitHub\gaia-archive-tools\bin\Debug\gaia-convert-sample.exe
  Building Custom Rule D:/home/desktop/GitHub/gaia-archive-tools/CMakeLists.txt
  gaia-exp.c
  gaia-exp.vcxproj -> D:\home\desktop\GitHub\gaia-archive-tools\bin\Debug\gaia-exp.exe
  Building Custom Rule D:/home/desktop/GitHub/gaia-archive-tools/CMakeLists.txt
  gaia-read.c
  gaia-read-sample.vcxproj -> D:\home\desktop\GitHub\gaia-archive-tools\bin\Debug\gaia-read-sample.exe
  Building Custom Rule D:/home/desktop/GitHub/gaia-archive-tools/CMakeLists.txt
  gaia-split.vcxproj -> D:\home\desktop\GitHub\gaia-archive-tools\bin\Debug\gaia-split.exe
  Building Custom Rule D:/home/desktop/GitHub/gaia-archive-tools/CMakeLists.txt

```

---
    
build ran for `9.45 s` and terminated with exit code `0`

---

