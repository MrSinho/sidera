#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include <shengine/shEngine.h>

#include <sidera/sidera.h>
#include <smd/smd.h>

#include <memory.h>



uint8_t gaiaReadSourceSettings(
	const char*        path,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(path    == NULL, "gaiaReadSourceSettings: invalid settings path memory",  return 0);
	gaiaModelError(p_model == NULL, "gaiaReadSourceSettings: invalid universe model memory", return 0);

	SmdFileHandle* p_handle            = &p_model->source_smd;

	smdReadFile(path, p_handle);
	smdParseMemory(p_handle);

	//CELESTIAL BODY COUNT
	//
	//
	smdAccessVarByName(p_handle, "celestial_body_count", NULL, &p_model->resource_count);

	gaiaModelError(
		p_model->resource_count == 0,
		"gaiaReadSourceSettings: invalid celestial_body_count",
		return 0
	);

	//XYZ PARAMETER TYPES
	//
	//
	smdAccessVarByName(p_handle, "x_parameter_type", NULL, p_model->s_x_parameter_type);
	smdAccessVarByName(p_handle, "y_parameter_type", NULL, p_model->s_y_parameter_type);
	smdAccessVarByName(p_handle, "z_parameter_type", NULL, p_model->s_z_parameter_type);

	char* s_parameter_types[3] = {
		p_model->s_x_parameter_type,
		p_model->s_y_parameter_type,
		p_model->s_z_parameter_type
	};

	float* p_model_parameter_types[3] = {
		 &p_model->x_parameter_type,
		 &p_model->y_parameter_type,
		 &p_model->z_parameter_type,
	};

	//MESSY AF BUT IMPORTANT
	//
	//
	for (uint32_t i = 0; i < 3; i++) {
																			 
		     if (strcmp(s_parameter_types[i], "RA")                       == 0) { p_model->celestial_body_flags |= GAIA_RA                      ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_RA                      ); }
		else if (strcmp(s_parameter_types[i], "DEC")                      == 0) { p_model->celestial_body_flags |= GAIA_DEC                     ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_DEC                     ); }
		else if (strcmp(s_parameter_types[i], "BARYCENTRIC_DISTANCE")     == 0) { p_model->celestial_body_flags |= GAIA_BARYCENTRIC_DISTANCE    ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_BARYCENTRIC_DISTANCE    ); }
		else if (strcmp(s_parameter_types[i], "PMRA")                     == 0) { p_model->celestial_body_flags |= GAIA_PMRA                    ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_PMRA                    ); }
		else if (strcmp(s_parameter_types[i], "PMDEC")                    == 0) { p_model->celestial_body_flags |= GAIA_PMDEC                   ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_PMDEC                   ); }
		else if (strcmp(s_parameter_types[i], "RADIAL_VELOCITY")          == 0) { p_model->celestial_body_flags |= GAIA_RADIAL_VELOCITY         ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_RADIAL_VELOCITY         ); }
		else if (strcmp(s_parameter_types[i], "MAG_G")                    == 0) { p_model->celestial_body_flags |= GAIA_MAG_G                   ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MAG_G                   ); }
		else if (strcmp(s_parameter_types[i], "MAG_BP")                   == 0) { p_model->celestial_body_flags |= GAIA_MAG_BP                  ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MAG_BP                  ); }
		else if (strcmp(s_parameter_types[i], "MAG_RP")                   == 0) { p_model->celestial_body_flags |= GAIA_MAG_RP                  ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MAG_RP                  ); }
		else if (strcmp(s_parameter_types[i], "MAG_RVS")                  == 0) { p_model->celestial_body_flags |= GAIA_MAG_RVS                 ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MAG_RVS                 ); }
		else if (strcmp(s_parameter_types[i], "V_I")                      == 0) { p_model->celestial_body_flags |= GAIA_V_I                     ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_V_I                     ); }
		else if (strcmp(s_parameter_types[i], "MEAN_ABSOLUTE_V")          == 0) { p_model->celestial_body_flags |= GAIA_MEAN_ABSOLUTE_V         ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MEAN_ABSOLUTE_V         ); }
		else if (strcmp(s_parameter_types[i], "AG")                       == 0) { p_model->celestial_body_flags |= GAIA_AG                      ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_AG                      ); }
		else if (strcmp(s_parameter_types[i], "AV")                       == 0) { p_model->celestial_body_flags |= GAIA_AV                      ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_AV                      ); }
		else if (strcmp(s_parameter_types[i], "TEFF")                     == 0) { p_model->celestial_body_flags |= GAIA_TEFF                    ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_TEFF                    ); }
		else if (strcmp(s_parameter_types[i], "LOGG")                     == 0) { p_model->celestial_body_flags |= GAIA_LOGG                    ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_LOGG                    ); }
		else if (strcmp(s_parameter_types[i], "FEH")                      == 0) { p_model->celestial_body_flags |= GAIA_FEH                     ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_FEH                     ); }
		else if (strcmp(s_parameter_types[i], "ALPHAFE")                  == 0) { p_model->celestial_body_flags |= GAIA_ALPHAFE                 ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_ALPHAFE                 ); }
		else if (strcmp(s_parameter_types[i], "MBOL")                     == 0) { p_model->celestial_body_flags |= GAIA_MBOL                    ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MBOL                    ); }
		else if (strcmp(s_parameter_types[i], "AGE")                      == 0) { p_model->celestial_body_flags |= GAIA_AGE                     ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_AGE                     ); }
		else if (strcmp(s_parameter_types[i], "MASS")                     == 0) { p_model->celestial_body_flags |= GAIA_MASS                    ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_MASS                    ); }
		else if (strcmp(s_parameter_types[i], "RADIUS")                   == 0) { p_model->celestial_body_flags |= GAIA_RADIUS                  ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_RADIUS                  ); }
		else if (strcmp(s_parameter_types[i], "VSINI")                    == 0) { p_model->celestial_body_flags |= GAIA_VSINI                   ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_VSINI                   ); }
		else if (strcmp(s_parameter_types[i], "POPULATION")               == 0) { p_model->celestial_body_flags |= GAIA_POPULATION              ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_POPULATION              ); }
		else if (strcmp(s_parameter_types[i], "NC")                       == 0) { p_model->celestial_body_flags |= GAIA_NC                      ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_NC                      ); }
		else if (strcmp(s_parameter_types[i], "NT")                       == 0) { p_model->celestial_body_flags |= GAIA_NT                      ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_NT                      ); }
		else if (strcmp(s_parameter_types[i], "SEMIMAJOR_AXIS")           == 0) { p_model->celestial_body_flags |= GAIA_SEMIMAJOR_AXIS          ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_SEMIMAJOR_AXIS          ); }
		else if (strcmp(s_parameter_types[i], "ECCENTRICITY")             == 0) { p_model->celestial_body_flags |= GAIA_ECCENTRICITY            ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_ECCENTRICITY            ); }
		else if (strcmp(s_parameter_types[i], "INCLINATION")              == 0) { p_model->celestial_body_flags |= GAIA_INCLINATION             ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_INCLINATION             ); }
		else if (strcmp(s_parameter_types[i], "LONGITUDE_ASCENDING_NODE") == 0) { p_model->celestial_body_flags |= GAIA_LONGITUDE_ASCENDING_NODE; p_model->celestial_body_size += gaiaGetBodySize(GAIA_LONGITUDE_ASCENDING_NODE); }
		else if (strcmp(s_parameter_types[i], "ORBIT_PERIOD")             == 0) { p_model->celestial_body_flags |= GAIA_ORBIT_PERIOD            ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_ORBIT_PERIOD            ); }
		else if (strcmp(s_parameter_types[i], "VARIABILITY_AMPLITUDE")    == 0) { p_model->celestial_body_flags |= GAIA_VARIABILITY_AMPLITUDE   ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_VARIABILITY_AMPLITUDE   ); }
		else if (strcmp(s_parameter_types[i], "VARIABILITY_PERIOD")       == 0) { p_model->celestial_body_flags |= GAIA_VARIABILITY_PERIOD      ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_VARIABILITY_PERIOD      ); }
		else if (strcmp(s_parameter_types[i], "VARIABILITY_PHASE")        == 0) { p_model->celestial_body_flags |= GAIA_VARIABILITY_PHASE       ; p_model->celestial_body_size += gaiaGetBodySize(GAIA_VARIABILITY_PHASE       ); }
		
		else {
			gaiaModelError(
				1,
				"gaiaReadSourceSettings: invalid s_parameter type",
				return 0
			);
		}
	}
	

	//COLOR FILTER
	//
	//
	smdAccessVarByName(p_handle, "color_filter", NULL, p_model->s_color_filter);

	     if (strcmp(p_model->s_color_filter, "RANDOM_COLOR_SEED")    == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_RANDOM_COLOR_SEED;    p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_RANDOM_COLOR_SEED;    }
	else if (strcmp(p_model->s_color_filter, "BARYCENTRIC_DISTANCE") == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_BARYCENTRIC_DISTANCE; p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_BARYCENTRIC_DISTANCE; }
	else if (strcmp(p_model->s_color_filter, "TEFF")                 == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_TEFF;                 p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_TEFF;                 }
	else if (strcmp(p_model->s_color_filter, "LOGG")                 == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_LOGG;                 p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_LOGG;                 }
	else if (strcmp(p_model->s_color_filter, "FEH")                  == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_FEH;                  p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_FEH;                  }
	else if (strcmp(p_model->s_color_filter, "ALPHAFE")              == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_ALPHAFE;              p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_ALPHAFE;              }
	else if (strcmp(p_model->s_color_filter, "AGE")                  == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_AGE;                  p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_AGE;                  }
	else if (strcmp(p_model->s_color_filter, "MASS")                 == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_MASS;                 p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_MASS;                 }
	else if (strcmp(p_model->s_color_filter, "RADIUS")               == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_RADIUS;               p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_RADIUS;               }
	else if (strcmp(p_model->s_color_filter, "VSINI")                == 0) { p_model->color_filter_flags = GAIA_MODEL_COLOR_FILTER_FLAGS_VSINI;                p_model->color_filter_type = GAIA_MODEL_COLOR_FILTER_TYPE_VSINI;                }

	else {
		gaiaModelError(
			1,
			"gaiaReadSourceSettings: invalid s_color_filter",
			return 0
		);		
	}

	smdFileHandleRelease(p_handle);

	p_model->celestial_body_flags |= p_model->color_filter_flags;
	p_model->celestial_body_size  += gaiaGetBodySize(p_model->color_filter_flags);

	smdFileHandleRelease(p_handle);

	return 1;
}

