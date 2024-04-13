#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include <shengine/shEngine.h>
#include <shengine/shExport.h>
#include <shengine/shLinearAlgebra.h>//will be replaced with shphysics one day

#include <shvulkan/shVulkan.h>

#include <sidera/sidera.h>



#define GAIA_SIM_COPY_MEMORY_TICK_IDX 0
#define GAIA_SIM_SORT_MEMORY_TICK_IDX 1



//NOT IMPLEMENTED
//
//
uint64_t SH_ENGINE_EXPORT_FUNCTION gaia_thread(
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_model == NULL, "gaia_thread: invalid universe model memory", return 0);

	gaiaModelError(
		gaiaReadSources(p_model) == 0,
		"gaia_thread: failed reading source data",
		return 0
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_start(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaia_start: invalid engine memory", return 0);

	p_engine->p_ext = gaiaAllocateUniverseModel();

	gaiaModelError(
		p_engine->p_ext == NULL,
		"gaia_start: invalid engine extension memory",
		return 0
	);

	GaiaUniverseModel* p_model =  p_engine->p_ext;
	ShVkPipelinePool*  p_pool  = &p_model->pipeline_pool;

	shEngineGuiSetup(p_engine);
	p_model->display_ui = 1;

	gaiaModelError(
		gaiaReadSourceSettings("../../smd/settings.smd", p_model) == 0,
		"gaia_start: failed reading source settings",
		return 0
	);

	gaiaModelError(
		gaiaReadGraphicsSettings("../../smd/settings.smd", p_model) == 0,
		"gaia_start: failed reading graphics settings",
		return 0
	);

	gaiaModelError(
		gaiaGetAvailableHeap(p_engine, p_model) == 0,
		"gaia_start: failed getting available heap memory",
		return 0
	);

	gaiaModelError(
		gaiaReadSources(p_model) == 0,
		"gaia_start: failed reading source data",
		return 0
	);

	gaiaModelError(
		gaiaAllocateGpuMemory(p_engine, p_model) == 0,
		"gaia_start: failed allocating gpu memory",
		return 0
	);

	gaiaModelError(
		gaiaWriteAndCopyMemory(
			p_engine, GAIA_MODEL_COPY_RESOURCES | GAIA_MODEL_COPY_COLOR_FILTER_TYPE | GAIA_MODEL_COPY_SHADE_TYPE, p_model
		) == 0,
		"gaia_start: failed writing memory",
		return 0
	);

	gaiaModelError(
		gaiaSetupPipelinePool(p_engine, p_model) == 0,
		"gaia_start: failed setting pipeline pool data",
		return 0
	);

	gaiaModelError(
		gaiaBuildGraphicsPipeline(p_engine, p_model) == 0,
		"gaia_start: failed building graphics pipeline",
		return 0
	);

	gaiaModelError(
		gaiaBuildComputePipeline(p_engine, p_model) == 0,
		"gaia_start: failed building compute pipeline",
		return 0
	);

	//INTERFACE
	//
	//
	p_model->camera.nc          = 10.0E-7f;
	p_model->camera.fc          = 10.0E7f;
	p_model->camera.fov         = 45.0f;
	p_model->camera.free_flight = SH_TRUE;
	p_model->camera.mouse_speed = 10.0f;
	p_model->camera.speed       = 0.1f;

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_update(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaia_update: invalid engine memory", return 0);

	gaiaModelError(
		p_engine->p_ext == NULL,
		"gaia_update: invalid engine extension memory",
		return 0
	);

	ShWindow           window        = p_engine->window;
	GaiaUniverseModel* p_model       = p_engine->p_ext;
	ShCamera*          p_camera      = &p_model->camera;
	ShTransform*       p_transform   = &p_model->camera_transform;

	if (shIsKeyDown(window, SH_KEY_LEFT_CONTROL) && shIsKeyPressed(window, SH_KEY_G)) {

		gaiaModelError(
			gaiaReadGraphicsSettings("../../smd/settings.smd", p_model) == 0,
			"gaia_update: failed reading graphics setting",
			return 0
		);

		gaiaDestroyGraphicsPipeline(p_engine, p_model);

		gaiaModelError(
			gaiaBuildGraphicsPipeline(p_engine, p_model) == 0,
			"gaia_update: failed building graphics pipeline",
			return 0
		);

		gaiaModelError(
			gaiaWriteAndCopyMemory(p_engine, GAIA_MODEL_COPY_COLOR_FILTER_TYPE | GAIA_MODEL_COPY_SHADE_TYPE, p_model) == 0,
			"gaia_update: failed writing and copying memory",
			return 0
		);

	}

	float              d_time        = (float)p_engine->time.delta_time;
	float              fov_scale     = 75.0f;
	float              rotation_unit = (75.01f + p_camera->fov - fov_scale) / 200.0f * d_time;

	if (shIsKeyDown(p_engine->window, SH_KEY_LEFT )) { p_transform->rotation[1] -= rotation_unit; }
	if (shIsKeyDown(p_engine->window, SH_KEY_RIGHT)) { p_transform->rotation[1] += rotation_unit; }
	if (shIsKeyDown(p_engine->window, SH_KEY_UP   )) { p_transform->rotation[0] -= rotation_unit; }
	if (shIsKeyDown(p_engine->window, SH_KEY_DOWN )) { p_transform->rotation[0] += rotation_unit; }
	
	if (p_transform->rotation[0] >= SH_DEGREES_TO_RADIANS( 89.99999f)) { p_transform->rotation[0] = SH_DEGREES_TO_RADIANS(89.99999f);  }
	if (p_transform->rotation[0] <= SH_DEGREES_TO_RADIANS(-89.99999f)) { p_transform->rotation[0] = SH_DEGREES_TO_RADIANS(-89.99999f); }
	
	if (shIsKeyPressed(p_engine->window, SH_KEY_0)) { p_camera->speed = 0.1f;	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_1)) { p_camera->speed = 1.0f;	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_2)) { p_camera->speed = 10.0f;	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_2)) { p_camera->speed = 50.0f;	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_3)) { p_camera->speed = 100.0f;	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_4)) { p_camera->speed = 200.0f;	}
	if (shIsKeyPressed(p_engine->window, SH_KEY_5)) { p_camera->speed = 500.0f;	}

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

	shUpdateTransform(p_transform);
	shUpdateCamera(p_engine, p_transform, p_camera);

	shOnTick(
		p_engine->time, 1.0, 0,
		gaiaWriteInterface("../../smd/interface.smd", "\n\n\n\tGAIA MODEL INTERFACE", p_model);
	);

	if (shIsKeyDown(window, SH_KEY_LEFT_CONTROL) && shIsKeyPressed(window, SH_KEY_F)) {
		gaiaWriteInterface("../../smd/interface-saved.smd", "\n\n\n\tSAVED GAIA MODEL INTERFACE", p_model);
	}

	if (shIsKeyDown(window, SH_KEY_LEFT_CONTROL) && shIsKeyPressed(window, SH_KEY_L)) {
		gaiaLoadInterface("../../smd/interface-saved.smd", p_model);
	}

	gaiaWriteViewMode(p_model);

	gaiaUpdateUI(p_engine);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_main_cmd_buffer(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaia_main_cmd_buffer: invalid engine memory", return 0);

	gaiaModelError(
		p_engine->p_ext == NULL,
		"gaia_main_cmd_buffer: invalid engine extension memory",
		return 0
	);

	GaiaUniverseModel* p_model = (GaiaUniverseModel*)p_engine->p_ext;
	p_model->time              = (float)p_engine->time.now;

	gaiaWriteAndCopyMemory(p_engine, GAIA_MODEL_COPY_TIME, p_model);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_main_renderpass(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaia_main_renderpass: invalid engine memory", return 0);

	gaiaModelError(
		p_engine->p_ext == NULL,
		"gaia_main_renderpass: invalid engine extension memory",
		return 0
	);

	VkDeviceSize        resources_offset      = 0;
	uint32_t            swapchain_image_count = p_engine->core.swapchain_image_count;
	uint32_t            swapchain_image_idx   = p_engine->core.swapchain_image_idx;
	VkDevice            device                = p_engine->core.device;
	VkCommandBuffer     cmd_buffer            = p_engine->core.graphics_cmd_buffers[swapchain_image_idx];
	GaiaUniverseModel*  p_model               = p_engine->p_ext;
	ShCamera*           p_camera              = &p_model->camera;
	ShTransform*        p_transform           = &p_model->camera_transform;
										      
	ShVkPipelinePool*   p_pool                = &p_model->pipeline_pool;
	ShVkPipeline*       p_pipeline            = &p_pool->pipelines[GAIA_MODEL_GRAPHICS_PIPELINE_IDX];

	shBindVertexBuffers(
		cmd_buffer, GAIA_MODEL_PER_INSTANCE_BINDING, 
		1, &p_model->dst_buffer, &resources_offset
	);

	shBindPipeline(cmd_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, p_pipeline);
	
	shPipelinePushConstants(cmd_buffer, p_camera->projection, p_pipeline);
	
	shPipelineBindDescriptorSetUnits(
		cmd_buffer,                      //cmd_buffer
		0,                               //first_descriptor_set
		swapchain_image_idx,             //first_descriptor_set_unit_idx
		1,                               //descriptor_set_unit_count
		VK_PIPELINE_BIND_POINT_GRAPHICS, //bind_point
		0,                               //dynamic_descriptors_count
		NULL,                            //p_dynamic_offsets
		p_pool,                          //p_pipeline_pool
		p_pipeline                       //p_pipeline
	);

	shDraw(cmd_buffer, 3, 0, p_model->resource_count, 0);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_frame_resize(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaia_frame_resize: invalid engine memory", return 0);

	gaiaModelError(
		p_engine->p_ext == NULL,
		"gaia_frame_resize: invalid universe model memory",
		return 0
	);

	VkDevice           device     =  p_engine->core.device;
	GaiaUniverseModel* p_model    =  p_engine->p_ext;
	ShVkPipeline*      p_pipeline = &p_model->pipeline_pool.pipelines[GAIA_MODEL_GRAPHICS_PIPELINE_IDX];

	shDestroyPipeline(device, p_pipeline->pipeline);
	shPipelineSetViewport(
		0, 0, p_engine->window.width, p_engine->window.height,
		0, 0, p_engine->window.width, p_engine->window.height, 
		p_pipeline
	);

	shApplicationError(
		shSetupGraphicsPipeline(device, p_engine->core.renderpass, p_pipeline) == 0,
		"gaia_frame_resize: failed creating pipeline",
		return 0
	);

	return 1;
}

uint8_t SH_ENGINE_EXPORT_FUNCTION gaia_close(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaia_close: invalid engine memory", return 0);

	gaiaModelError(
		p_engine->p_ext == NULL,
		"gaia_close: invalid engine extension memory", 
		return 0
	);

	VkDevice           device  = p_engine->core.device;
	GaiaUniverseModel* p_model = p_engine->p_ext;

	if (p_model->pipeline_pool.descriptor_set_unit_count != 0) {//stuff has been allocated
		gaiaDestroyPipelinePool(p_engine, p_model);
	}
	if (p_model->pipeline_pool.pipelines[GAIA_MODEL_GRAPHICS_PIPELINE_IDX].pipeline != VK_NULL_HANDLE) {
		gaiaDestroyGraphicsPipeline(p_engine, p_model);
	}
	if (p_model->pipeline_pool.pipelines[GAIA_MODEL_COMPUTE_PIPELINE_IDX].pipeline != VK_NULL_HANDLE) {
		gaiaDestroyComputePipeline(p_engine, p_model);
	}
	if (p_model->dst_buffer != VK_NULL_HANDLE) {
		gaiaDestroyBuffers(p_engine, p_model);
	}
	if (p_model->copy_fence != VK_NULL_HANDLE) {
		shDestroyFences(device, 1, &p_model->copy_fence);
	}

	gaiaFreeCelestialBodies(p_model);
	gaiaFreeUniverseModel(p_model);

	return 1;
}



#ifdef SH_APPLICATION_TARGET_TYPE_EXECUTABLE

#include <sheditor/shEditor.h>

int main() {
	ShEngine* p_engine = shAllocateEngine();

	shEngineError(
		p_engine == NULL,
		"main: invalid engine memory",
		return -1
	);

    p_engine->application_host.p_start           = (ShApplicationFunc*) &gaia_start;
    p_engine->application_host.p_update          = (ShApplicationFunc*) &gaia_update;
    p_engine->application_host.p_main_cmd_buffer = (ShApplicationFunc*) &gaia_main_cmd_buffer;
    p_engine->application_host.p_main_renderpass = (ShApplicationFunc*) &gaia_main_renderpass;
    p_engine->application_host.p_frame_resize    = (ShApplicationFunc*) &gaia_frame_resize;
    p_engine->application_host.p_close           = (ShApplicationFunc*) &gaia_close;
    p_engine->window.title                       = "sidera";
    
    shEditorMain(p_engine);
    return 0;
}
#endif//SH_APPLICATION_TARGET_TYPE_EXECUTABLE



#ifdef __cplusplus
}
#endif//__cplusplus