#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifndef GAIA_UNIVERSE_MODEL_H
#define GAIA_UNIVERSE_MODEL_H



#include <gaia-archive-tools/gaiaArchiveTools.h>

#include <shvulkan/shVkPipelineData.h>
#include <shthreads/shthreads.h>

typedef struct GaiaUniverseModelMemory {
	uint32_t         used_gpu_heap;
	void*            p_celestial_bodies;
	uint32_t         celestial_body_size;
	GaiaCelestialBodyFlags         celestial_body_flags;
	uint32_t         max_buffer_memory;
	uint32_t         available_video_memory;
	ShVkPipeline*    p_pipeline;
	ShVkFixedStates* p_fixed_states;
	uint8_t          display_gui;
	uint8_t          display_menu;
	uint8_t          display_interface;
	uint8_t          display_quick_menu;
} GaiaUniverseModelMemory;


typedef struct GaiaModelDescriptorInfo {
	uint32_t source_start;
	uint32_t source_end;
} GaiaModelDescriptorInfo;



#define gaiaSimulationError(condition, failure_expression)\
	if ((int)(condition)) {\
		return 0;\
	}\



extern uint8_t gaiaReadModelDescriptor(const char* path, GaiaModelDescriptorInfo* p_descriptor_info);

extern uint8_t gaiaGetAvailableHeap(ShEngine* p_engine);

extern uint8_t gaiaReadSources(GaiaModelDescriptorInfo descriptor_info, GaiaUniverseModelMemory* p_model);

extern uint8_t gaiaBuildPipeline(ShEngine* p_engine, GaiaUniverseModelMemory* p_model);

extern uint8_t gaiaWriteMemory(ShEngine* p_engine, GaiaUniverseModelMemory* p_model);

#define gaiaMemoryRelease(p_universe_model)\
	free((p_universe_model)->p_celestial_bodies)\



#endif//GAIA_UNIVERSE_MODEL_H

#ifdef __cplusplus
}
#endif//__cplusplus