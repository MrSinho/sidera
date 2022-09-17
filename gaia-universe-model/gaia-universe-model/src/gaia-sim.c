#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <shengine/shEngine.h>
#include <shengine/shExport.h>
#include <shecs/shComponents.h>
#include <shlinear-algebra/shEuler.h>
#include <shegui/shEgui.h>

#include <shgui/shgui.h>

#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkDrawLoop.h>

#include <cglm/cglm.h>

#include <gaia-universe-model/gaiaUniverseModel.h>
#include <shthreads/shthreads.h>

#define CENTER_GUI_TEXT_POS_X(text, pos)\
	-(float)strlen(text) * SH_GUI_CHAR_DISTANCE_OFFSET * SH_GUI_WINDOW_TEXT_SIZE / 8.0f + (float)(pos)


uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_start(ShEngine* p_engine) {
	shEngineGuiSetup(p_engine, 512, SH_GUI_THEME_EXTRA_DARK);

	p_engine->p_ext = calloc(1, sizeof(GaiaUniverseModelMemory));
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_ext;

	gaiaSimulationError(
		gaiaGetAvailableHeap(p_engine) == 0,
		return 0;
	);

	p_universe_model->display_interface = 1;

	return 1;
}

uint64_t SH_ENGINE_EXPORT_FUNCTION gaia_thread(GaiaUniverseModelMemory* p_universe_model) {
	//called after gaia_start
	GaiaModelDescriptorInfo descriptor_info = { 0 };
	char descriptor_path[256];
	shMakeAssetsPath("/descriptors/universe-model.json", descriptor_path);

	gaiaSimulationError(
		gaiaReadModelDescriptor(descriptor_path, &descriptor_info) == 0,
		return 0;
	);

	gaiaSimulationError(
		gaiaReadSources(descriptor_info, p_universe_model) == 0,
		return 0;
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_update_pending(ShEngine* p_engine) {
	
	shGuiText(
		p_engine->p_gui,
		SH_GUI_WINDOW_TEXT_SIZE * 2.0f,
		0.0f,
		0.0f,
		"Loading universe model data...",
		SH_GUI_CENTER_WIDTH | SH_GUI_CENTER_HEIGHT
	);

	shGuiText(
		p_engine->p_gui,
		SH_GUI_WINDOW_TEXT_SIZE * 1.0f,
		0.0f,
		-SH_GUI_WINDOW_TEXT_SIZE - 30.0f,
		"Gaia @Aip: gaia.aip.de",
		SH_GUI_CENTER_WIDTH | SH_GUI_CENTER_HEIGHT
	);

	shGuiText(
		p_engine->p_gui,
		SH_GUI_WINDOW_TEXT_SIZE * 1.0f,
		10.0f,
		-10.0f,
		"Sinho softworks: gaia-universe-model",
		SH_GUI_EDGE_LEFT | SH_GUI_EDGE_TOP
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_after_thread(ShEngine* p_engine) {
	//called one time after gaia_thread
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_ext;

	if (p_universe_model->used_gpu_heap == 0) {
		return 1;
	}

	if (p_universe_model->p_pipeline == NULL) {//only the first time the application is loaded
		gaiaSimulationError(
			gaiaBuildPipeline(p_engine, p_universe_model) == 0,
			return 0;
		);
	}

	gaiaSimulationError(
		gaiaWriteMemory(p_engine, p_universe_model) == 0,
		return 0;
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_update(ShEngine* p_engine) {
	//called after end of gaia_after_thread
	ShGui* p_gui                              = p_engine->p_gui;
	ShScene* p_scene                          = &p_engine->scene;
	ShCamera* p_camera                        = shGetShCamera(p_scene, 0);
	ShTransform* p_camera_transform           = shGetShTransform(p_scene, 0);
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_ext;

	shGuiText(
		p_engine->p_gui,
		SH_GUI_WINDOW_TEXT_SIZE * 1.0f,
		-10.0f,
		10.0f,
		"Gaia @Aip: gaia.aip.de",
		SH_GUI_EDGE_RIGHT | SH_GUI_EDGE_BOTTOM
	);

	if (p_universe_model->used_gpu_heap == 0) {

		shGuiText(
			p_engine->p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.0f,
			10.0f,
			-10.0f,
			"Sinho softworks: gaia-universe-model",
			SH_GUI_EDGE_LEFT | SH_GUI_EDGE_TOP
		);

		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 2.0f * (float)p_engine->window.width / 1000.0f,
			0.0f,
			0.0f,
			"gaia-archive-tools error: invalid file data",
			SH_GUI_CENTER_WIDTH | SH_GUI_CENTER_HEIGHT
		);

		return 1;
	}

	if ((shIsKeyPressed(p_engine->window, SH_KEY_ESCAPE))
		|| 
		shIsKeyPressed(p_engine->window, SH_KEY_P)
		) {
		p_universe_model->display_menu = 1 * p_universe_model->display_menu == 0;
	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_R)) {
		p_universe_model->display_quick_menu = 1 * p_universe_model->display_quick_menu == 0;
	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_G)) {
		p_universe_model->display_quick_menu = 1 * p_universe_model->display_quick_menu == 0;
	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_H)) {
		p_universe_model->display_interface = 1 * p_universe_model->display_interface == 0;
	}

	if (p_universe_model->display_menu) {
		p_universe_model->display_quick_menu = 0;

		shGuiWindow(p_gui, 30.0f, 30.0f, 0.0f, 0.0f, "Menu", SH_GUI_MOVABLE | SH_GUI_RELATIVE);
		shGuiWindowSeparator(p_gui);
		shGuiWindowSeparator(p_gui);

		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "Reset position", SH_GUI_CENTER_WIDTH)) {
			p_camera_transform->position[0] = 0.0f;
			p_camera_transform->position[1] = 0.0f;
			p_camera_transform->position[2] = 0.0f;
			p_universe_model->display_menu = 0;
		}
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "Reset orientation", SH_GUI_CENTER_WIDTH)) {
			p_camera_transform->rotation[0] = 0.0f;
			p_camera_transform->rotation[1] = 0.0f;
			p_camera_transform->rotation[2] = 0.0f;
			p_universe_model->display_menu = 0;
		}
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE , "Reset zoom", SH_GUI_CENTER_WIDTH)) {
			p_camera->fov = 45.0f;
			p_universe_model->display_menu = 0;
		}
		shGuiWindowSeparator(p_gui);
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE, "Reload resources", SH_GUI_CENTER_WIDTH)) {
			shResetEngineState(p_engine, 0);
		}
	}
	else if (p_universe_model->display_quick_menu) {
		p_universe_model->display_menu = 0;
		shGuiWindow(
			p_gui,
			30.0f,
			30.0f,
			0.0f,
			0.0f,
			"Go to",
			SH_GUI_RELATIVE
		);
		shGuiWindowSeparator(p_gui);

		shGuiWindowSeparator(p_gui);
		shGuiWindowButton(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE,
			"Confirm",
			SH_GUI_CENTER_WIDTH
		);
	}
	else if (p_universe_model->display_interface) {

		shGuiText(
			p_gui, 
			SH_GUI_WINDOW_TEXT_SIZE * 1.0f, 
			10.0f,
			 -10.0f, 
			"Position UA:",
			SH_GUI_EDGE_TOP | SH_GUI_EDGE_LEFT
		);
		shGuiText(
			p_gui, 
			SH_GUI_WINDOW_TEXT_SIZE * 1.0f, 
			10.0f,
			10.0f, 
			"RA DEC:",
			SH_GUI_EDGE_LEFT | SH_GUI_EDGE_BOTTOM
		);

		char pos[64];
		sprintf(pos, "%.10f, %.10f, %.10f", p_camera_transform->position[0], -p_camera_transform->position[1], p_camera_transform->position[2]);
		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
			0.0f,
			-10.0f,
			pos,
			SH_GUI_CENTER_WIDTH | SH_GUI_EDGE_TOP
		);

		char ra_dec[64];
		float camera_ra = p_camera_transform->euler[1];
		float camera_dec = -p_camera_transform->euler[0];
		sprintf(ra_dec, "%.10f, %.10f", camera_ra, camera_dec);
		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
			0.0f,
			10.0f,
			ra_dec,
			SH_GUI_CENTER_WIDTH | SH_GUI_EDGE_BOTTOM
		);

		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.0f, 
			0.0f,
			0.0f,
			"+",
			SH_GUI_CENTER_WIDTH | SH_GUI_CENTER_HEIGHT
		);

		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
			0.0f,
			0.0f,
			"--",
			SH_GUI_EDGE_LEFT | SH_GUI_CENTER_HEIGHT
		);

		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
			0.0f,
			0.0f,
			"--",
			SH_GUI_EDGE_RIGHT | SH_GUI_CENTER_HEIGHT
		);


		char fov[32];
		sprintf(fov, "FOV: %.3f", p_camera->fov);
		shGuiText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.0f,
			-10.0f,
			-10.0f,
			fov,
			SH_GUI_EDGE_TOP | SH_GUI_EDGE_RIGHT
		);
		

		//cursor coords
		if (!p_universe_model->display_gui && !p_universe_model->display_quick_menu) {
			char cursor_ra_dec[64];
			float cursor_ra = p_engine->window.input.cursor_pos_x;
			float cursor_dec = p_engine->window.input.cursor_pos_x;
		
			sprintf(cursor_ra_dec, "%.2f, %.2f px", cursor_ra, cursor_dec);
			shGuiText(
				p_gui,
				SH_GUI_WINDOW_TEXT_SIZE / 1.0f,
				p_engine->window.input.cursor_pos_x,
				-p_engine->window.input.cursor_pos_y - SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
				cursor_ra_dec,
				SH_GUI_CENTER_WIDTH | SH_GUI_CENTER_HEIGHT
			);
		}
	}
	


	float d_time = (float)p_engine->time.delta_time;
	float fov_scale = 75.0f;

	float d = (75.01f + p_camera->fov - fov_scale) / 200.0f * d_time;

	if (shIsKeyDown(p_engine->window, SH_KEY_LEFT)) {
		p_camera_transform->rotation[1] -= d;
	}
	if (shIsKeyDown(p_engine->window, SH_KEY_RIGHT)) {
		p_camera_transform->rotation[1] += d;
	}
	if (shIsKeyDown(p_engine->window, SH_KEY_UP)) {
		p_camera_transform->rotation[0] -= d;
	}
	if (shIsKeyDown(p_engine->window, SH_KEY_DOWN)) {
		p_camera_transform->rotation[0] += d;
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

	if (shIsKeyDown(p_engine->window, SH_KEY_Z)) {
		if (p_camera->fov > 0.01f) {
			p_camera->fov -= p_camera->fov / 2.0f * d_time;
		}
		else {
			p_camera->fov = 0.01f;
		}
	}
	else if (shIsKeyDown(p_engine->window, SH_KEY_X)) {
		if (p_camera->fov < 160.0f) {
			p_camera->fov += p_camera->fov / 2.0f * d_time;
		}
		else {
			p_camera->fov = 160.0f;
		}
	}

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_frame_update(ShEngine* p_engine) {
	//called after end of gaia_thread
	ShMaterialHost*				p_material			= &p_engine->p_materials[0];
	VkCommandBuffer				cmd_buffer			= p_engine->core.p_graphics_commands[0].cmd_buffer;
	GaiaUniverseModelMemory*	p_universe_model	= p_engine->p_ext;
	
	ShScene*					p_scene				= &p_engine->scene;
	ShTransform*				p_camera_transform	= shGetShTransform(p_scene, 0);
	ShCamera*					p_camera			= shGetShCamera(p_scene, 0);
	
	if (p_universe_model->used_gpu_heap == 0) {
		return 1;
	}
	
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

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_frame_resize(ShEngine* p_engine) {
	//pipeline has been released
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_ext;

	if (p_universe_model->used_gpu_heap == 0) {
		return 1;
	}

	gaiaSimulationError(
		gaiaBuildPipeline(p_engine, p_engine->p_ext) == 0,
		return 0;
	);

	gaiaSimulationError(
		gaiaWriteMemory(p_engine, p_engine->p_ext) == 0,
		return 0;
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_close(ShEngine* p_engine) {
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_ext;

	if (p_universe_model != NULL) {
		if (p_universe_model->p_celestial_bodies != NULL) {
			free(p_universe_model->p_celestial_bodies);
		}
		free(p_universe_model);
	}

	return 1;
}



#ifdef __cplusplus
}
#endif//__cplusplus