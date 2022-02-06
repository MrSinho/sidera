#include <engine/shEngine.h>

#include <shvulkan/shVkCore.h>
#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkPipelineData.h>
#include <shvulkan/shVkDrawloop.h>

#include <ecs/shCamera.h>
#include <ecs/shTransform.h>

#include <gaia_archive_tools/gaiaArchiveTools.h>

#include <assert.h>

const char* readBinary(const char* path, uint32_t* p_size);

#ifdef _MSC_VER
#pragma warning (disable: 6011)
#endif//_MSC_VER

int main(void) {

	ShEngine engine = { 0 };
	shWindowSetup("SH-Engine Editor", 720, 480, &engine.window);
	shCreateInstance(&engine.core, "SH-Engine editor", "SH-Engine", engine.window.instance_extension_count, engine.window.pp_instance_extensions);
	shCreateWindowSurface(&engine);
	shSelectPhysicalDevice(&engine.core, VK_QUEUE_GRAPHICS_BIT);
	shSetLogicalDevice(&engine.core);
	shGetGraphicsQueue(&engine.core);
	shGetComputeQueue(&engine.core);
	shInitSwapchainData(&engine.core);
	shInitDepthData(&engine.core);
	shCreateRenderPass(&engine.core);
	shSetFramebuffers(&engine.core);
	shSetSyncObjects(&engine.core);
	shCreateGraphicsCommandBuffer(&engine.core);

	engine.material_count = 1;
	engine.p_materials = calloc(1, sizeof(ShMaterialHost));
	uint32_t vertex_shader_size = 0;
	uint32_t fragment_shader_size = 0;
	const char* vertex_code = readBinary("../shaders/bin/celestialBody.vert.spv", &vertex_shader_size);
	const char* fragment_code = readBinary("../shaders/bin/celestialBody.frag.spv", &fragment_shader_size);
	shCreateShaderModule(engine.core.device, vertex_shader_size, vertex_code, &engine.p_materials[0].pipeline);
	shCreateShaderModule(engine.core.device, fragment_shader_size, fragment_code, &engine.p_materials[0].pipeline);
	shCreateShaderStage(engine.core.device, engine.p_materials[0].pipeline.shader_modules[0], VK_SHADER_STAGE_VERTEX_BIT, &engine.p_materials[0].pipeline);
	shCreateShaderStage(engine.core.device, engine.p_materials[0].pipeline.shader_modules[1], VK_SHADER_STAGE_FRAGMENT_BIT, &engine.p_materials[0].pipeline);

	shSetPushConstants(VK_SHADER_STAGE_VERTEX_BIT, 0, 128, &engine.p_materials[0].pipeline);

	shSetVertexInputAttribute(0, SH_VEC1_SIGNED_FLOAT, 0, 4, &engine.p_materials[0].fixed_states); //asc
	shSetVertexInputAttribute(1, SH_VEC1_SIGNED_FLOAT, 4, 4, &engine.p_materials[0].fixed_states); //dec
	shSetVertexInputAttribute(2, SH_VEC1_SIGNED_FLOAT, 8, 4, &engine.p_materials[0].fixed_states); //baricentric_distance
	shSetVertexInputAttribute(3, SH_VEC1_SIGNED_FLOAT,12, 4, &engine.p_materials[0].fixed_states); //teff
	shSetVertexInputAttribute(4, SH_VEC1_SIGNED_FLOAT,16, 4, &engine.p_materials[0].fixed_states); //radius

	shSetFixedStates(&engine.core, SH_FIXED_STATES_POLYGON_MODE_POINTS | SH_FIXED_STATES_PRIMITIVE_TOPOLOGY_POINT_LIST, &engine.p_materials[0].fixed_states);
	shSetupGraphicsPipeline(&engine.core, engine.p_materials[0].fixed_states, &engine.p_materials[0].pipeline);

	//typedef struct celestialbody_t {
	//	double ra;
	//	double dec;
	//	float baricentric_distance;
	//	float teff;
	//	float radius;
	//}celestialbody_t;
	#define CELESTIAL_BODY_SIZE 20	
	#define CELESTIAL_BODY_COUNT 800000
	#define UNIVERSE_MODEL_REGIONS_COUNT 1
	#define UNIVERSE_MODEL_REGION_SIZE CELESTIAL_BODY_SIZE * CELESTIAL_BODY_COUNT
	#define UNIVERSE_MODEL_REGIONS_SIZE UNIVERSE_MODEL_REGION_SIZE * UNIVERSE_MODEL_REGIONS_COUNT

	void* p_celestial_bodies = calloc(1, UNIVERSE_MODEL_REGIONS_SIZE);
	uint64_t celestial_body_flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF | GAIA_RADIUS;
	gaiaReadBinaryFile("../../Gaia_Archive_Tools/gaia_bin/GaiaUniverseModel_4001.bin", celestial_body_flags, 0, UNIVERSE_MODEL_REGION_SIZE, p_celestial_bodies);
	//gaiaReadBinaryFile("../../Gaia_Archive_Tools/gaia_bin/GaiaUniverseModel_0001.bin", celestial_body_flags, 0, UNIVERSE_MODEL_REGION_SIZE, &((char*)p_celestial_bodies)[UNIVERSE_MODEL_REGION_SIZE]);
	//gaiaReadBinaryFile("../../Gaia_Archive_Tools/gaia_bin/GaiaUniverseModel_0002.bin", celestial_body_flags, 0, UNIVERSE_MODEL_REGION_SIZE, &((char*)p_celestial_bodies)[UNIVERSE_MODEL_REGION_SIZE*2]);
	//gaiaReadBinaryFile("../../Gaia_Archive_Tools/gaia_bin/GaiaUniverseModel_0003.bin", celestial_body_flags, 0, UNIVERSE_MODEL_REGION_SIZE, &((char*)p_celestial_bodies)[UNIVERSE_MODEL_REGION_SIZE*3]);

	gaia_real* p0 = (gaia_real*)&(((char*)p_celestial_bodies)[0]);
	gaia_real* dist0 = (gaia_real*)&(((char*)p_celestial_bodies)[8]);
	gaia_real* teff0 = (gaia_real*)&(((char*)p_celestial_bodies)[12]);
	gaia_real* rad0 = (gaia_real*)&(((char*)p_celestial_bodies)[16]);
	printf("ra0: %f\n", *p0);
	printf("dist0: %f\n", *dist0);
	printf("teff0: %f\n", *teff0);
	printf("rad0: %f\n", *rad0);
	//
	//float celestial_bodies[10] = {
	//	0.1f, 
	//	0.1f,
	//	1.0f,
	//	1.0f,
	//	1.0f,
	//	0.1f,
	//	0.1f,
	//	5.0f,
	//	1.0f,
	//	1.0f
	//};

	VkBuffer celestial_body_buffer;
	VkDeviceMemory celestial_body_buffer_memory;
	shCreateVertexBuffer(&engine.core, UNIVERSE_MODEL_REGIONS_SIZE, &celestial_body_buffer);
	shAllocateVertexBuffer(&engine.core, celestial_body_buffer, &celestial_body_buffer_memory);
	shWriteVertexBufferMemory(&engine.core, celestial_body_buffer_memory, UNIVERSE_MODEL_REGIONS_SIZE, p_celestial_bodies);

	shCreateScene(&engine.scenes[0]);
	const uint32_t camera_entity = shCreateEntity(&engine.scenes[0]);
	ShCamera* p_camera = shAddShCamera(&engine.scenes[0], camera_entity);
	p_camera->fov = 1.0f;
	p_camera->nc = 1.0E-3f;
	p_camera->fc = 1.0E38f;
	p_camera->speed = 2.0f;
	p_camera->flags = SH_CAMERA_SETUP_FREE_FLIGHT;
	const ShTransform* p_camera_transform = shAddShTransform(&engine.scenes[0], camera_entity);
	shSceneInit(&engine, 0);

	void* push_constant[128 / 8];
	while (shIsWindowActive(engine.window.window)) {
		glfwPollEvents();
		shGetTime(&engine.time);
		shGetCursorPosition(&engine.window);

		shFrameReset(&engine.core);
		uint32_t frame_index = 0;
		shFrameBegin(&engine.core, &frame_index);

		shSceneUpdate(&engine, 0);

		shBindPipeline(&engine.core, &engine.p_materials[0].pipeline);

		memcpy(push_constant, p_camera->projection, 64);
		memcpy(&push_constant[64/8], p_camera->view, 64);
		shPushConstants(&engine.core, push_constant, &engine.p_materials[0].pipeline);

		shBindVertexBuffer(&engine.core, &celestial_body_buffer);

		shDraw(&engine.core, UNIVERSE_MODEL_REGIONS_SIZE * 3);

		shEndPipeline(&engine.p_materials[0].pipeline);
		


		shFrameEnd(&engine.core, frame_index);
	}
	free(p_celestial_bodies);

	shMaterialsRelease(&engine.core, &engine.material_count, &engine.p_materials);
	shSceneRelease(&engine, 0);
	shClearBufferMemory(engine.core.device, celestial_body_buffer, celestial_body_buffer_memory);
	shVulkanRelease(&engine.core);
    return 0;
}

#ifdef _MSC_VER
#pragma warning (disable: 4996)
#endif//_MSC_VER
#include <stdlib.h>
#include <stdio.h>
const char* readBinary(const char* path, uint32_t* p_size) {
	FILE* stream = fopen(path, "rb");
	if (stream == NULL) {
		return NULL;
	}
	fseek(stream, 0, SEEK_END);
	uint32_t code_size = ftell(stream);
	fseek(stream, 0, SEEK_SET);
	char* code = (char*)calloc(1, code_size);
	if (code == NULL) {
		return NULL;
	}
	fread(code, code_size, 1, stream);
	*p_size = code_size;
	fclose(stream);
	return code;
}