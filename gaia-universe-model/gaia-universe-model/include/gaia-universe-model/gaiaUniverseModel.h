#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifndef GAIA_UNIVERSE_MODEL_H
#define GAIA_UNIVERSE_MODEL_H



#include <gaia-archive-tools/gaiaArchiveTools.h>



typedef struct GaiaUniverseModelMemory {
	uint32_t		used_gpu_heap;
	void*			p_celestial_bodies;
	uint32_t		celestial_body_size;
	uint32_t		vertex_buffer_count;
	VkBuffer		vertex_buffers[64];
	VkDeviceMemory	vertex_buffers_memory[64];
} GaiaUniverseModelMemory;



uint8_t gaiaReadSources(ShEngine* p_engine, const GaiaCelestialBodyFlags celestial_body_flags, GaiaUniverseModelMemory* p_universe_model);

uint8_t gaiaWriteVertexBuffers(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

uint8_t gaiaMemoryRelease(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);


#endif//GAIA_UNIVERSE_MODEL_H

#ifdef __cplusplus
}
#endif//__cplusplus