#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <shengine/shEngine.h>



#include <gaia-universe-model/gaiaUniverseModel.h>



uint8_t gaiaReadSources(ShEngine* p_engine, const GaiaCelestialBodyFlags celestial_body_flags, GaiaUniverseModelMemory* p_universe_model) {
	gaiaError(p_engine == NULL, "invalid engine memory", return 0);
	gaiaError(p_universe_model == NULL, "invalid universe model memory", return 0);

	uint32_t available_video_memory = 0;
	shGetMemoryBudgetProperties(p_engine->core.physical_device, &available_video_memory, NULL, NULL);
	available_video_memory /= 20;
	p_universe_model->p_celestial_bodies = calloc(1, available_video_memory);
	gaiaError(p_universe_model->p_celestial_bodies == NULL, "invalid celestial bodies memory", return 0);
	
	for (uint32_t i = 0; i < 25; i++) {
		for (uint8_t half = 0; half < 2; half++) {
			uint32_t bytes_read = 0;
			void* p_src = NULL;
			gaiaError(
				gaiaReadBinaryFileFromID("../../../gaia-resources/", i, half, celestial_body_flags, 0, 0, &bytes_read, &p_src) == 0,
				"failed reading source file",
				return 0;
			);
			if (p_universe_model->used_gpu_heap + bytes_read >= available_video_memory) {
				break;
			}
			memcpy(&((char*)p_universe_model->p_celestial_bodies)[p_universe_model->used_gpu_heap], p_src, bytes_read);
			p_universe_model->used_gpu_heap += bytes_read;
			gaiaFree(p_src);
		}
		
	}

	return 1;
}

uint8_t gaiaWriteVertexBuffers(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	gaiaError(p_engine == NULL, "invalid engine memory", return 0);
	gaiaError(p_universe_model == NULL, "invalid universe model memory", return 0);

	const uint32_t MAX_GPU_HEAP_SIZE = 67108864;
	uint32_t written_memory = 0;

	p_universe_model->vertex_buffer_count = (p_universe_model->used_gpu_heap > MAX_GPU_HEAP_SIZE) ? (p_universe_model->used_gpu_heap / MAX_GPU_HEAP_SIZE) : 1;
	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		uint32_t buffer_size = p_universe_model->used_gpu_heap > MAX_GPU_HEAP_SIZE ? MAX_GPU_HEAP_SIZE : p_universe_model->used_gpu_heap;

		shCreateVertexBuffer(p_engine->core.device, buffer_size, &p_universe_model->vertex_buffers[i]);

		shAllocateVertexBufferMemory(p_engine->core.device, p_engine->core.physical_device, p_universe_model->vertex_buffers[i], &p_universe_model->vertex_buffers_memory[i]);

		shWriteVertexBufferMemory(p_engine->core.device, p_universe_model->vertex_buffers_memory[i], 0, buffer_size, &((char*)p_universe_model->p_celestial_bodies)[written_memory]);
		
		shBindVertexBufferMemory(p_engine->core.device, p_universe_model->vertex_buffers[i], 0, p_universe_model->vertex_buffers_memory[i]);

		written_memory += buffer_size;
		if (written_memory >= p_universe_model->used_gpu_heap) { break; }
	}

	return 1;
}

uint8_t gaiaMemoryRelease(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	gaiaError(p_engine == NULL, "invalid engine memory", return 0);
	gaiaError(p_universe_model == NULL, "invalid universe model memory", return 0);
	free(p_universe_model->p_celestial_bodies);
	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		shClearBufferMemory(p_engine->core.device, p_universe_model->vertex_buffers[i], p_universe_model->vertex_buffers_memory[i]);
	}
	return 1;
}



#ifdef __cplusplus
}
#endif//__cplusplus