uint8_t gaiaReadGraphicsSettings(
	const char*        path,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(path    == NULL, "gaiaReadGraphicsSettings: invalid settings path memory",  return 0);
	gaiaModelError(p_model == NULL, "gaiaReadGraphicsSettings: invalid universe model memory", return 0);

	SmdFileHandle* p_handle          = &p_model->rendering_smd;
	
	smdReadFile(path, p_handle);
	smdParseMemory(p_handle);

	
	//VIEW MODE
	//
	//
	smdAccessVarByName(p_handle, "view_mode", NULL, p_model->s_view_mode);

	     if (strcmp(p_model->s_view_mode, "CARTESIAN") == 0) { p_model->view_mode = GAIA_VIEW_MODE_CARTESIAN; }
	else if (strcmp(p_model->s_view_mode, "POLAR")     == 0) { p_model->view_mode = GAIA_VIEW_MODE_POLAR;     }
	
	else {
		gaiaModelError(
			1,
			"gaiaReadGraphicsSettings: invalid s_view_mode",
			return 0
		);		
	}

	//VIEW POINT
	//
	//
	//smdAccessVarByName(p_handle, "view_point", NULL, s_view_point);
	//
	//     if (strcmp(s_view_mode, "ORTHOGRAPHIC") == 0) { p_model->view_mode  = GAIA_VIEW_MODE_CARTESIAN; }
	//else if (strcmp(s_view_mode, "PERSPECTIVE")  == 0) { p_model->view_point = GAIA_VIEW_MODE_POLAR;     }
	//
	//else {
	//	gaiaModelError(
	//		1,
	//		"gaiaReadGraphicsSettings: invalid s_view_mode",
	//		return 0
	//	);		
	//}

	//SHADE TYPE
	//
	//
	smdAccessVarByName(p_handle, "shade_type", NULL, p_model->s_shade_type);

	     if (strcmp(p_model->s_shade_type, "PIXEL")    == 0)  { p_model->shade_type = GAIA_MODEL_SHADE_TYPE_PIXEL;           }
	else if (strcmp(p_model->s_shade_type, "CIRCLE")   == 0)  { p_model->shade_type = GAIA_MODEL_SHADE_TYPE_CIRCLE;          }
	else if (strcmp(p_model->s_shade_type, "CLOUD")    == 0)  { p_model->shade_type = GAIA_MODEL_SHADE_TYPE_CLOUD;           }
	else if (strcmp(p_model->s_shade_type, "ANIMATED") == 0)  { p_model->shade_type = GAIA_MODEL_SHADE_TYPE_ANIMATED_CLOUD;  }

	else {
		gaiaModelError(
			1,
			"gaiaReadGraphicsSettings: invalid s_shade_type",
			return 0
		);		
	}

	smdFileHandleRelease(p_handle);

	return 1;
}

