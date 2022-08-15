#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <shengine/shEngine.h>
#include <shengine/shExport.h>
#include <shecs/shComponents.h>
#include <shlinear-algebra/shEuler.h>

#include <shgui/shgui.h>


#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkDrawLoop.h>



#include <gaia-universe-model/gaiaUniverseModel.h>




uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_start(ShEngine* p_engine) {

	p_engine->p_engine_extension = calloc(1, sizeof(GaiaUniverseModelMemory));
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_engine_extension;

	GaiaCelestialBodyFlags flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;


	GaiaModelDescriptorInfo descriptor_info = { 0 };
	char descriptor_path[256];
	shMakeAssetsPath("/descriptors/universe-model.json", descriptor_path);
	
	
	gaiaSimulationError(
		gaiaReadModelDescriptor(descriptor_path, &descriptor_info) == 0,
		return 0;
	);

	gaiaSimulationError(
		gaiaReadSources(p_engine, GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF, descriptor_info, p_universe_model) == 0,
		return 0;
	);

	gaiaSimulationError(
		gaiaBuildPipeline(p_engine, p_universe_model) == 0,
		return 0;
	);

	gaiaSimulationError(
		gaiaWriteMemory(p_engine, p_universe_model) == 0,
		return 0;
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_update(ShEngine* p_engine) {

	GaiaUniverseModelMemory* p_universe_model = p_engine->p_engine_extension;
	ShGui* p_gui = p_engine->p_gui;
	ShScene* p_scene = &p_engine->scene;
	ShCamera* p_camera = shGetShCamera(p_scene, 0);
	ShTransform* p_camera_transform = shGetShTransform(p_scene, 0);


	if ((shIsKeyPressed(p_engine->window, SH_KEY_ESCAPE))
		|| 
		shIsKeyPressed(p_engine->window, SH_KEY_P)
		) {
		p_universe_model->display_menu = 1 * p_universe_model->display_menu == 0;
	}

	if (p_universe_model->display_menu) {
		shGuiWindow(p_gui, 300.0f, 200.0f, 0.0f, 0.0f, "Settings", SH_GUI_PIXELS | SH_GUI_RESIZABLE);
		shGuiWindowSeparator(p_gui);
		shGuiWindowText(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "Model size", 0);
		shGuiWindowSeparator(p_gui);
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "Low (10.000.000 stars)", SH_GUI_CENTER_WIDTH)) {
			puts("Reloading universe model");//0-10
			return 0;
		}
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "Medium (50.000.000 stars)", SH_GUI_CENTER_WIDTH)) {
			puts("Reloading universe model");//0-50
			return 0;
		}
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "High (150.000.000 stars)", SH_GUI_CENTER_WIDTH)) {
			puts("Reloading universe model");//0-150
			return 0;
		}
	}
	else {
		shGuiText(p_gui, SH_GUI_WINDOW_TEXT_SIZE, SH_GUI_CHAR_DISTANCE_OFFSET - (float)p_engine->window.width / 2.0f, (float)p_engine->window.height / 2.0f - SH_GUI_WINDOW_TEXT_SIZE, "Position UA:");
		shGuiText(p_gui, SH_GUI_WINDOW_TEXT_SIZE, SH_GUI_CHAR_DISTANCE_OFFSET - (float)p_engine->window.width / 2.0f,-(float)p_engine->window.height / 2.0f + SH_GUI_WINDOW_TEXT_SIZE / 2.0f, "RA DEC:");

		char pos[64];
		sprintf(pos, "%.10f, %.10f, %.10f", p_camera_transform->position[0], -p_camera_transform->position[1], p_camera_transform->position[2]);
		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE,
			-(float)strlen(pos) * SH_GUI_CHAR_DISTANCE_OFFSET * SH_GUI_WINDOW_TEXT_SIZE / 8.0f,
			(float)p_engine->window.height / 2.0f - SH_GUI_WINDOW_TEXT_SIZE,
			pos
		);

		shGuiText(p_gui, SH_GUI_WINDOW_TEXT_SIZE, -(float)p_engine->window.width / 2.0f, -(float)p_engine->window.width / 2.0f, "RA, DEC:");
		
		char ra_dec[64];
		sprintf(ra_dec, "%.10f, %.10f", p_camera_transform->euler[1], -p_camera_transform->euler[0]);
		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE,
			-(float)strlen(ra_dec) * SH_GUI_CHAR_DISTANCE_OFFSET * SH_GUI_WINDOW_TEXT_SIZE / 8.0f,
			(-(float)p_engine->window.height + SH_GUI_WINDOW_TEXT_SIZE) / 2.0f,
			ra_dec
		);
	}
	
	{
		double d_time = p_engine->time.delta_time;

		if (shIsKeyDown(p_engine->window, SH_KEY_LEFT)) {
			p_camera_transform->rotation[1] -= 0.2f * (float)d_time;
		}
		if (shIsKeyDown(p_engine->window, SH_KEY_RIGHT)) {
			p_camera_transform->rotation[1] += 0.2f * (float)d_time;
		}
		if (shIsKeyDown(p_engine->window, SH_KEY_UP)) {
			p_camera_transform->rotation[0] -= 0.2f * (float)d_time;
		}
		if (shIsKeyDown(p_engine->window, SH_KEY_DOWN)) {
			p_camera_transform->rotation[0] += 0.2f * (float)d_time;
		}
		if (p_camera_transform->rotation[0] >= SH_DEGREES_TO_RADIANS(89.99999f)) {
			p_camera_transform->rotation[0] = SH_DEGREES_TO_RADIANS(89.99999f);
		}
		if (p_camera_transform->rotation[0] <= SH_DEGREES_TO_RADIANS(-89.99999f)) {
			p_camera_transform->rotation[0] = SH_DEGREES_TO_RADIANS (-89.99999f);
		}

		if (shIsKeyPressed(p_engine->window, SH_KEY_0)) {
			p_camera->speed = 0.1f;
		}
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

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_frame_update(ShEngine* p_engine) {
	
	ShMaterialHost*				p_material			= &p_engine->p_materials[0];
	VkCommandBuffer				cmd_buffer			= p_engine->core.p_graphics_commands[0].cmd_buffer;
	GaiaUniverseModelMemory*	p_universe_model	= p_engine->p_engine_extension;
	
	ShScene*					p_scene				= &p_engine->scene;
	ShTransform*				p_camera_transform	= shGetShTransform(p_scene, 0);
	ShCamera*					p_camera			= shGetShCamera(p_scene, 0);

	shBindPipeline(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, &p_material->pipeline);

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