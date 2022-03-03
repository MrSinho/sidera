#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include <engine/shEngine.h>
#include <shvulkan/shVkDrawLoop.h>
#include <gaia-archive-tools/gaiaArchiveTools.h>


typedef struct GaiaUniverseModelMemory {
	ShMaterialHost	materials[1];
	uint32_t		used_vram;
	void*			p_celestial_bodies;
	uint32_t		vertex_buffer_count;
	VkBuffer		vertex_buffers[64];
	VkDeviceMemory	vertex_buffers_memory[64];
	void*			push_constant[128 / sizeof(void*)];
	void*			uniform_buffer[16 / sizeof(void*)];
} GaiaUniverseModelMemory;



extern void gaiaEngineSetup(ShEngine* p_engine);

extern const char* gaiaReadBinaryGeneric(const char* path, uint32_t* p_size);

extern void gaiaSetupMaterial(ShEngine* p_engine, const char* vertex_shader_path, const char* fragment_shader_path, GaiaUniverseModelMemory* p_universe_model);

extern void gaiaReadSources(ShEngine* p_engine, const GaiaCelestialBodyFlags celestial_body_flags, GaiaUniverseModelMemory* p_universe_model);

extern void gaiaWriteVertexBuffers(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

extern void gaiaSceneSetup(ShEngine* p_engine);

extern void gaiaSceneUpdate(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

extern void gaiaMemoryRelease(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

extern void gaiaEngineShutdown(ShEngine* p_engine);

#ifdef __cplusplus
}
#endif//__cplusplus