uint8_t gaiaWriteInterface(
	const char*        path,
	SmdLine            comment,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(path    == NULL, "gaiaWriteInterface: invalid interface path memory", return 0);
	gaiaModelError(p_model == NULL, "gaiaWriteInterface: invalid universe model memory", return 0);

	SmdExportHandle* p_handle    = &p_model->interface_smd;
	ShTransform*     p_transform = &p_model->camera_transform;
	ShCamera*        p_camera    = &p_model->camera;

	smdCommentLine(p_handle, comment);

	smdCommentLine(p_handle, "\n\n\n\tCAMERA PROPERTIES\n\n\n");
	
	smdWriteLine(p_handle, 1, "camera_right_ascension___rad", SMD_VAR_TYPE_FLOAT32, &p_transform->rotation[1]);
	smdWriteLine(p_handle, 1, "camera_declination_______rad", SMD_VAR_TYPE_FLOAT32, &p_transform->rotation[0]);
	smdWriteLine(p_handle, 3, "camera_position___________pc", SMD_VAR_TYPE_FLOAT32,  p_transform->position);
	smdWriteLine(p_handle, 1, "camera_fov_______________rad", SMD_VAR_TYPE_FLOAT32, &p_camera->fov);

	smdWriteFile(p_handle, (char*)path);

	smdExportHandleRelease(p_handle);

	return 1;
}

