# Terminal install

![](https://img.shields.io/badge/SIDERA%20|%20SINHO%20SOFTWORKS-3CFADC?style=for-the-badge&logo=&logoColor=white&labelColor=990042)
[![](https://img.shields.io/badge/GitHub_repository-000000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/mrsinho/crystallography-model)


[TOC]

## Clone and build (cmake)

To generate the CMake targets, open the terminal with admin/root permission and run the following commands:

```bash
git clone --recursive https://github.com/mrsinho/sidera
cd sidera
```

@note If you get a python syntax error, try specifying the python version (must be 3.0 or greater).

![](./media/mass_feh_age_polar__agecf.png)


<div class="tabbed">

- <b class="tab-title">Windows</b>
    ```bash
    cd scripts
    start download-release.bat
    cd ../sidera
    mkdir build
    mkdir build/windows
    cd build/windows
    cmake ../../ -DSIDERA_BINARY_TYPE=EXECUTABLE -DSH_ENGINE_ROOT_DIR="repo/absolute/path/externals/shengine"
    cmake --build .
    ```

    The Windows binaries are compiled at `sidera/bin/windows`


- <b class="tab-title">Linux</b>
    ```bash
    cd scripts
    start download-release.sh
    cd ../sidera
    mkdir build
    mkdir build/linux
    cd build/linux
    cmake ../../ -DSIDERA_BINARY_TYPE=EXECUTABLE -DSH_ENGINE_ROOT_DIR="repo/absolute/path/externals/shengine"
    cmake --build .
    ```

    The Linux binaries are compiled at `sidera/bin/linux`

</div>






## Move ini file

The engine needs to know where to locate the universe model assets path, and some general properties of the application: 

<div class="tabbed">

- <b class="tab-title">Windows</b>
    ```bash
    #starting from root repo
    cd sidera/
    cp ini.smd bin/windows/ini.smd
    ```

- <b class="tab-title">Linux</b>
    ```bash
    #starting from root repo
    cd sidera/
    cp ini.smd bin/linux/ini.smd
    ```

</div>

![](./media/age_mass_feh__fehcf_cartesian.png)



## Download Gaia Data Release binaries

@note The following steps require a python3.11+ interpreter to be already installed in your system.

Now navigate to the installation path and find the `scripts` directory and run the `download-release` batch/shell script:

<div class="tabbed">

- <b class="tab-title">Windows</b>
    ```bash
    #starting from root repo
    cd scripts/
    start download-release.bat
    ```

- <b class="tab-title">Linux</b>
    ```bash
    #starting from root repo
    cd scripts/
    sudo bash download-release.sh
    ```

</div>



## Run executable

Starting from the root directory of the program, go to `sidera/bin/os` and run the `sidera` executable file.

<div class="tabbed">

- <b class="tab-title">Windows</b>
    ```bash
    #starting from root repo
    cd sidera/bin/windows
    start sidera.exe
    ```

- <b class="tab-title">Linux</b>
    ```bash
    #starting from root repo
    cd sidera/bin/linux
    ./sidera
    ```

</div>

![](./media/sidera-startup.png)



## How to use sidera application

See the guide at [docs/application-tutorial.md](application-tutorial.md)

