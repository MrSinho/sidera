# gaia-universe-model

# MAJOR COMMITS COMING SOON WITH MANY IMPROVEMENTS AND NEW FEATURES

[![linux_badge](.shci/linux-exit_code.svg)](.shci/linux-log.md)
[![windows_badge](.shci/windows-exit_code.svg)](.shci/windows-log.md)

https://user-images.githubusercontent.com/68569053/185792534-b0a95fb5-9232-4683-92a3-2c87fabf2909.mp4

# [Online documentation](https://mrsinho.github.io/docs/gaia-universe-model/index)

# To do
* Load data from cloud
* Gaia Launcher
	* 3d simulation
		* Build HR diagram
		* Alpha blend (shengine and shvulkan specific)
		* Grids
		* Find a way to render interstellar matter
	* Gaia hub
		* Time warp
		* Star search
			* When selected, point to the star and display info
		* Scale galaxy
		* 3d rendering settings
			* Brightness saturation radius
			* Pick pipeline
		* Navigate to a specific region from menu
	* Instead of creating gui, manually update a json file
		* then press ALT-R to reload what's needed

https://user-images.githubusercontent.com/68569053/185792548-ab8d8614-f213-44b6-a572-1aa5f4ccc656.mp4


- [Setup](#setup)
	* [Clone and build](#clone-and-build)
	* [Generate CMake targets](#generate-cmake-targets)
	* [Build](#build)

- [Testing](#testing)


---


# Setup

## Clone and Build

Open the terminal and run the following commands:

### Generate cmake targets

```bash
git clone --recursive https://github.com/MrSinho/gaia-universe-model.git
cd gaia-universe-model
cd external/shengine
python export-application.py gaia-universe-model EXECUTABLE ../../gaia-universe-model
```

if you get a python syntax error specify the python version (must be 3.0 or greater).

![](saved/screenshot_0.jpg)

### Build

On Windows:
```bash
cd gaia-universe-model/windows/build
cmake --build .
```
The windows binaries are compiled at gaia-universe-model/windows/bin

On Linux:
```bash
cd gaia-universe-model/linux/build
cmake --build .
```
The linux binaries are compiled at gaia-universe-model/linux/bin

# Testing

![](saved/screenshot_3.png)

Go to `external/shengine/bin` and run the executable named `sheditor`.
To move use the `WASD` keys and set the camera speed with `012345`.