uint8_t gaiaLoadInterface(
	const char*        path,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(path     == NULL, "gaiaLoadInterface: invalid interface path memory", return 0);
	gaiaModelError(p_model  == NULL, "gaiaLoadInterface: invalid universe model memory", return 0);

	SmdFileHandle* p_handle    = &p_model->interface_saved_smd;
	ShTransform*   p_transform = &p_model->camera_transform;
	ShCamera*      p_camera    = &p_model->camera;

	smdReadFile(path, p_handle);
	smdParseMemory(p_handle);

	smdAccessVarByName(p_handle, "camera_right_ascension___rad", NULL, &p_transform->rotation[0]);
	smdAccessVarByName(p_handle, "camera_declination_______rad", NULL, &p_transform->rotation[1]);
	smdAccessVarByName(p_handle, "camera_position___________pc", NULL,  p_transform->position);
	smdAccessVarByName(p_handle, "camera_fov_______________rad", NULL, &p_camera->fov);

	smdFileHandleRelease(p_handle);

	return 1;
}

uint8_t gaiaGetAvailableHeap(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaGetAvailableHeap: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaGetAvailableHeap: invalid universe model memory", return 0);

	uint32_t                                  host_visible_available_video_memory =   0;
	uint32_t                                  host_memory_type_index              =   0;
	uint32_t                                  device_memory_type_index            =   0;
	VkPhysicalDeviceMemoryBudgetPropertiesEXT host_heap_budget                    = { 0 };
	VkPhysicalDeviceMemoryBudgetPropertiesEXT device_heap_budget                  = { 0 };
	uint32_t                                  device_available_video_memory       =   0;

	//HOST HEAP BUDGET
	//
	//
	shGetMemoryType(
		p_engine->core.device,
		p_engine->core.physical_device,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&host_memory_type_index
	);

	shGetMemoryBudgetProperties(
		p_engine->core.physical_device, &host_heap_budget
	);

	host_visible_available_video_memory = (uint32_t)host_heap_budget.heapBudget[host_memory_type_index];


	//DEVICE HEAP BUDGET
	//
	//
	shGetMemoryType(
		p_engine->core.device,
		p_engine->core.physical_device,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		&device_memory_type_index
	);

	shGetMemoryBudgetProperties(
		p_engine->core.physical_device, &device_heap_budget
	);

	device_available_video_memory           = (uint32_t)device_heap_budget.heapBudget[device_memory_type_index];
	p_model->available_video_memory         = host_visible_available_video_memory <= device_available_video_memory ? host_visible_available_video_memory : device_available_video_memory;
	
	p_model->resources_size                 = p_model->resource_count * p_model->celestial_body_size;
	
	p_model->settings_uniform_buffer_offset = gaiaGetUniformBufferOffset(p_engine, GAIA_MODEL_SETTINGS_UNIFORM_DST_BUFFER_OFFSET_0(p_model->resources_size));
	p_model->used_video_memory              = p_model->settings_uniform_buffer_offset + GAIA_MODEL_SETTINGS_UNIFORM_SIZE;//not over yet

	//p_model->utils_uniform_buffer_offset    = gaiaGetUniformBufferOffset(p_engine, p_model->used_video_memory);
	//p_model->used_video_memory              = p_model->utils_uniform_buffer_offset + GAIA_MODEL_UTILS_UNIFORM_SIZE;

	gaiaModelError(
		p_model->used_video_memory > p_model->available_video_memory,
		"gaiaGetAvailableHeap: too big number of celestial bodies",
		return 0
	);

	return 1;
}

uint8_t gaiaReadSources(
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_model == NULL, "gaiaReadSources: invalid universe model memory", return 0);

	p_model->p_celestial_bodies = calloc(1, p_model->used_video_memory);

	gaiaModelError(
		p_model->p_celestial_bodies == NULL,
		"gaiaReadSources: invalid celestial bodies memory",
		return 0
	);

	uint32_t _resources_size = 0;//at the end will be equal to p_model->resources_size

	for (uint32_t i = p_model->source_start; i < p_model->resource_count; i++) {

		void* p_src         = NULL;
		uint32_t bytes_read = 0;

		gaiaModelError(
			gaiaReadBinaryFileFromID("../../../gaia-release/", i, p_model->celestial_body_flags, 0, 0, &bytes_read, &p_src) == 0,
			"gaiaReadSources: failed reading source file",
			return 0;
		);

		if (_resources_size + bytes_read >= p_model->resources_size) {
			uint32_t copy_size = p_model->resources_size - _resources_size;
			memcpy(&((char*)p_model->p_celestial_bodies)[_resources_size], p_src, copy_size);
			_resources_size += copy_size;
			gaiaFree(p_src);
			break;
		}

		memcpy(&((char*)p_model->p_celestial_bodies)[_resources_size], p_src, bytes_read);
		_resources_size += bytes_read;

		gaiaFree(p_src);
	}

	return 1;
}

uint8_t gaiaWriteViewMode(
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_model == NULL, "gaiaWriteViewMode: invalid universe model memory", return 0);

	p_model->camera.view[0][3] = p_model->view_mode;

	return 1;
}

