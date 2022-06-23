#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <shengine/shEngine.h>
#include <shengine/shExport.h>
#include <shecs/shComponents.h>

#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkDrawLoop.h>

#include <gaia-universe-model/gaiaUniverseModel.h>

#include <math.h>

#define GAIA_UNIVERSE_ENTITY 1



void SH_ENGINE_EXPORT_FUNCTION gaia_start(ShEngine* p_engine) {

	p_engine->p_engine_extension = calloc(1, sizeof(GaiaUniverseModelMemory));
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_engine_extension;

	GaiaCelestialBodyFlags flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;

	gaiaError(
		gaiaReadSources(p_engine, GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF, p_universe_model) == 0,
		"failed reading source files",
		return
	);
	p_universe_model->celestial_body_size = gaiaGetBodySize(flags);

	gaiaWriteVertexBuffers(p_engine, p_universe_model);
}

void SH_ENGINE_EXPORT_FUNCTION gaia_update(ShEngine* p_engine) {
	
	ShMaterialHost*				p_material			= &p_engine->p_materials[0];
	VkCommandBuffer				cmd_buffer			= p_engine->core.p_graphics_commands[0].cmd_buffer;
	GaiaUniverseModelMemory*	p_universe_model	= p_engine->p_engine_extension;
	
	ShScene*					p_scene				= &p_engine->scene;
	ShTransform*				p_camera_transform	= shGetShTransform(p_scene, 0);
	ShCamera*					p_camera			= shGetShCamera(p_scene, 0);

	shBindPipeline(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, &p_material->pipeline);
	
	float p_const[32];
	memcpy(p_const, p_camera->projection, 64);
	memcpy(&((char*)p_const)[64], p_camera->view, 64);
	shPipelinePushConstants(cmd_buffer, p_const, &p_material->pipeline);

	shPipelineUpdateDescriptorSets(p_engine->core.device, &p_material->pipeline);

	shPipelineWriteDescriptorBufferMemory(p_engine->core.device, 0, p_camera_transform->position, &p_material->pipeline);
	shPipelineBindDescriptorSet(cmd_buffer, 0, VK_PIPELINE_BIND_POINT_GRAPHICS, &p_material->pipeline);

	shBindVertexBuffers(cmd_buffer, 0, p_universe_model->vertex_buffer_count, p_universe_model->vertex_buffers);

	shEndPipeline(&p_material->pipeline);

	
	shDraw(cmd_buffer, p_universe_model->used_gpu_heap / p_universe_model->celestial_body_size);

}

void SH_ENGINE_EXPORT_FUNCTION gaia_close(ShEngine* p_engine) {
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_engine_extension;

	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		shClearBufferMemory(p_engine->core.device, p_universe_model->vertex_buffers[i], p_universe_model->vertex_buffers_memory[i]);
	}

	if (p_universe_model != NULL) {
		free(p_engine->p_engine_extension);
	}
}



#ifdef __cplusplus
}
#endif//__cplusplus