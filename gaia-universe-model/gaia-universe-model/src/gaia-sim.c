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



uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_start(ShEngine* p_engine) {

	p_engine->p_engine_extension = calloc(1, sizeof(GaiaUniverseModelMemory));
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_engine_extension;

	GaiaCelestialBodyFlags flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;


	GaiaModelDescriptorInfo descriptor_info = { 0 };
	char descriptor_path[256];
	shMakeAssetsPath("/descriptors/universe-model.json", descriptor_path);
	
	
	gaiaSimulationError(
		p_engine,
		gaiaReadModelDescriptor(descriptor_path, &descriptor_info) == 0,
		return 0;
	);

	gaiaSimulationError(
		p_engine,
		gaiaReadSources(p_engine, GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF, descriptor_info, p_universe_model) == 0,
		return 0;
	);

	gaiaSimulationError(
		p_engine,
		gaiaBuildPipeline(p_engine, p_universe_model) == 0,
		return 0;
	);

	gaiaSimulationError(
		p_engine,
		gaiaWriteMemory(p_engine, p_universe_model) == 0,
		return 0;
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_update(ShEngine* p_engine) {
	
	ShMaterialHost*				p_material			= &p_engine->p_materials[0];
	VkCommandBuffer				cmd_buffer			= p_engine->core.p_graphics_commands[0].cmd_buffer;
	GaiaUniverseModelMemory*	p_universe_model	= p_engine->p_engine_extension;
	
	ShScene*					p_scene				= &p_engine->scene;
	ShTransform*				p_camera_transform	= shGetShTransform(p_scene, 0);
	ShCamera*					p_camera			= shGetShCamera(p_scene, 0);


	shBindPipeline(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, &p_material->pipeline);
	
	{
		if (shIsKeyPressed(p_engine->window, SH_KEY_1)) {
			p_camera->speed = 1.0f;
		}
		if (shIsKeyPressed(p_engine->window, SH_KEY_2)) {
			p_camera->speed = 10.0f;
		}
		if (shIsKeyPressed(p_engine->window, SH_KEY_2)) {
			p_camera->speed = 50.0f;
		}
		if (shIsKeyPressed(p_engine->window, SH_KEY_3)) {
			p_camera->speed = 100.0f;
		}
		if (shIsKeyPressed(p_engine->window, SH_KEY_4)) {
			p_camera->speed = 200.0f;
		}
		if (shIsKeyPressed(p_engine->window, SH_KEY_5)) {
			p_camera->speed = 500.0f;
		}
	}

	{
		float p_const[32];
		memcpy(p_const, p_camera->projection, 64);
		memcpy(&((char*)p_const)[64], p_camera->view, 64);
		shPipelinePushConstants(cmd_buffer, p_const, &p_material->pipeline);
	}

	shPipelineUpdateDescriptorSets(p_engine->core.device, &p_material->pipeline);

	{//CAMERA
		shPipelineWriteDescriptorBufferMemory(p_engine->core.device, 1, p_camera_transform->position, &p_material->pipeline);
	}//CAMERA

	shPipelineBindDescriptorSets(cmd_buffer, 0, p_material->pipeline.descriptor_count, VK_PIPELINE_BIND_POINT_GRAPHICS, &p_material->pipeline);

	shEndPipeline(&p_material->pipeline);
	
	shDraw(cmd_buffer, p_universe_model->used_gpu_heap / p_universe_model->celestial_body_size);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_close(ShEngine* p_engine) {
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_engine_extension;

	if (p_universe_model != NULL) {
		free(p_engine->p_engine_extension);
	}

	return 1;
}



#ifdef __cplusplus
}
#endif//__cplusplus