uint8_t gaiaBuildGraphicsPipeline(
	ShEngine*                 p_engine,
	GaiaUniverseModel*        p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaBuildGraphicsPipeline: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaBuildGraphicsPipeline: invalid universe model memory", return 0);

	gaiaModelError(
		p_model->shade_type >= GAIA_MODEL_SHADE_TYPE_MAX_ENUM, 
		"gaiaBuildGraphicsPipeline: invalid pipeline type",
		return 0
	);

	gaiaModelError(
		p_model->color_filter_flags >= GAIA_MODEL_COLOR_FILTER_FLAGS_MAX_ENUM,
		"gaiaBuildGraphicsPipeline: invalid color filter",
		return 0
	);
	
	VkDevice          device                =  p_engine->core.device;
	VkRenderPass      renderpass            =  p_engine->core.renderpass;
	uint32_t          swapchain_image_count =  p_engine->core.swapchain_image_count;

	ShVkPipelinePool* p_pool                = &p_model->pipeline_pool;
	ShVkPipeline*     p_pipeline            = &p_pool->pipelines[GAIA_MODEL_GRAPHICS_PIPELINE_IDX];
	uint32_t          sample_count          =  p_engine->core.sample_count;
	uint32_t          width                 =  p_engine->window.width;
	uint32_t          height                =  p_engine->window.height;

	shPipelineSetVertexBinding(
		GAIA_MODEL_PER_INSTANCE_BINDING,
		p_model->celestial_body_size,
		VK_VERTEX_INPUT_RATE_INSTANCE,
		p_pipeline
	);

	shPipelineSetVertexAttribute(
		GAIA_MODEL_X_PARAMETER_LOCATION, GAIA_MODEL_PER_INSTANCE_BINDING,
		VK_FORMAT_R32_SFLOAT, GAIA_MODEL_X_PARAMETER_VERTEX_OFFSET, p_pipeline
	);

	shPipelineSetVertexAttribute(
		GAIA_MODEL_Y_PARAMETER_LOCATION, GAIA_MODEL_PER_INSTANCE_BINDING,
		VK_FORMAT_R32_SFLOAT, GAIA_MODEL_Y_PARAMETER_VERTEX_OFFSET, p_pipeline
	);

	shPipelineSetVertexAttribute(
		GAIA_MODEL_Z_PARAMETER_LOCATION, GAIA_MODEL_PER_INSTANCE_BINDING,
		VK_FORMAT_R32_SFLOAT, GAIA_MODEL_Z_PARAMETER_VERTEX_OFFSET, p_pipeline
	);

	shPipelineSetVertexAttribute(
		GAIA_MODEL_COLOR_FILTER_DATA_LOCATION, GAIA_MODEL_PER_INSTANCE_BINDING,
		VK_FORMAT_R32_SFLOAT, GAIA_MODEL_COLOR_FILTER_DATA_VERTEX_OFFSET, p_pipeline
	);

	shPipelineSetVertexInputState(p_pipeline);

	if (p_model->shade_type == GAIA_MODEL_SHADE_TYPE_PIXEL) {
		shPipelineCreateInputAssembly(
			VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
			VK_FALSE,
			p_pipeline
		);

		shPipelineCreateRasterizer(
			VK_POLYGON_MODE_POINT,
			SH_FALSE,
			p_pipeline
		);

		shPipelineSetMultisampleState(
			sample_count,
			0.0f,
			p_pipeline
		);
	}
	else {
		shPipelineCreateInputAssembly(
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			VK_FALSE,
			p_pipeline
		);

		shPipelineCreateRasterizer(
			VK_POLYGON_MODE_FILL,
			SH_FALSE,
			p_pipeline
		);

		shPipelineSetMultisampleState(
			sample_count,
			0.0f,
			p_pipeline
		);
	}
	

	shPipelineSetViewport(
		0, 0, width, height, 
		0, 0, width, height, 
		p_pipeline
	);

	shPipelineColorBlendSettings(
		SH_FALSE, SH_FALSE, 
		SH_ENGINE_SUBPASS_COLOR_ATTACHMENT_COUNT, 
		p_pipeline
	);

	shPipelineSetPushConstants(VK_SHADER_STAGE_VERTEX_BIT, 0, 128, p_pipeline);

	uint32_t shader_size = 0;
	char*    shader_code = NULL;
	
	if (p_model->shade_type == GAIA_MODEL_SHADE_TYPE_PIXEL) {
		shader_code = (char*)shReadCode(
			"../../shaders/bin/celestialbody-pixel.vert.spv",
			"rb", &shader_size
		);
	}
	else {
		shader_code = (char*)shReadCode(
			"../../shaders/bin/celestialbody-shaded.vert.spv",
			"rb", &shader_size
		);
	}
	
	shPipelineCreateShaderModule(
		device, shader_size, 
		shader_code, p_pipeline
	);

	free(shader_code);

	shPipelineCreateShaderStage(
		VK_SHADER_STAGE_VERTEX_BIT,
		p_pipeline
	);

	shader_code = (char*)shReadCode(
		"../../shaders/bin/celestialbody-shaded.frag.spv",
		"rb", &shader_size
	);

	shPipelineCreateShaderModule(
		device,
		shader_size,
		shader_code,
		p_pipeline
	);

	shPipelineCreateShaderStage(
		VK_SHADER_STAGE_FRAGMENT_BIT, p_pipeline
	);

	shPipelineCreateLayout(
		device, 0, swapchain_image_count, p_pool, p_pipeline
	);

	shSetupGraphicsPipeline(device, renderpass, p_pipeline);

	return 1;
}

