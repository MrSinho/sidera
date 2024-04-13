#ifndef GAIA_UNIVERSE_MODEL_H
#define GAIA_UNIVERSE_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus


#include <gaia-archive-tools/gaiaArchiveTools.h>

#include <shvulkan/shvulkan.h>
#include <smd/smd.h>    



#define GAIA_MODEL_GRAPHICS_PIPELINE_IDX 0
#define GAIA_MODEL_COMPUTE_PIPELINE_IDX  1



//resources
#define GAIA_MODEL_RESOURCES_STAGING_BUFFER_OFFSET 0

//settings
#define GAIA_MODEL_COLOR_FILTER_TYPE_STAGING_BUFFER_OFFSET(resources_size)  (resources_size)
#define GAIA_MODEL_SHADE_TYPE_STAGING_BUFFER_OFFSET(resources_size)        ((resources_size) + (GAIA_MODEL_COLOR_FILTER_TYPE_SIZE))
#define GAIA_MODEL_TIME_STAGING_BUFFER_OFFSET(resources_size)              ((resources_size) + (GAIA_MODEL_COLOR_FILTER_TYPE_SIZE) + (GAIA_MODEL_SHADE_TYPE_SIZE))



//resources
#define GAIA_MODEL_RESOURCES_DST_BUFFER_OFFSET         GAIA_MODEL_RESOURCES_STAGING_BUFFER_OFFSET

//settings
#define GAIA_MODEL_COLOR_FILTER_TYPE_DST_BUFFER_OFFSET GAIA_MODEL_COLOR_FILTER_TYPE_STAGING_BUFFER_OFFSET
#define GAIA_MODEL_SHADE_TYPE_DST_BUFFER_OFFSET        GAIA_MODEL_SHADE_TYPE_STAGING_BUFFER_OFFSET
#define GAIA_MODEL_TIME_DST_BUFFER_OFFSET              GAIA_MODEL_TIME_STAGING_BUFFER_OFFSET



//resources to be calculated
//settings
#define GAIA_MODEL_COLOR_FILTER_TYPE_SIZE 4  //32-bit int
#define GAIA_MODEL_SHADE_TYPE_SIZE        4  //32-bit int
#define GAIA_MODEL_TIME_SIZE              4  //32-bit float



//settings uniform
#define GAIA_MODEL_SETTINGS_UNIFORM_SIZE   (GAIA_MODEL_COLOR_FILTER_TYPE_SIZE + GAIA_MODEL_SHADE_TYPE_SIZE + GAIA_MODEL_TIME_SIZE)
#define GAIA_MODEL_SETTINGS_DESCRIPTOR_IDX 0

//total
#define GAIA_MODEL_UNIFORMS_TOTAL_SIZE GAIA_MODEL_SETTINGS_UNIFORM_SIZE


//final alignment needs to be calculated
#define GAIA_MODEL_SETTINGS_UNIFORM_DST_BUFFER_OFFSET_0  GAIA_MODEL_COLOR_FILTER_TYPE_DST_BUFFER_OFFSET



typedef enum GaiaModelColorFilterFlags {//do read celestial body data
	GAIA_MODEL_COLOR_FILTER_FLAGS_RANDOM_COLOR_SEED    = GAIA_TEFF,//used to generate random color
	GAIA_MODEL_COLOR_FILTER_FLAGS_BARYCENTRIC_DISTANCE = GAIA_BARYCENTRIC_DISTANCE,
	GAIA_MODEL_COLOR_FILTER_FLAGS_TEFF                 = GAIA_TEFF,
	GAIA_MODEL_COLOR_FILTER_FLAGS_LOGG                 = GAIA_LOGG,
	GAIA_MODEL_COLOR_FILTER_FLAGS_FEH                  = GAIA_FEH,
	GAIA_MODEL_COLOR_FILTER_FLAGS_ALPHAFE              = GAIA_ALPHAFE,
	GAIA_MODEL_COLOR_FILTER_FLAGS_AGE                  = GAIA_AGE,
	GAIA_MODEL_COLOR_FILTER_FLAGS_MASS                 = GAIA_MASS,
	GAIA_MODEL_COLOR_FILTER_FLAGS_RADIUS               = GAIA_RADIUS,
	GAIA_MODEL_COLOR_FILTER_FLAGS_VSINI                = GAIA_VSINI,
	GAIA_MODEL_COLOR_FILTER_FLAGS_MAX_ENUM
} GaiaModelColorFilterFlags;

typedef enum GaiaModelColorFilterType {//to submit to shader
	GAIA_MODEL_COLOR_FILTER_TYPE_RANDOM_COLOR_SEED    = 0,
	GAIA_MODEL_COLOR_FILTER_TYPE_BARYCENTRIC_DISTANCE = 1,
	GAIA_MODEL_COLOR_FILTER_TYPE_TEFF                 = 2,
	GAIA_MODEL_COLOR_FILTER_TYPE_LOGG                 = 3,
	GAIA_MODEL_COLOR_FILTER_TYPE_FEH                  = 4,
	GAIA_MODEL_COLOR_FILTER_TYPE_ALPHAFE              = 5,
	GAIA_MODEL_COLOR_FILTER_TYPE_AGE                  = 6,
	GAIA_MODEL_COLOR_FILTER_TYPE_MASS                 = 7,
	GAIA_MODEL_COLOR_FILTER_TYPE_RADIUS               = 8,
	GAIA_MODEL_COLOR_FILTER_TYPE_VSINI                = 9,
	GAIA_MODEL_COLOR_FILTER_TYPE_MAX_ENUM
} GaiaModelColorFilterType;

