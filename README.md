# Gaia Universe Model Library Walkthrough

<button>[index](./index.md)</button>

Setup
* [Clone and build](#clone-and-build)
* [Download Universe Model Data](#download-universe-model-data)

Tutorial
* [Use CMake](#use-cmake)
* [Example](#example)

---

# Setup

## Clone and Build

Open the terminal and run the following commands:
```bash
git clone --recursive https://github.com/MrSinho/Gaia_Universe_Model.git
cd Gaia_Universe_Model
mkdir build
cd build
cmake ..
cmake --build .
```

## Download Universe Model Data

Inside the cloned repository directory download the GEDR3 binaries by executing one of the scripts shown below: 
```bash
#For Linux devices
./download_resources.sh
#For Windows devices
./download_resources.bat
```

# Tutorial

## Use CMake

| CMake target                                           | type       |
|--------------------------------------------------------|------------|
| [shvulkan](../ShVulkan/index.md)                       | library    |
| [shengine](../ShEngine/index.md)                       | library    |
| [gaia-archive-tools](../Gaia_Archive_Tools/index.md)   | library    |
| [gaia-universe-model](../Gaia_Universe_Model/index.md) | library    |
| gaia-universe-model-simulation                         | executable |

`gaia-universe-model-simulation` is a real time simulation, thus it needs all the libraries written on the table above.

## Example
```c
//Located at "repo-dir/GaiaUniverseModel/gaia-universe-model-simulation/src/main.c"
#include <stdint.h>
#include <gaia-universe-model/gaiaUniverseModel.h>

int main(void) {
	//ENGINE SETUP
	ShEngine engine = { 0 };
	gaiaEngineSetup(&engine);

	//SETUP MAIN MATERIAL
	GaiaUniverseModelMemory universe_model = { 0 };
	gaiaSetupMaterial(&engine, &universe_model);
	assert(engine.p_materials != NULL);

	uint64_t celestial_body_flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;
	const uint32_t CELESTIAL_BODY_SIZE = gaiaGetBodySize(celestial_body_flags);

	//GET AVAILABLE MEMORY
	//READ SOURCE FILES
	gaiaReadSources(&engine, celestial_body_flags, &universe_model);

	//WRITE VERTEX BUFFER MEMORY
	gaiaWriteVertexBuffers(&engine, &universe_model);

	//CREATE SCENE
	gaiaSceneSetup(&engine);

	while (shIsWindowActive(engine.window.window)) {
		//UPDATE WINDOW
		shUpdateWindow(&engine);

		//BEGIN FRAME
		shFrameReset(&engine.core);
		uint32_t frame_index = 0;
		shFrameBegin(&engine.core, &frame_index);

		//UPDATE SCENE AND START DRAWING
		gaiaSceneUpdate(&engine, &universe_model);
		shDraw(&engine.core, universe_model.used_vram / CELESTIAL_BODY_SIZE);

		//END FRAME
		shEndPipeline(&engine.p_materials[0].pipeline);
		shFrameEnd(&engine.core, frame_index);
	}

	gaiaMemoryRelease(&engine, &universe_model);
	gaiaEngineShutdown(&engine);
	return 0;
}
```