uint8_t gaiaBuildComputePipeline(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaBuildComputePipeline: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaBuildComputePipeline: invalid universe model memory", return 0);

	return 1;
}

uint8_t gaiaAllocateGpuMemory(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaAllocateGpuMemory: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaAllocateGpuMemory: invalid universe model memory", return 0);

	VkDevice         device           =  p_engine->core.device;
	VkPhysicalDevice physical_device  =  p_engine->core.physical_device;

	VkBuffer*        p_staging_buffer = &p_model->staging_buffer;
	VkDeviceMemory*  p_staging_memory = &p_model->staging_memory;
									 
	VkBuffer*        p_dst_buffer     = &p_model->dst_buffer;
	VkDeviceMemory*  p_dst_memory     = &p_model->dst_memory;
								     
	uint32_t         total_size       =  p_model->used_video_memory;

	//
	//STAGING BUFFER
	//
	shCreateBuffer(
		device, total_size,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_SHARING_MODE_EXCLUSIVE, p_staging_buffer
	);

	shAllocateBufferMemory(
		device, physical_device, *p_staging_buffer,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		p_staging_memory
	);

	shBindBufferMemory(
		device, *p_staging_buffer, 0, *p_staging_memory
	);

	//
	//DST BUFFER
	//
	shCreateBuffer(
		device, total_size,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_SHARING_MODE_EXCLUSIVE, p_dst_buffer
	);

	shAllocateBufferMemory(
		device, physical_device, *p_dst_buffer,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		p_dst_memory
	);

	shBindBufferMemory(
		device, *p_dst_buffer, 0, *p_dst_memory
	);

	//
	//
	//
	shCreateFences(device, 1, SH_TRUE, &p_model->copy_fence);

	return 1;
}

uint8_t gaiaWriteAndCopyMemory(
	ShEngine*           p_engine, 
	GaiaModelCopyStages copy_stages,
	GaiaUniverseModel*  p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaWriteAndCopyMemory: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaWriteAndCopyMemory: invalid universe model memory", return 0);

	gaiaModelError(
		copy_stages == 0,
		"gaiaWriteAndCopyMemory: invalid copy stages flags",
		return 0
	);

	VkDevice         device          = p_engine->core.device;
	VkCommandBuffer  cmd_buffer      = p_engine->core.transfer_cmd_buffer;

	VkFence          copy_fence      = p_model->copy_fence;
	VkBuffer         staging_buffer  = p_model->staging_buffer;
	VkDeviceMemory   staging_memory  = p_model->staging_memory;
	
	VkBuffer         dst_buffer      = p_model->dst_buffer;
	uint32_t         resources_size  = p_model->resources_size;

	if (copy_stages & GAIA_MODEL_COPY_RESOURCES) {
		shWriteMemory(
			device, staging_memory,
			GAIA_MODEL_RESOURCES_STAGING_BUFFER_OFFSET,
			resources_size,
			p_model->p_celestial_bodies
		);
	}

	if (copy_stages & GAIA_MODEL_COPY_COLOR_FILTER_TYPE) {
		shWriteMemory(
			device, staging_memory,
			GAIA_MODEL_COLOR_FILTER_TYPE_STAGING_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_COLOR_FILTER_TYPE_SIZE,
			&p_model->color_filter_type
		);
	}

	if (copy_stages & GAIA_MODEL_COPY_SHADE_TYPE) {
		shWriteMemory(
			device, staging_memory,
			GAIA_MODEL_SHADE_TYPE_STAGING_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_SHADE_TYPE_SIZE,
			&p_model->shade_type
		);
	}

	if (copy_stages & GAIA_MODEL_COPY_TIME) {
		shWriteMemory(
			device, staging_memory,
			GAIA_MODEL_TIME_STAGING_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_TIME_SIZE,
			&p_model->time
		);
	}

	shWaitForFences(device, 1, &copy_fence, SH_TRUE, UINT64_MAX);
	
	shResetFences(device, 1, &copy_fence);
	
	shBeginCommandBuffer(cmd_buffer);
	
	//BETTER COPY ONE TIME MULTIPLE REGIONS
	if (copy_stages & GAIA_MODEL_COPY_RESOURCES) {
		shCopyBuffer(
			cmd_buffer, staging_buffer,
			GAIA_MODEL_RESOURCES_STAGING_BUFFER_OFFSET,
			GAIA_MODEL_RESOURCES_DST_BUFFER_OFFSET,
			resources_size,
			dst_buffer
		);
	}

	if (copy_stages & GAIA_MODEL_COPY_COLOR_FILTER_TYPE) {
		shCopyBuffer(
			cmd_buffer, staging_buffer,
			GAIA_MODEL_COLOR_FILTER_TYPE_STAGING_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_COLOR_FILTER_TYPE_DST_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_COLOR_FILTER_TYPE_SIZE,
			dst_buffer
		);
	}

	if (copy_stages & GAIA_MODEL_COPY_SHADE_TYPE) {
		shCopyBuffer(
			cmd_buffer, staging_buffer,
			GAIA_MODEL_SHADE_TYPE_STAGING_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_SHADE_TYPE_DST_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_SHADE_TYPE_SIZE,
			dst_buffer
		);
	}

	if (copy_stages & GAIA_MODEL_COPY_TIME) {
		shCopyBuffer(
			cmd_buffer, staging_buffer,
			GAIA_MODEL_TIME_STAGING_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_TIME_DST_BUFFER_OFFSET(resources_size),
			GAIA_MODEL_TIME_SIZE,
			dst_buffer
		);
	}
	
	shEndCommandBuffer(cmd_buffer);
	
	shQueueSubmit(
		1, &cmd_buffer, p_engine->core.graphics_queue,
		copy_fence, 0, NULL, VK_PIPELINE_STAGE_TRANSFER_BIT,
		0, NULL
	);
	
	shWaitForFences(device, 1, &copy_fence, SH_TRUE, UINT64_MAX);

	return 1;
}