typedef enum GaiaModelShadeType {
	GAIA_MODEL_SHADE_TYPE_PIXEL          = 0,
	GAIA_MODEL_SHADE_TYPE_CIRCLE         = 1,
	GAIA_MODEL_SHADE_TYPE_CLOUD          = 2,
	GAIA_MODEL_SHADE_TYPE_ANIMATED_CLOUD = 3,
	GAIA_MODEL_SHADE_TYPE_MAX_ENUM
} GaiaModelShadeType;



#define GAIA_MODEL_PER_INSTANCE_BINDING            0

#define GAIA_MODEL_X_PARAMETER_VERTEX_OFFSET       0 //always
#define GAIA_MODEL_Y_PARAMETER_VERTEX_OFFSET       4 //always
#define GAIA_MODEL_Z_PARAMETER_VERTEX_OFFSET       8 //always
#define GAIA_MODEL_COLOR_FILTER_DATA_VERTEX_OFFSET 12//always

#define GAIA_MODEL_X_PARAMETER_LOCATION            0//always
#define GAIA_MODEL_Y_PARAMETER_LOCATION            1//always
#define GAIA_MODEL_Z_PARAMETER_LOCATION            2//always
#define GAIA_MODEL_COLOR_FILTER_DATA_LOCATION      3//always



#define GAIA_VIEW_MODE_CARTESIAN 0.0
#define GAIA_VIEW_MODE_POLAR     1.0



typedef struct GaiaUniverseModel {

	uint32_t                  source_start;
	uint32_t                  source_end;
							  
	SmdFileHandle             source_smd;
	SmdFileHandle             rendering_smd;
	SmdFileHandle             interface_saved_smd;

	SmdExportHandle           interface_smd;
							  
	uint32_t                  max_buffer_memory;
	uint32_t                  available_video_memory;
							  
	uint32_t                  used_video_memory;
							  
	uint32_t                  resources_size;//is not total VRAM, does not consider camera data
	uint32_t                  resource_count;
	uint32_t                  last_resource_count;

	char                      s_x_parameter_type[128];//str1024
	char                      s_y_parameter_type[128];//str1024
	char                      s_z_parameter_type[128];//str1024

	float                     x_parameter_type;
	float                     y_parameter_type;
	float                     z_parameter_type;
	
	char                      s_shade_type[128];//str1024
	char                      s_view_mode [128];//str1024

	float                     view_mode;
	float                     view_point;

	char                      s_color_filter[128];//str1024

	GaiaModelColorFilterFlags color_filter_flags;
	GaiaModelColorFilterType  color_filter_type;

	GaiaModelShadeType        shade_type;

	float                     time;

	uint32_t                  settings_uniform_buffer_offset;
	uint32_t                  utils_uniform_buffer_offset;

	void*                     p_celestial_bodies;
	uint32_t                  celestial_body_size;
	GaiaCelestialBodyFlags    celestial_body_flags;
							  
	VkBuffer                  staging_buffer;
	VkDeviceMemory            staging_memory;
							  
	VkBuffer                  dst_buffer;
	VkDeviceMemory            dst_memory;
							  
	VkFence                   copy_fence;
							  
	ShCamera                  camera;
	ShTransform               camera_transform;
							  
	ShVkPipelinePool          pipeline_pool;

	uint8_t                   display_ui;

} GaiaUniverseModel;



#define gaiaAllocateUniverseModel() (GaiaUniverseModel*)calloc(1, sizeof(GaiaUniverseModel))

#define gaiaFreeCelestialBodies(p_model) free((p_model)->p_celestial_bodies);

#define gaiaFreeUniverseModel(p_model) free(p_model)

#define gaiaModelError(condition, error_msg, failure_expression)\
	if ((int)(condition)) {\
		printf("sidera error: %s\n", (const char*)error_msg);\
		failure_expression;\
	}\



typedef enum GaiaModelCopyStages {
	GAIA_MODEL_COPY_RESOURCES         = 1 << 0,
	GAIA_MODEL_COPY_COLOR_FILTER_TYPE = 1 << 1,
	GAIA_MODEL_COPY_SHADE_TYPE        = 1 << 2,
	GAIA_MODEL_COPY_CAMERA            = 1 << 3,
	GAIA_MODEL_COPY_TIME              = 1 << 4,
	GAIA_MODEL_COPY_ALL               = UINT64_MAX
} GaiaModelCopyStages;



extern uint8_t gaiaReadSourceSettings(
	const char*        path,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaReadGraphicsSettings(
	const char*        path,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaWriteInterface(
	const char*        path,
	SmdLine            comment,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaLoadInterface(
	const char*        path,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaGetAvailableHeap(
	ShEngine* p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaReadSources(
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaWriteViewMode(
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaBuildGraphicsPipeline(
	ShEngine*                 p_engine,
	GaiaUniverseModel*        p_model
);

extern uint8_t gaiaBuildComputePipeline(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaAllocateGpuMemory(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaWriteAndCopyMemory(
	ShEngine*           p_engine,
	GaiaModelCopyStages copy_stages,
	GaiaUniverseModel*  p_model
);

extern uint32_t gaiaGetUniformBufferOffset(
	ShEngine* p_engine,
	uint32_t  offset_0
);

extern uint8_t gaiaSetupPipelinePool(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaDestroyPipelinePool(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaDestroyGraphicsPipeline(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaDestroyComputePipeline(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaSortCelestialBodies(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaDestroyBuffers(
	ShEngine*          p_engine,
	GaiaUniverseModel* p_model
);

extern uint8_t gaiaUpdateUI(
	ShEngine* p_engine
);



#define gaiaMemoryRelease(p_universe_model)\
	free((p_universe_model)->p_celestial_bodies)\



#ifdef __cplusplus
}
#endif//__cplusplus
#endif//GAIA_UNIVERSE_MODEL_H
