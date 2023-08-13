# Install gaia-universe-model using terminal

---

## 1. Clone and build (cmake)

To generate the CMake targets, open the terminal with admin/root permission and run the following commands:

```bash
git clone --recursive https://github.com/MrSinho/gaia-universe-model.git
cd gaia-universe-model
cd external/shengine
python export-application.py name=gaia-universe-model target=EXECUTABLE path=../../gaia-universe-model
```

if you get a python syntax error, try specifying the python version (must be 3.0 or greater).

![](/docs/media/mass_feh_age_polar__agecf.png)


On Windows:
```bash
cd scripts
start download-release.bat
cd ../
cd gaia-universe-model/windows/build
cmake --build .
```
The windows binaries are compiled at gaia-universe-model/windows/bin

On Linux:
```bash
cd scripts
start download-release.sh
cd ../
cd gaia-universe-model/linux/build
cmake --build .
```

The linux binaries are compiled at gaia-universe-model/linux/bin

---

## 2. Move ini file

The engine needs to know where to locate the universe model assets path, and some general properties of the application: 

On Windows:

```bash
#starting from root repo
cd gaia-universe-model/
cp ini.smd windows/bin/ini.smd
```

On Linux:

```bash
#starting from root repo
cd gaia-universe-model/
cp ini.smd linux/bin/ini.smd
```

![](/docs/media/age_mass_feh__fehcf_cartesian.png)

---

## 3. Download Gaia Data Release binaries

> Note: the following step needs a python3.11+ interpreter to be already installed in your system.

Now navigate to the installation path and find the `scripts` directory and run the `download-release` batch/shell script:

On Windows:

```bash
#starting from root repo
cd scripts/
start download-release.bat
```

On Linux:

```bash
#starting from root repo
cd scripts/
sudo bash download-release.sh
```

---

## 4. Run executable

Starting from the root directory of the program, go to `gaia-universe-model/os/bin` and run the `gaia-universe-model` executable file.

```bash
#starting from root repo
cd gaia-universe-model/windows/bin
start gaia-universe-model.exe
```

On Linux:

```bash
#starting from root repo
cd gaia-universe-model/linux/bin
./gaia-universe-model
```

![](/docs/media/gaia-universe-model-startup.png)

---

## 5. How to use gaia-universe-model application

See the guide at [docs/runtime-tutorial.md](/docs/runtime-tutorial.md)

---