uint32_t gaiaGetUniformBufferOffset(
	ShEngine* p_engine,
	uint32_t  offset_0
) {
	gaiaModelError(p_engine == NULL, "gaiaGetUniformBufferOffset: invalid engine memory", return 0);

	uint32_t alignment = (uint32_t)p_engine->core.physical_device_properties.limits.minUniformBufferOffsetAlignment;
	uint32_t mod       = offset_0 % alignment;
	
	uint32_t offset    = offset_0;
	
	if (offset % alignment) {
		offset = offset_0 + alignment - (offset_0 % alignment);
	}

	return offset;
}

uint8_t gaiaSetupPipelinePool(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaSetupPipelinePool: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaSetupPipelinePool: invalid universe model memory", return 0);
	
	VkDevice          device                =  p_engine->core.device;
	ShVkPipelinePool* p_pool                = &p_model->pipeline_pool;
	uint32_t          swapchain_image_count =  p_engine->core.swapchain_image_count;

	VkBuffer          dst_buffer            =  p_model->dst_buffer;

	//
	//
	//
	shPipelinePoolCreateDescriptorSetLayoutBinding(
		0, 
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1,
		VK_SHADER_STAGE_FRAGMENT_BIT, p_pool
	);

	//SETTINGS
	//
	//
	shPipelinePoolSetDescriptorBufferInfos(
		GAIA_MODEL_SETTINGS_DESCRIPTOR_IDX * swapchain_image_count, swapchain_image_count, dst_buffer,
		p_model->settings_uniform_buffer_offset,
		GAIA_MODEL_SETTINGS_UNIFORM_SIZE, p_pool
	);

	shPipelinePoolCreateDescriptorSetLayout(
		device, 0, 1, 
		GAIA_MODEL_SETTINGS_DESCRIPTOR_IDX * swapchain_image_count, p_pool
	);

	shPipelinePoolCopyDescriptorSetLayout(
		GAIA_MODEL_SETTINGS_DESCRIPTOR_IDX * swapchain_image_count, 
		GAIA_MODEL_SETTINGS_DESCRIPTOR_IDX * swapchain_image_count, 
		swapchain_image_count, p_pool
	);

	//SAME DESCRIPTOR POOL AND ALLOCATE ALL
	//
	//
	shPipelinePoolCreateDescriptorPool(
		device, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 
		swapchain_image_count, p_pool
	);

	shPipelinePoolAllocateDescriptorSetUnits(
		device, 0, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		0, swapchain_image_count, p_pool
	);

	shPipelinePoolUpdateDescriptorSetUnits(
		device, 0, swapchain_image_count, p_pool
	);

	return 1;
}

uint8_t gaiaDestroyPipelinePool(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaDestroyPipelinePool: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaDestroyPipelinePool: invalid universe model memory", return 0);

	VkDevice          device =  p_engine->core.device;
	ShVkPipelinePool* p_pool = &p_model->pipeline_pool;

	shWaitDeviceIdle(device);

	shPipelinePoolDestroyDescriptorPools(device, 0, 1, p_pool);
	shPipelinePoolDestroyDescriptorSetLayouts(device, GAIA_MODEL_SETTINGS_DESCRIPTOR_IDX * p_engine->core.swapchain_image_count, 1, p_pool);

	return 1;
}

uint8_t gaiaDestroyGraphicsPipeline(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaDestroyGraphicsPipeline: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaDestroyGraphicsPipeline: invalid universe model memory", return 0);

	VkDevice          device     =  p_engine->core.device;
	ShVkPipelinePool* p_pool     = &p_model->pipeline_pool;
	ShVkPipeline*     p_pipeline = &p_model->pipeline_pool.pipelines[GAIA_MODEL_GRAPHICS_PIPELINE_IDX];

	shDestroyShaderModule(device, p_pipeline->shader_modules[0]);
	shDestroyShaderModule(device, p_pipeline->shader_modules[1]);

	shPipelineDestroyLayout(device, p_pipeline);

	shDestroyPipeline(device, p_pipeline->pipeline);

	memset(p_pipeline, 0, sizeof(ShVkPipeline));

	return 1;
}

