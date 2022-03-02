#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include <stdint.h>
#include <gaia-universe-model/gaiaUniverseModel.h>

int main(void) {
	//ENGINE SETUP
	ShEngine engine = { 0 };
	gaiaEngineSetup(&engine);

	//SETUP MAIN MATERIAL
	GaiaUniverseModelMemory universe_model = { 0 };
	gaiaSetupMaterial(&engine, "../shaders/bin/celestialBody.vert.spv", "../shaders/bin/celestialBody.frag.spv", &universe_model);
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

		//UPDATE FRAME
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

#ifdef __cplusplus
}
#endif//__cplusplus