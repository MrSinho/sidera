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



#define GAIA_UNIVERSE_MODEL_DESCRIPTOR_DIR      "/descriptors/"
#define GAIA_UNIVERSE_MODEL_DESCRIPTOR_FILENAME "/universe-model.json"


uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_start(ShEngine* p_engine) {
	shEngineGuiSetup(p_engine, 512, SH_GUI_THEME_EXTRA_DARK);

	p_engine->p_ext = calloc(1, sizeof(GaiaUniverseModelMemory));
	GaiaUniverseModelMemory* p_universe_model = p_engine->p_ext;

	gaiaSimulationError(
		gaiaGetAvailableHeap(p_engine) == 0,
		return 0;
	);

	shAppendAssetsPath(
		p_engine->loader_ini.assets_path, 
		GAIA_UNIVERSE_MODEL_DESCRIPTOR_DIR,
		GAIA_UNIVERSE_MODEL_DESCRIPTOR_FILENAME,
		&p_universe_model->descriptor_info.descriptor
	);
	
	p_universe_model->display_ui = GAIA_DISPLAY_NAV_INTERFACE;


	return 1;
}

uint64_t SH_ENGINE_EXPORT_FUNCTION gaia_thread(GaiaUniverseModelMemory* p_universe_model) {
	//called after gaia_start

	gaiaSimulationError(
		gaiaReadModelDescriptor(p_universe_model->descriptor_info.descriptor.path, &p_universe_model->descriptor_info) == 0,
		return 0;
	);
	p_universe_model->resource_count = p_universe_model->descriptor_info.source_end - p_universe_model->descriptor_info.source_start;
	p_universe_model->resource_countf = (float)p_universe_model->resource_count;

	gaiaSimulationError(
		gaiaReadSources(p_universe_model->descriptor_info, p_universe_model) == 0,
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

	if (shIsKeyPressed(p_engine->window, SH_KEY_ESCAPE)) {
		if ((p_universe_model->display_ui & GAIA_DISPLAY_MENU) == 0) {
			p_universe_model->display_ui |= GAIA_DISPLAY_MENU;
		}
		else {
			p_universe_model->display_ui &= ~GAIA_DISPLAY_MENU;
		}
	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_H)) {
		if ((p_universe_model->display_ui & GAIA_DISPLAY_NAV_INTERFACE) == 0) {
			p_universe_model->display_ui |= GAIA_DISPLAY_NAV_INTERFACE;
		}
		else {
			p_universe_model->display_ui &= ~GAIA_DISPLAY_NAV_INTERFACE;
		}
	}
	if (p_universe_model->display_ui & GAIA_DISPLAY_MENU) {
		
		shGuiWindow(
			p_gui, 
			500.0f, 
			350.0f, 
			0.0f, 
			0.0f, 
			"Menu", 
			SH_GUI_PIXELS
		);
		
		shGuiWindowText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE,
			"",
			0
		);

		//if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE * 1.5f, " Gaia hub          ", SH_GUI_CENTER_WIDTH)) {
		//
		//}
		//
		//shGuiWindowSeparator(p_gui);
		//
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE * 1.5f, " Reset position    ", SH_GUI_CENTER_WIDTH)) {
			p_camera_transform->position[0] = 0.0f;
			p_camera_transform->position[1] = 0.0f;
			p_camera_transform->position[2] = 0.0f;
		}
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE * 1.5f, " Reset orientation ", SH_GUI_CENTER_WIDTH)) {
			p_camera_transform->rotation[0] = 0.0f;
			p_camera_transform->rotation[1] = 0.0f;
			p_camera_transform->rotation[2] = 0.0f;
		}
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE * 1.5f, " Reset zoom        ", SH_GUI_CENTER_WIDTH)) {
			p_camera->fov = 45.0f;
		}
		shGuiWindowSeparator(p_gui);
		shGuiWindowText(
			p_gui,
			SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
			"Source files",
			SH_GUI_CENTER_WIDTH
		);
		{
			char s_resource_count[4] = { '\0' };
			sprintf(s_resource_count, "%.0f", p_universe_model->resource_countf);
			shGuiWindowSliderf(
				p_gui,
				200.0f,
				SH_GUI_WINDOW_TEXT_SIZE * 2.0f,
				2.0f,
				25.0f,
				s_resource_count,
				&p_universe_model->resource_countf,
				SH_GUI_CENTER_WIDTH
			);
		}
		
		if (shGuiWindowButton(p_gui, SH_GUI_WINDOW_TEXT_SIZE * 1.5f, " Reload resources  ", SH_GUI_CENTER_WIDTH)) {
			gaiaWriteUniverseModelDescriptor(
				p_universe_model->descriptor_info.descriptor.path, 
				0, 
				(uint32_t)p_universe_model->resource_countf, 
				"ftp://hihihiha"
			);
			shResetEngineState(p_engine, 0);
		}
	}
	else if (p_universe_model->display_ui & GAIA_DISPLAY_NAV_INTERFACE) {

		shGuiText(
			p_gui, 
			SH_GUI_WINDOW_TEXT_SIZE, 
			10.0f,
			-10.0f,
			"Pos pc:",
			SH_GUI_EDGE_LEFT | SH_GUI_EDGE_TOP
		);
		shGuiText(
			p_gui, 
			SH_GUI_WINDOW_TEXT_SIZE, 
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
		if (	!(p_universe_model->display_ui & GAIA_DISPLAY_MENU) &&
				
				 p_engine->window.input.cursor_pos_x < ((p_engine->window.width / 2.0f))  &&
				-p_engine->window.input.cursor_pos_x < ((p_engine->window.width / 2.0f))  &&

				-p_engine->window.input.cursor_pos_y < ((p_engine->window.height / 2.0f)) &&
				 p_engine->window.input.cursor_pos_y < ((p_engine->window.height / 2.0f))
			) {
			char cursor_coords[64];
			sprintf(
				cursor_coords,
				"%.2f, %.2f px", 
				p_engine->window.input.cursor_pos_x, 
				p_engine->window.input.cursor_pos_x
			);
			shGuiText(
				p_gui,
				SH_GUI_WINDOW_TEXT_SIZE / 1.0f,
				p_engine->window.input.cursor_pos_x,
				-p_engine->window.input.cursor_pos_y - SH_GUI_WINDOW_TEXT_SIZE * 1.5f,
				cursor_coords,
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



#ifdef SH_SIMULATION_TARGET_TYPE_EXECUTABLE

#include <sheditor/shEditor.h>

int main() {
    ShEngine engine = { 0 };
    engine.simulation_host.p_start          = &gaia_start;
    engine.simulation_host.p_thread         = &gaia_thread;
    engine.simulation_host.p_update_pending = &gaia_update_pending;
    engine.simulation_host.p_after_thread   = &gaia_after_thread;
    engine.simulation_host.p_update         = &gaia_update;
    engine.simulation_host.p_frame_update   = &gaia_frame_update;
    engine.simulation_host.p_frame_resize   = &gaia_frame_resize;
    engine.simulation_host.p_close          = &gaia_close;
    engine.window.title                     = "gaia universe model";
    return shEditorMain(&engine);
}
#endif//SH_SIMULATION_TARGET_TYPE_EXECUTABLE



#ifdef __cplusplus
}
#endif//__cplusplus