uint8_t gaiaDestroyComputePipeline(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaDestroyComputePipeline: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaDestroyComputePipeline: invalid universe model memory", return 0);

	VkDevice          device     =  p_engine->core.device;
	ShVkPipelinePool* p_pool     = &p_model->pipeline_pool;
	ShVkPipeline*     p_pipeline = &p_model->pipeline_pool.pipelines[GAIA_MODEL_COMPUTE_PIPELINE_IDX];

	return 1;
}

uint8_t gaiaSortCelestialBodies(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaWriteMemory: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaWriteMemory: invalid universe model memory", return 0);



	return 1;
}

uint8_t gaiaDestroyBuffers(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
) {
	gaiaModelError(p_engine == NULL, "gaiaDestroyBuffers: invalid engine memory",         return 0);
	gaiaModelError(p_model  == NULL, "gaiaDestroyBuffers: invalid universe model memory", return 0);
	
	VkDevice       device         = p_engine->core.device;
	VkBuffer       staging_buffer = p_model->staging_buffer;
	VkDeviceMemory staging_memory = p_model->staging_memory;
	VkBuffer       dst_buffer     = p_model->dst_buffer;
	VkDeviceMemory dst_memory     = p_model->dst_memory;

	shClearBufferMemory(device, staging_buffer, staging_memory);
	shClearBufferMemory(device, dst_buffer, dst_memory);

	return 1;
}

uint8_t gaiaUpdateUI(
	ShEngine* p_engine
) {
	gaiaModelError(p_engine == NULL, "gaiaUpdateUI: invalid engine memory", return 0);

	ShGui*             p_gui   = &p_engine->gui;
	GaiaUniverseModel* p_model = (GaiaUniverseModel*)p_engine->p_ext;
	
	if (shIsKeyPressed(p_engine->window, SH_KEY_H)) {
		p_model->display_ui = !p_model->display_ui;
	}

	if (p_model->display_ui == 0) {
		return 1;
	}

	char text[2048] = { 0 };

	shGuiText(
		p_gui,
		(shguivec2) { 0.0f, -5.0f },
		SH_GUI_COLOR_WHITE,
		12.0f,
		"Gaia@AIP",
		SH_GUI_CENTER_WIDTH | SH_GUI_EDGE_TOP
	);

	char* camera_info = "\
right ascension      : %.3f\n\
right declination    : %.3f\n\
position             : %.3f, %.3f, %.3f\n\
fov                  : %.3f\n\
	";
	snprintf(
		text,
		2048,
		camera_info,
		p_model->camera_transform.rotation[1],
		p_model->camera_transform.rotation[0],
		p_model->camera_transform.position[0], p_model->camera_transform.position[1], p_model->camera_transform.position[2],
		p_model->camera.fov
	);

	shGuiText(
		p_gui,
		(shguivec2) { -5.0f, -5.0f },
		SH_GUI_COLOR_WHITE,
		12.0f,
		text,
		SH_GUI_EDGE_RIGHT | SH_GUI_EDGE_TOP
	);
	memset(text, 0, 2048);

	char* settings = "\
data release     : GEDR3\n\
body count       : %i\n\
x parameter type : %s\n\
y parameter type : %s\n\
z parameter type : %s\n\
color filter     : %s\n\
\n\
\n\
\n\
view mode        : %s\n\
shade type       : %s\n\
\n\
\n\
\n\
GPU              : %s\n\
used VRAM        : %i B\n\
	";
	snprintf(
		text, 
		2048, 
		settings,
		p_model->resource_count,
		p_model->s_x_parameter_type,
		p_model->s_y_parameter_type,
		p_model->s_z_parameter_type,
		p_model->s_color_filter,
		p_model->s_view_mode,
		p_model->s_shade_type,
		p_engine->core.physical_device_properties.deviceName,
		p_model->used_video_memory
	);

	shGuiText(
		p_gui,
		(shguivec2) { 5.0f, -5.0f },
		SH_GUI_COLOR_WHITE,
		12.0f,
		text,
		SH_GUI_EDGE_LEFT | SH_GUI_EDGE_TOP
	);
	memset(text, 0, 2048);

	shGuiText(
		p_gui,
		(shguivec2) { -5.0f, 10.0f },
		SH_GUI_COLOR_WHITE,
		12.0f,
		SIDERA_VERSION,
		SH_GUI_EDGE_RIGHT | SH_GUI_EDGE_BOTTOM
	);

	shGuiText(
		p_gui,
		(shguivec2) { 0.0f, 10.0f },
		SH_GUI_COLOR_WHITE,
		12.0f,
		"@mrsinho/sidera",
		SH_GUI_CENTER_WIDTH | SH_GUI_EDGE_BOTTOM
	);

	snprintf(
		text,
		2048,
		"time: %.3f s",
		p_model->time
	);

	shGuiText(
		p_gui,
		(shguivec2) { 5.0f, 10.0f },
		SH_GUI_COLOR_WHITE,
		12.0f,
		text,
		SH_GUI_EDGE_LEFT | SH_GUI_EDGE_BOTTOM
	);
	memset(text, 0, 2048);


	return 1;
}



#ifdef __cplusplus
}
#endif//__cplusplus