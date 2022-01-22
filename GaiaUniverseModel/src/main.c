#include <shvulkan/shVkCore.h>
#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkPipelineData.h>
#include <shvulkan/shVkDrawLoop.h>

#include <GLFW/glfw3.h>

#include <gaia_archive_tools/gaiaArchiveTools.h>

#include <assert.h>

const char* readBinary(const char* path, uint32_t* p_size);

#define _CRT_SECURE_NO_WARNINGS

#pragma warning (disable: 26812 4996)

#include <cglm/cglm.h>

int main(void) {

	const char* application_name = "Gaia Universe Model";
	const uint32_t width = 720;
	const uint32_t height = 480;
	assert(glfwInit());
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(width, height, application_name, NULL, NULL);
	uint32_t extensions_count = 0;
	const char** extensions_names = glfwGetRequiredInstanceExtensions(&extensions_count);

	ShVkCore core = { 0 };
	shCreateInstance(&core, application_name, "shVulkan Engine", extensions_count, extensions_names);
	glfwCreateWindowSurface(core.instance, window, NULL, &core.surface.surface);
	core.surface.width = width;
	core.surface.height = height;

	shSelectPhysicalDevice(&core, SH_VK_CORE_GRAPHICS);
	shSetLogicalDevice(&core);
	shGetGraphicsQueue(&core);
	shInitSwapchainData(&core);
	shInitDepthData(&core);
	shCreateRenderPass(&core);
	shSetFramebuffers(&core);
	shSetSyncObjects(&core);
	shCreateGraphicsCommandBuffer(&core);

	ShVkGraphicsPipeline pipeline = { 0 };

	uint32_t vertex_shader_size = 0;
	uint32_t fragment_shader_size = 0;
	const char* vertex_code = readBinary("../shaders/bin/celestialBody.vert.spv", &vertex_shader_size);
	const char* fragment_code = readBinary("../shaders/bin/celestialBody.frag.spv", &fragment_shader_size);
	shCreateShaderModule(core.device, vertex_shader_size, vertex_code, &pipeline);
	shCreateShaderModule(core.device, fragment_shader_size, fragment_code, &pipeline);
	shCreateShaderStage(core.device, pipeline.shader_modules[0], VK_SHADER_STAGE_VERTEX_BIT, &pipeline);
	shCreateShaderStage(core.device, pipeline.shader_modules[1], VK_SHADER_STAGE_FRAGMENT_BIT, &pipeline);

	ShVkFixedStates fixed_states = { 0 };
	shSetVertexInputAttribute(0, SH_VEC1_SIGNED_FLOAT, 0, 4, &fixed_states); //asc
	shSetVertexInputAttribute(1, SH_VEC1_SIGNED_FLOAT, 4, 4, &fixed_states); //dec
	shSetVertexInputAttribute(2, SH_VEC1_SIGNED_FLOAT, 8, 4, &fixed_states); //baricentric_distance
	shSetVertexInputAttribute(3, SH_VEC1_SIGNED_FLOAT,12, 4, &fixed_states); //teff
	shSetVertexInputAttribute(4, SH_VEC1_SIGNED_FLOAT,16, 4, &fixed_states); //radius

	shSetFixedStates(&core, SH_FIXED_STATES_POLYGON_MODE_POINTS | SH_FIXED_STATES_PRIMITIVE_TOPOLOGY_POINT_LIST, &fixed_states);
	shSetupGraphicsPipeline(&core, fixed_states, &pipeline);

	//typedef struct celestialbody_t {
	//	double ra;
	//	double dec;
	//	float baricentric_distance;
	//	float teff;
	//	float radius;
	//}celestialbody_t;
	#define CELESTIAL_BODY_SIZE 20
	#define UNIVERSE_MODEL_REGION_SIZE CELESTIAL_BODY_SIZE * 800000
	void* p_celestial_bodies = calloc(1, UNIVERSE_MODEL_REGION_SIZE);
	uint64_t celestial_body_flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF | GAIA_RADIUS;
	gaiaReadBinary("../../Gaia_Archive_Tools/gaia_bin/GaiaUniverseModel_4999.bin", celestial_body_flags, UNIVERSE_MODEL_REGION_SIZE, p_celestial_bodies);

	//gaia_real* p0 = (gaia_real*)&(((char*)p_celestial_bodies)[0]);
	//gaia_real* p1 = (gaia_real*)&(((char*)p_celestial_bodies)[20]);
	//printf("ra0: %f\n", *p0);
	//printf("ra1: %f\n", *p1);
	
	float celestial_body[5] = {
		0.01f, 
		0.01f,
		1.0f,
		0.0f,
		0.0f
	};

	VkBuffer celestial_body_buffer;
	VkDeviceMemory celestial_body_buffer_memory;
	shCreateVertexBuffer(&core, UNIVERSE_MODEL_REGION_SIZE, &celestial_body_buffer);
	shAllocateVertexBuffer(&core, celestial_body_buffer, &celestial_body_buffer_memory);
	shWriteVertexBufferMemory(&core, celestial_body_buffer_memory, UNIVERSE_MODEL_REGION_SIZE, p_celestial_bodies);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		shFrameReset(&core);
		uint32_t frame_index = 0;
		shFrameBegin(&core, &frame_index);

		shBindPipeline(&core, &pipeline);

		//celestial_body[1] += 0.08f;
		//celestial_body[0] += 0.08f;
		//shWriteVertexBufferMemory(&core, celestial_body_buffer_memory, CELESTIAL_BODY_SIZE, celestial_body);
		shBindVertexBuffer(&core, &celestial_body_buffer);
		shDraw(&core, 1);

		shEndPipeline(&pipeline);
		shFrameEnd(&core, frame_index);
	}
	free(p_celestial_bodies);

	shClearBufferMemory(core.device, celestial_body_buffer, celestial_body_buffer_memory);
	shDestroyPipeline(&core, &pipeline);
	shVulkanRelease(&core);
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