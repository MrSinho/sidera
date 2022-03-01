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

typedef struct GaiaUniverseModelMemory {
	ShMaterialHost	materials[1];
	uint32_t		used_vram;
	void*			p_celestial_bodies;
	uint32_t		vertex_buffer_count;
	VkBuffer		vertex_buffers[64];
	VkDeviceMemory	vertex_buffers_memory[64];
	void*			push_constant[128 / sizeof(void*)];
	void*			uniform_buffer[16 / sizeof(void*)];
} GaiaUniverseModelMemory;


const char* readBinary(const char* path, uint32_t* p_size);

void gaiaUniverseModelEngineSetup(ShEngine* p_engine);

void gaiaUniverseModelSetupMaterial(ShEngine* p_engine, const char* vertex_shader_path, const char* fragment_shader_path, GaiaUniverseModelMemory* p_universe_model);

void gaiaUniverseModelReadSources(ShEngine* p_engine, const GaiaCelestialBodyFlags celestial_body_flags, GaiaUniverseModelMemory* p_universe_model);

void gaiaUniverseModelWriteVertexBuffers(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

void gaiaUniverseModelSceneUpdate(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

void gaiaUniverseModelSceneSetup(ShEngine* p_engine);

void gaiaUniverseModelMemoryRelease(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model);

void gaiaUniverseModelEngineShutdown(ShEngine* p_engine);


int main(void) {
	//ENGINE SETUP
	ShEngine engine = { 0 };
	gaiaUniverseModelEngineSetup(&engine);

	//SETUP MAIN MATERIAL
	GaiaUniverseModelMemory universe_model = { 0 };
	gaiaUniverseModelSetupMaterial(&engine, "../shaders/bin/celestialBody.vert.spv", "../shaders/bin/celestialBody.frag.spv", &universe_model);
	

	uint64_t celestial_body_flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;
	const uint32_t CELESTIAL_BODY_SIZE = gaiaGetBodySize(celestial_body_flags);

	//GET AVAILABLE MEMORY
	//READ SOURCE FILES
	gaiaUniverseModelReadSources(&engine, celestial_body_flags, &universe_model);

	//WRITE VERTEX BUFFER MEMORY
	gaiaUniverseModelWriteVertexBuffers(&engine, &universe_model);

	//CREATE SCENE
	gaiaUniverseModelSceneSetup(&engine);
	
	while (shIsWindowActive(engine.window.window)) {
		//UPDATE WINDOW
		shUpdateWindow(&engine);

		//BEGIN FRAME
		shFrameReset(&engine.core);
		uint32_t frame_index = 0;
		shFrameBegin(&engine.core, &frame_index);

		//UPDATE FRAME
		gaiaUniverseModelSceneUpdate(&engine, &universe_model);
		shDraw(&engine.core, universe_model.used_vram / CELESTIAL_BODY_SIZE);

		//END FRAME
		shEndPipeline(&engine.p_materials[0].pipeline);
		shFrameEnd(&engine.core, frame_index);
	}
	
	gaiaUniverseModelMemoryRelease(&engine, &universe_model);
	gaiaUniverseModelEngineShutdown(&engine);
    return 0;
}

void gaiaUniverseModelEngineSetup(ShEngine* p_engine) {
	assert(p_engine != NULL);
	shWindowSetup("Gaia EDR3 Universe Model", 1900, 1000, &p_engine->window);
	shCreateInstance(&p_engine->core, "Gaia EDR3 Universe Model", "SH-Engine", 1, p_engine->window.instance_extension_count, p_engine->window.pp_instance_extensions);
	shCreateWindowSurface(p_engine);
	shSelectPhysicalDevice(&p_engine->core, VK_QUEUE_GRAPHICS_BIT);
	shSetLogicalDevice(&p_engine->core);
	shGetGraphicsQueue(&p_engine->core);
	shGetComputeQueue(&p_engine->core);
	shInitSwapchainData(&p_engine->core);
	shInitDepthData(&p_engine->core);
	shCreateRenderPass(&p_engine->core);
	shSetFramebuffers(&p_engine->core);
	shSetSyncObjects(&p_engine->core);
	shCreateGraphicsCommandBuffer(&p_engine->core);
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

void gaiaUniverseModelSetupMaterial(ShEngine* p_engine, const char* vertex_shader_path, const char* fragment_shader_path, GaiaUniverseModelMemory* p_universe_model) {
	p_engine->p_materials = p_universe_model->materials;
	float one = 1.0f;
	memcpy(&((char*)p_universe_model->uniform_buffer)[12], &one, 4);
	p_engine->material_count = 1;
	p_engine->p_materials->pipeline.shader_module_count = 0;

	uint32_t vertex_shader_size = 0;
	uint32_t fragment_shader_size = 0;
	char* vertex_code = (char*)readBinary(vertex_shader_path, &vertex_shader_size);
	char* fragment_code = (char*)readBinary(fragment_shader_path, &fragment_shader_size);
	shCreateShaderModule(p_engine->core.device, vertex_shader_size, vertex_code, &p_engine->p_materials[0].pipeline);
	shCreateShaderModule(p_engine->core.device, fragment_shader_size, fragment_code, &p_engine->p_materials[0].pipeline);
	free(vertex_code);
	free(fragment_code);
	shCreateShaderStage(p_engine->core.device, p_engine->p_materials[0].pipeline.shader_modules[0], VK_SHADER_STAGE_VERTEX_BIT, &p_engine->p_materials[0].pipeline);
	shCreateShaderStage(p_engine->core.device, p_engine->p_materials[0].pipeline.shader_modules[1], VK_SHADER_STAGE_FRAGMENT_BIT, &p_engine->p_materials[0].pipeline);

	shSetPushConstants(VK_SHADER_STAGE_VERTEX_BIT, 0, 128, &p_engine->p_materials[0].pipeline);

	shCreateUniformBuffer(&p_engine->core, 0, 16, &p_engine->p_materials[0].pipeline);
	shAllocateUniformBuffers(&p_engine->core, &p_engine->p_materials[0].pipeline);
	shDescriptorSetLayout(&p_engine->core, 0, VK_SHADER_STAGE_FRAGMENT_BIT, &p_engine->p_materials[0].pipeline);
	shCreateDescriptorPools(&p_engine->core, &p_engine->p_materials[0].pipeline);
	shAllocateDescriptorSets(&p_engine->core, &p_engine->p_materials[0].pipeline);

	shSetVertexInputAttribute(0, SH_VEC1_SIGNED_FLOAT, 0, 4, &p_engine->p_materials[0].fixed_states);	//asc
	shSetVertexInputAttribute(1, SH_VEC1_SIGNED_FLOAT, 4, 4, &p_engine->p_materials[0].fixed_states);	//dec
	shSetVertexInputAttribute(2, SH_VEC1_SIGNED_FLOAT, 8, 4, &p_engine->p_materials[0].fixed_states);	//baricentric_distance
	shSetVertexInputAttribute(3, SH_VEC1_SIGNED_FLOAT, 12, 4, &p_engine->p_materials[0].fixed_states);	//teff

	shSetFixedStates(&p_engine->core, SH_FIXED_STATES_POLYGON_MODE_FACE | SH_FIXED_STATES_PRIMITIVE_TOPOLOGY_POINT_LIST, &p_engine->p_materials[0].fixed_states);
	shSetupGraphicsPipeline(&p_engine->core, p_engine->p_materials[0].fixed_states, &p_engine->p_materials[0].pipeline);
}

void gaiaUniverseModelReadSources(ShEngine* p_engine, const GaiaCelestialBodyFlags celestial_body_flags, GaiaUniverseModelMemory* p_universe_model) {
	assert(p_universe_model != NULL);

	uint32_t available_video_memory = 0;
	shGetMemoryBudgetProperties(p_engine->core.physical_device, &available_video_memory, NULL, NULL);
	available_video_memory /= 20;
	p_universe_model->p_celestial_bodies = calloc(1, available_video_memory);
	assert(p_universe_model->p_celestial_bodies != NULL);
	void* src;
	for (uint32_t i = 0; i < 2; i++) {
		uint32_t bytes_read = 0;
		gaiaReadBinaryFileFromID("../gaia_resources/", i, celestial_body_flags, 0, 0, &bytes_read, &src);
		if (p_universe_model->used_vram + bytes_read >= available_video_memory) {
			break;
		}
		memcpy(&((char*)p_universe_model->p_celestial_bodies)[p_universe_model->used_vram], src, bytes_read);
		p_universe_model->used_vram += bytes_read;
	}
	gaiaFree(src);
}

void gaiaUniverseModelWriteVertexBuffers(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	const uint32_t MAX_GPU_HEAP_SIZE = 67108864;
	uint32_t written_memory = 0;
	
	p_universe_model->vertex_buffer_count = (p_universe_model->used_vram > MAX_GPU_HEAP_SIZE) ? (p_universe_model->used_vram / MAX_GPU_HEAP_SIZE) : 1;
	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		uint32_t buffer_size = p_universe_model->used_vram > MAX_GPU_HEAP_SIZE ? MAX_GPU_HEAP_SIZE : p_universe_model->used_vram;
		shCreateVertexBuffer(&p_engine->core, buffer_size, &p_universe_model->vertex_buffers[i]);

		shAllocateVertexBuffer(&p_engine->core, p_universe_model->vertex_buffers[i], &p_universe_model->vertex_buffers_memory[i]);

		shWriteVertexBufferMemory(&p_engine->core, p_universe_model->vertex_buffers_memory[i], buffer_size, &((char*)p_universe_model->p_celestial_bodies)[written_memory]);
		written_memory += buffer_size;
		if (written_memory >= p_universe_model->used_vram) { break; }
	}
}

void gaiaUniverseModelSceneSetup(ShEngine* p_engine) {
	shCreateScene(&p_engine->scenes[0]);
	const uint32_t camera_entity = shCreateEntity(&p_engine->scenes[0]);
	ShCamera* p_camera = shAddShCamera(&p_engine->scenes[0], camera_entity);
	p_camera->fov = 1.0f;
	p_camera->nc = 1.0E-3f;
	p_camera->fc = 1.0E3f;
	p_camera->speed = 0.5f;
	p_camera->flags = SH_CAMERA_SETUP_FREE_FLIGHT;
	ShTransform* p_camera_transform = shAddShTransform(&p_engine->scenes[0], camera_entity);
	shSceneInit(p_engine, 0);
}

void gaiaUniverseModelSceneUpdate(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	ShCamera* p_camera = shGetShCamera(&p_engine->scenes[0], 0);
	if (shIsKeyPressed(p_engine->window, SH_KEY_LEFT_SHIFT)) {
		p_camera->speed = 5.0f;
	}
	if (shIsKeyReleased(p_engine->window, GLFW_KEY_LEFT_SHIFT)) {
		p_camera->speed = 0.1f;
	}
	shSceneUpdate(p_engine, 0);
	shBindPipeline(&p_engine->core, &p_engine->p_materials[0].pipeline);

	shUpdateUniformBuffers(&p_engine->core, &p_engine->p_materials[0].pipeline);

	memcpy(p_universe_model->uniform_buffer, shGetShTransform(&p_engine->scenes[0], 0)->position, 12);
	shWriteUniformBufferMemory(&p_engine->core, 0, p_universe_model->uniform_buffer, &p_engine->p_materials[0].pipeline);
	shBindUniformBuffer(&p_engine->core, 0, &p_engine->p_materials[0].pipeline);

	memcpy(p_universe_model->push_constant, p_camera->projection, 64);
	memcpy(&p_universe_model->push_constant[64 / sizeof(void*)], p_camera->view, 64);
	shPushConstants(&p_engine->core, p_universe_model->push_constant, &p_engine->p_materials[0].pipeline);

	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		shBindVertexBuffer(&p_engine->core, &p_universe_model->vertex_buffers[i]);
	}
}

void gaiaUniverseModelMemoryRelease(ShEngine* p_engine, GaiaUniverseModelMemory* p_universe_model) {
	free(p_universe_model->p_celestial_bodies);
	for (uint32_t i = 0; i < p_universe_model->vertex_buffer_count; i++) {
		shClearBufferMemory(p_engine->core.device, p_universe_model->vertex_buffers[i], p_universe_model->vertex_buffers_memory[i]);
	}
}

void gaiaUniverseModelEngineShutdown(ShEngine* p_engine) {
	shClearUniformBufferMemory(&p_engine->core, 0, &p_engine->p_materials[0].pipeline);
	shDestroyPipeline(&p_engine->core, &p_engine->p_materials[0].pipeline);
	shSceneRelease(p_engine, 0);
	shVulkanRelease(&p_engine->core);
}

#ifdef __cplusplus
}
#endif//__cplusplus