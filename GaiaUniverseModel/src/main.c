#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifdef _MSC_VER
#pragma warning (disable: 4005 4996 6011)
#endif//_MSC_VER

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <engine/shEngine.h>

#include <shvulkan/shVkCore.h>
#include <shvulkan/shVkMemoryInfo.h>
#include <shvulkan/shVkPipelineData.h>
#include <shvulkan/shVkDrawloop.h>

#include <ecs/shEcsImplementation.h>
#include <ecs/shCamera.h>
#include <ecs/shTransform.h>

#include <gaia_archive_tools/gaiaArchiveTools.h>


const char* readBinary(const char* path, uint32_t* p_size);

void gaiaUniverseModelGetId(const uint32_t id, char* s_dst);

int main(void) {

	ShEngine engine = { 0 };
	shWindowSetup("Gaia EDR3 Universe Model", 1900, 1000, &engine.window);
	shCreateInstance(&engine.core, "Gaia EDR3 Universe Model", "SH-Engine", 1, engine.window.instance_extension_count, engine.window.pp_instance_extensions);
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
	
	ShMaterialHost materials[1] = { 0 };
	engine.material_count = 1;
	engine.p_materials = materials;
	uint32_t vertex_shader_size = 0;
	uint32_t fragment_shader_size = 0;
	char* vertex_code = (char*)readBinary("../shaders/bin/celestialBody.vert.spv", &vertex_shader_size);
	char* fragment_code = (char*)readBinary("../shaders/bin/celestialBody.frag.spv", &fragment_shader_size);
	shCreateShaderModule(engine.core.device, vertex_shader_size, vertex_code, &engine.p_materials[0].pipeline);
	shCreateShaderModule(engine.core.device, fragment_shader_size, fragment_code, &engine.p_materials[0].pipeline);
	free(vertex_code);
	free(fragment_code);
	shCreateShaderStage(engine.core.device, engine.p_materials[0].pipeline.shader_modules[0], VK_SHADER_STAGE_VERTEX_BIT, &engine.p_materials[0].pipeline);
	shCreateShaderStage(engine.core.device, engine.p_materials[0].pipeline.shader_modules[1], VK_SHADER_STAGE_FRAGMENT_BIT, &engine.p_materials[0].pipeline);

	shSetPushConstants(VK_SHADER_STAGE_VERTEX_BIT, 0, 128, &engine.p_materials[0].pipeline);

	shCreateUniformBuffer(&engine.core, 0, 16, &engine.p_materials[0].pipeline);
	shAllocateUniformBuffers(&engine.core, &engine.p_materials[0].pipeline);
	shDescriptorSetLayout(&engine.core, 0, VK_SHADER_STAGE_FRAGMENT_BIT, &engine.p_materials[0].pipeline);
	shCreateDescriptorPools(&engine.core, &engine.p_materials[0].pipeline);
	shAllocateDescriptorSets(&engine.core, &engine.p_materials[0].pipeline);
	
	shSetVertexInputAttribute(0, SH_VEC1_SIGNED_FLOAT, 0, 4, &engine.p_materials[0].fixed_states); //asc
	shSetVertexInputAttribute(1, SH_VEC1_SIGNED_FLOAT, 4, 4, &engine.p_materials[0].fixed_states); //dec
	shSetVertexInputAttribute(2, SH_VEC1_SIGNED_FLOAT, 8, 4, &engine.p_materials[0].fixed_states); //baricentric_distance
	shSetVertexInputAttribute(3, SH_VEC1_SIGNED_FLOAT,12, 4, &engine.p_materials[0].fixed_states); //teff

	shSetFixedStates(&engine.core, SH_FIXED_STATES_POLYGON_MODE_FACE | SH_FIXED_STATES_PRIMITIVE_TOPOLOGY_POINT_LIST, &engine.p_materials[0].fixed_states);
	shSetupGraphicsPipeline(&engine.core, engine.p_materials[0].fixed_states, &engine.p_materials[0].pipeline);

	//typedef struct celestialbody_t {
	//	double ra;
	//	double dec;
	//	float baricentric_distance;
	//	float teff;
	//}celestialbody_t;
	#define CELESTIAL_BODY_SIZE 16
	#define CELESTIAL_BODY_COUNT 800000
	#define UNIVERSE_MODEL_REGION_SIZE CELESTIAL_BODY_SIZE * CELESTIAL_BODY_COUNT

	uint32_t available_video_memory = 0;
	shGetMemoryBudgetProperties(engine.core.physical_device, &available_video_memory, NULL, NULL);
	available_video_memory /= UNIVERSE_MODEL_REGION_SIZE * 10;
	available_video_memory *= UNIVERSE_MODEL_REGION_SIZE;

	void* p_celestial_bodies = calloc(1, available_video_memory);
	assert(p_celestial_bodies != NULL);

	uint64_t celestial_body_flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;

	uint32_t used_vram = 0;
	for (uint32_t i = 0; used_vram < available_video_memory; i++) {
		char s_id[5] = "0000";
		gaiaUniverseModelGetId(i, s_id);
		uint32_t bytes_read = 0;
		gaiaReadWeb(s_id, celestial_body_flags, 0, 0, &bytes_read, &((char*)p_celestial_bodies)[UNIVERSE_MODEL_REGION_SIZE * i]);
		used_vram += bytes_read;
		break;
	}

	VkBuffer celestial_body_buffers[64];
	VkDeviceMemory celestial_body_buffers_memory[64];
	const uint32_t MAX_GPU_HEAP_SIZE = 67108864;
	uint32_t vertex_buffer_count = (used_vram > MAX_GPU_HEAP_SIZE) ? (used_vram / MAX_GPU_HEAP_SIZE) : 1;
	uint32_t written_memory = 0;

	for (uint32_t i = 0; i < vertex_buffer_count; i++) {
		uint32_t buffer_size = used_vram > MAX_GPU_HEAP_SIZE ? MAX_GPU_HEAP_SIZE : used_vram;
		shCreateVertexBuffer(&engine.core, buffer_size, &celestial_body_buffers[i]);

		shAllocateVertexBuffer(&engine.core, celestial_body_buffers[i], &celestial_body_buffers_memory[i]);

		shWriteVertexBufferMemory(&engine.core, celestial_body_buffers_memory[i], buffer_size, &((char*)p_celestial_bodies)[written_memory]);
		written_memory += buffer_size;
		if (written_memory >= used_vram) { break; }
	}

	shCreateScene(&engine.scenes[0]);
	const uint32_t camera_entity = shCreateEntity(&engine.scenes[0]);
	ShCamera* p_camera = shAddShCamera(&engine.scenes[0], camera_entity);
	p_camera->fov = 1.0f;
	p_camera->nc = 1.0E-3f;
	p_camera->fc = 1.0E3f;
	p_camera->speed = 0.5f;
	p_camera->flags = SH_CAMERA_SETUP_FREE_FLIGHT;
	const ShTransform* p_camera_transform = shAddShTransform(&engine.scenes[0], camera_entity);
	shSceneInit(&engine, 0);

	void* push_constant[128 / sizeof(void*)];
	void* uniform_buffer[16 / sizeof(void*)];
	float one = 1.0f;
	memcpy(&((char*)uniform_buffer)[12], &one, 4);
	
	while (shIsWindowActive(engine.window.window)) {
		glfwPollEvents();
		shGetTime(&engine.time);
		shGetCursorPosition(&engine.window);

		if (shIsKeyPressed(engine.window, SH_KEY_LEFT_SHIFT)) {
			p_camera->speed = 5.0f;
		}
		if (shIsKeyReleased(engine.window, GLFW_KEY_LEFT_SHIFT)) {
			p_camera->speed = 0.1f;
		}

		shFrameReset(&engine.core);
		uint32_t frame_index = 0;
		shFrameBegin(&engine.core, &frame_index);

		shSceneUpdate(&engine, 0);

		shBindPipeline(&engine.core, &engine.p_materials[0].pipeline);

		shUpdateUniformBuffers(&engine.core, &engine.p_materials[0].pipeline);

		memcpy(uniform_buffer, p_camera_transform->position, 12);
		shWriteUniformBufferMemory(&engine.core, 0, uniform_buffer, &engine.p_materials[0].pipeline);
		shBindUniformBuffer(&engine.core, 0, &engine.p_materials[0].pipeline);

		memcpy(push_constant, p_camera->projection, 64);
		memcpy(&push_constant[64/sizeof(void*)], p_camera->view, 64);
		shPushConstants(&engine.core, push_constant, &engine.p_materials[0].pipeline);

		for (uint32_t i = 0; i < vertex_buffer_count; i++) {
			shBindVertexBuffer(&engine.core, &celestial_body_buffers[i]);
		}

		shDraw(&engine.core, used_vram / CELESTIAL_BODY_SIZE);

		shEndPipeline(&engine.p_materials[0].pipeline);
		
		shFrameEnd(&engine.core, frame_index);
	}
	free(p_celestial_bodies);

	shClearUniformBufferMemory(&engine.core, 0, &engine.p_materials[0].pipeline);
	shDestroyPipeline(&engine.core, &materials[0].pipeline);
	shSceneRelease(&engine, 0);
	for (uint32_t i = 0; i < vertex_buffer_count; i++) {
		shClearBufferMemory(engine.core.device, celestial_body_buffers[i], celestial_body_buffers_memory[i]);
	}
	shVulkanRelease(&engine.core);
    return 0;
}

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

void gaiaUniverseModelGetId(const uint32_t id, char* s_dst) {
	if (id >= 1000) {
		itoa(id, s_dst, 10);
	}
	else if (100 <= id && id < 1000) {
		itoa(id, &s_dst[1], 10);
	}
	else if (10 <= id && id < 100) {
		itoa(id, &s_dst[2], 10);
	}
	else if (id < 10) {
		itoa(id, &s_dst[3], 10);
	}
}

#ifdef __cplusplus
}
#endif//__cplusplus